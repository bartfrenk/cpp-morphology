LIBS = -lfreeimage
CFLAGS = -std=c++11 -g
OBJECTS = client.o image/strict.o image/base.o image/pixel.o utils/log.o
CC = g++

.PHONY: clean

%.o: %.cpp
	$(CC) -c -o $@ $(CFLAGS) $<

client.out: $(OBJECTS)
	$(CC) -o $@ $^ $(LIBS)


clean:
	@rm -rf $(OBJECTS) client.out
