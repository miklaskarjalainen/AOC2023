CXX = clang++
ARGS = -std=c++17 -Wall
SRC = *.cpp
BIN=bin/day1.o
BUILD=debug

# extension
ifeq ($(OS),Windows_NT)
    BIN=bin/day1.exe
endif

# debug and release args
ifeq ($(BUILD), debug)
	ARGS +=-g
else
	ARGS +=-O3
endif

all:
	$(CXX) $(SRC) $(ARGS) -o $(BIN)

run: all
	$(BIN)