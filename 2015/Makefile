CC=gcc
CFLAGS= -Wall -g -O3

SOURCES=$(wildcard day*.c)
SOURCE=main.c
TARGET=main

.PHONY: run clean hash

$(TARGET): $(SOURCE) $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@

run: $(TARGET)
	time -p ./$(TARGET)

clean:
	rm $(TARGET)

hash:
	$(CC) $(CFLAGS) hashmap.c -o hashmap
	./hashmap
