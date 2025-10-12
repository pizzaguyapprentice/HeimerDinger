# For SDL only
SDLFLAGS = $(shell pkg-config --cflags --libs sdl2 SDL2_image)
SDLTARGET = sdltest
SDLSRC = sdltest.c

$(SDLTARGET): $(SDLSRC)
	gcc sdltest.c -o sdltest $(SDLFLAGS) 

clean:
	rm -f $(SDLTARGET)

gtktest: main.c
	gcc main.c -o gtk `pkg-config --cflags glib-2.0` `pkg-config --cflags gdk-pixbuf-2.0` `pkg-config --cflags --libs gtk4 sdl2` 