#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double sigmoid(double x){
   return 1/(1+exp(-x));
}

double dsigmoid(double x){
   return x * (1 - x);
} 

void shuffle(int *array, size_t n){
   if (n > 1){
      size_t i;
      for (i = 0; i < n -1 ; i++){
         size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
         int t = array[j];
         array[j] = array[i];
         array[i] = t;
      }
   }
}

double initweights() {
   return (
      ((double)rand()) / ((double)RAND_MAX)
   );
}

#define numinputs 2
#define numhiddennodes 2
#define numoutputs 1
#define numtrainingsets 4



int main() {
   const double lr = 0.1f;

   double hiddenlayer[numhiddennodes];
   double outputlayer[numoutputs];

   double hiddenlayerbias[numhiddennodes];
   double outputlayerbias[numoutputs];

   double hiddenweights[numinputs][numhiddennodes];
   double outputweights[numhiddennodes][numoutputs];

   double traininginputs[numtrainingsets][numinputs] = {
                                                      {0.0f, 0.0f},
                                                      {1.0f, 0.0f},
                                                      {0.0f, 1.0f},
                                                      {1.0f, 1.0f}
   };

   double trainingoutputs[numtrainingsets][numoutputs] = {
                                                      {0.0f},
                                                      {1.0f},
                                                      {1.0f},
                                                      {0.0f}
   };

   for(int i = 0; i < numinputs; i++){
      for(int j = 0; j < numhiddennodes; j++){
         hiddenweights[i][j] = initweights();
      }
   }

   for(int i = 0; i < numhiddennodes; i++){
      for(int j = 0; i < numoutputs; j++){
         outputweights[i][j] = initweights();
      }
   }

   for(int i = 0; i < numoutputs; i++){
         outputlayer[i] = initweights();
   }

   int trainingsetorder[] = {0,1,2,3};

   int numberofepochs = 100000000;

   //Training commencing
   for(int epoch = 0; epoch < numberofepochs; epoch++){
      shuffle(trainingsetorder, numtrainingsets);

      for( int x = 0; x < numtrainingsets; x++){
         int i = trainingsetorder[x];

         //Forward pass

         //Compute hidden layer activation

         for(int j = 0; j < numhiddennodes; j++){
            double activation = hiddenlayerbias[j];

            for(int k = 0; k < numinputs; k++){
               activation += traininginputs[i][k] * hiddenweights[k][j];
            }
            hiddenlayer[j] = sigmoid(activation);
         }

         //Compute output layer activation

         for(int j = 0; j < numoutputs; j++){
            double activation = outputlayerbias[j];

            for(int k = 0; k < numhiddennodes; k++){
               activation += hiddenlayer[k] * outputweights[k][j];
            }
            outputlayer[j] = sigmoid(activation);
         }
         printf("Input: %g   Output: %g    Predicted Output: %g \n",
               traininginputs[i][0], traininginputs[i][1],
               outputlayer[0], trainingoutputs[i][0]);

         //Backprop

         // Compute change in output weights
         double deltaoutput[numoutputs];

         for(int j = 0; j < numoutputs; j++){
            double error = (trainingoutputs[i][j] - outputlayer[j]);
            deltaoutput[j] = error * dsigmoid(outputlayer[j]);
         }
         // Compute change in hidden weights
         double deltahidden[numhiddennodes];

         for(int j = 0; j < numhiddennodes; j++){
            double error = 0.0f;
            for(int k = 0; k < numoutputs; k++){
               error += deltaoutput[k] * outputweights[j][k];
            }
            deltahidden[j] = error * dsigmoid(hiddenlayer[j]);
         }

         //Apply change in output weights
         for(int j = 0;j < numoutputs; j++){
            outputlayerbias[j] += deltaoutput[j] * lr;

            for(int k = 0; k < numhiddennodes; k++){
               outputweights[k][j] +=  hiddenlayer[k] * deltaoutput[j] * lr;
            }
         }
         
         //Apply change in hidden weights
         for(int j = 0;j < numhiddennodes; j++){
            hiddenlayerbias[j] += deltahidden[j] * lr;
            for(int k = 0; k < numinputs; k++){
               hiddenweights[k][j] +=  traininginputs[i][k] * deltahidden[j] * lr;
            }
         }

      }


   }

    // Print final weights after training
    fputs ("Final Hidden Weights\n[ ", stdout);
    for (int j=0; j<numhiddennodes; j++) {
        fputs ("[ ", stdout);
        for(int k=0; k<numinputs; k++) {
            printf ("%f ", hiddenweights[k][j]);
        }
        fputs ("] ", stdout);
    }
    
    fputs ("]\nFinal Hidden Biases\n[ ", stdout);
    for (int j=0; j<numhiddennodes; j++) {
        printf ("%f ", hiddenlayerbias[j]);
    }

    fputs ("]\nFinal Output Weights\n", stdout);
    for (int j=0; j<numoutputs; j++) {
        fputs ("[ ", stdout);
        for (int k=0; k<numhiddennodes; k++) {
            printf ("%f ", outputweights[k][j]);
        }
        fputs ("]\n", stdout);
    }

    fputs ("Final Output Biases\n[ ", stdout);
    for (int j=0; j<numoutputs; j++) {
        printf ("%f ", outputlayerbias[j]);
        
    }
    
    fputs ("]\n", stdout);



   return 0;
}
