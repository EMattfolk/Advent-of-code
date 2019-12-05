CXX=g++
CFLAGS= -O2 --std=c++17 -Wall

SOURCES = $(sort $(wildcard day*.cpp))
RUNNABLES = $(SOURCES:day%.cpp=%)

.SILENT: all run
.PHONY: all run clean

all: $(RUNNABLES)

run: $(RUNNABLES)
	time -p ./runall $(RUNNABLES)

$(RUNNABLES): %: day%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -f $(RUNNABLES)
