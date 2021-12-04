SYLT := sylt
LUA := luajit

SRC := main.sy
TARGET := /tmp/aoc21.lua

.PHONY: run

run:
	@$(SYLT) -c $(TARGET) $(SRC)
	@$(LUA) $(TARGET)
