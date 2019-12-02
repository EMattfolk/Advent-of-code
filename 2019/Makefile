CC=g++
CFLAGS= --std=c++17 -O2 -Wall

SOURCES = $(wildcard day*.cpp)
RUNNABLES = $(SOURCES:day%.cpp=%)

.SILENT: all run
.PHONY: all run clean

all: $(RUNNABLES)

run: $(RUNNABLES)
	time -p ./runall $(RUNNABLES)

$(RUNNABLES):
	$(CC) $(CFLAGS) -o $@ day$@.cpp

clean:
	rm $(RUNNABLES)
