# I have no idea how to properly write a Makefile
# so this probably sucks but I kinda don't care

CC       := gcc
CXX      := g++
CFLAGS   := -g -Wall -O2
INCLUDES := -I/usr/include/lua5.2 -I./lodepng
LIBS_ALL := -llua5.2 -ljansson -lSDL2_mixer -lSDL2

SOURCES := $(wildcard source/*.c) lodepng/lodepng.cpp

objects/%.o: %
	mkdir -p $(@D)
	$(CXX) $(CFLAGS) $^ -o $@ -c $(INCLUDES) $(LIBS_ALL)

SuperX: $(SOURCES:%=objects/%.o)
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(INCLUDES) $(LIBS_ALL)
clean::
	rm -rf objects
	rm -rf ./SuperX
