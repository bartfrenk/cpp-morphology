INCLUDES = $(shell pkg-config lua5.1 --cflags)
LIBS = -lfreeimage
OPTIONS = -std=c++11
OBJECTS = freeimage.o geometry.o
CC = g++

.PHONY: all clean

all: client.out

client.out: client.cpp
	$(CC) -o $@ $^ $(OPTIONS) $(LIBS)

clean:
	@rm -rf *.o *.out
