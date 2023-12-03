BIN_PART1=bin/part1.o
BIN_PART2=bin/part2.o

CXX = clang++
ARGS = -std=c++2a -Wall
SRC = *.cpp
RELEASE=no
INPUT=./input.txt

# extension
ifeq ($(OS),Windows_NT)
    BIN_PART1=bin/part1.exe
	BIN_PART2=bin/part2.exe
endif

# debug and release args
ifeq ($(RELEASE), yes)
	ARGS +=-O3
else
	ARGS +=-g
endif

all:
	$(CXX) $(SRC) $(ARGS) -o $(BIN_PART1) -DAOC_PART1
	$(CXX) $(SRC) $(ARGS) -o $(BIN_PART2) -DAOC_PART2

