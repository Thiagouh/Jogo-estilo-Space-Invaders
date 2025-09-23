EXEC=space_invaders

SRCS=space_invaders_sdl.c

CC=gcc

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Linux)
    CFLAGS=$(shell sdl2-config --cflags)
    LIBS=$(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image
else ifeq ($(UNAME_S),Darwin)
    CFLAGS=$(shell sdl2-config --cflags)
    LIBS=$(shell sdl2-config --libs) -lSDL2_ttf -lSDL2_image
else
    CFLAGS=-IC:/msys64/mingw64/include
    LIBS=-LC:/msys64/mingw64/lib -lmingw32 -mwindows -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image
endif

all: $(EXEC)

$(EXEC): $(SRCS)
	$(CC) $(SRCS) -o $(EXEC) $(CFLAGS) $(LIBS)

clean:
	rm -f $(EXEC)
