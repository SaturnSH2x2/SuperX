# I have no idea how to properly write a Makefile
# so this probably sucks but I kinda don't care

CC       := gcc
CXX      := g++
CFLAGS   := -g -Wall
INCLUDES := -I/usr/include
LIBS_ALL := -llua5.4 -lSDL

SOURCES := $(wildcard source/*.c) lodepng/lodepng.cpp

objects/%.o: %
	mkdir -p $(@D)
	$(CXX) $(CFLAGS) $^ -o $@ -c $(INCLUDES) $(LIBS_ALL)

SuperX: $(SOURCES:%=objects/%.o)
	$(CXX) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS_ALL)
clean::
	rm -rf objects
	rm -rf ./SuperX
