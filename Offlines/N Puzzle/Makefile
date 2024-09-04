# This Makefile is designed to be simple and readable. It does not
# aim at portability. It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2

EXEC = main

CPP_SOURCES = main.cpp \
util/util.cpp \
classes/NPuzzle.cpp \
classes/solvability/EvenSolvable.cpp \
classes/solvability/OddSolvable.cpp \
classes/solver/Solver.cpp

CPP_OBJS = $(CPP_SOURCES:.cpp=.o)
OBJS = $(CPP_OBJS)

# Convert forward slashes to backslashes for Windows
OBJS_WIN = $(subst /,\,$(OBJS))

.PHONY: all run clean

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) -o $@ $(OBJS)

run: $(EXEC)
	./$(EXEC)

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(EXEC).exe) $(OBJS_WIN)
else ifeq ($(shell uname), Linux)
	rm -f $(EXEC) $(OBJS)
else ifeq ($(shell uname), Darwin)
	rm -f $(EXEC) $(OBJS)
else
	@echo "Unsupported OS: Please manually delete the files."
endif