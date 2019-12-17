CXX=clang++
CFLAGS= -O3 --std=c++17 -Wall

SOURCES = $(sort $(wildcard day*.cpp))
TARGETS = $(SOURCES:day%.cpp=%)

.SILENT: all run
.PHONY: all run clean

all: $(TARGETS)

run: $(TARGETS)
	time -p ./runall $(TARGETS)

$(TARGETS): %: day%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean:
	rm -f $(TARGETS)
