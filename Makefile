# I have no idea how to properly write a Makefile
# so this probably sucks but I kinda don't care

CC       := gcc
CFLAGS   := -g
LIBS_ALL := -lSDL

SOURCES := $(wildcard source/*.c)

objects/%.o: %
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $^ -o $@ -c

SuperX: $(SOURCES:%=objects/%.o)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS_ALL)
clean::
	rm -rf objects
	rm -rf ./SuperX
