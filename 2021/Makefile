SYLT := sylt
LUA := luajit

SRC := main.sy
TARGET := /tmp/aoc21.lua

.PHONY: run

run:
	@$(SYLT) --output $(TARGET) $(SRC)
	@$(LUA) $(TARGET)
