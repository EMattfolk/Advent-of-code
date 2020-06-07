SOURCES=$(wildcard src/*)
TARGET=main
MAIN=main.go

.PHONY: run clean

$(TARGET): $(SOURCES) $(MAIN)
	go build $(MAIN)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
