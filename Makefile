# I have no idea how to properly write a Makefile
# so this probably sucks but I kinda don't care

SOURCES := $(wildcard source/*.c) lodepng/lodepng.cpp
COMMIT := $(shell git rev-parse --short HEAD)

CC       := gcc
CXX      := g++
CFLAGS   := -g -Wall -O2 -DCOMMIT=\"$(COMMIT)\"
INCLUDES := -I/usr/include/lua5.2 -I./lodepng -I/usr/local/include
LIBS_ALL := -llua5.2 -ljansson -ltmxparser -lSDL2_mixer -lSDL2

objects/%.o: %
	mkdir -p $(@D)
	$(CXX) $(CFLAGS) $^ -o $@ -c $(INCLUDES) $(LIBS_ALL)

SuperX: $(SOURCES:%=objects/%.o)
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(INCLUDES) $(LIBS_ALL)
clean::
	rm -rf objects
	rm -rf ./SuperX
