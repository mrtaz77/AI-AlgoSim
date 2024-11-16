# This Makefile is designed for separate compilation.
# It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -g -MMD

EXEC = main

# List of all source files
CPP_SOURCES = main.cpp \
classes/util/util.cpp \
classes/graph/Graph.cpp \
classes/tsp/TSP.cpp \
classes/tsp/heuristics/Heuristic.cpp \
classes/tsp/heuristics/constructive/Constructive.cpp \
classes/tsp/heuristics/constructive/NearestNeighbour.cpp \
classes/tsp/heuristics/constructive/FarthestInsertion.cpp \
classes/tsp/heuristics/constructive/MST.cpp \
classes/tsp/heuristics/perturbative/Perturbative.cpp \
classes/tsp/heuristics/perturbative/TwoOpt.cpp \
classes/tsp/heuristics/perturbative/NodeShift.cpp \
classes/tsp/heuristics/perturbative/TwoHalfOpt.cpp

CPP_OBJS = $(CPP_SOURCES:.cpp=.o)
OBJS = $(CPP_OBJS)

OBJS_WIN = $(subst /,\,$(OBJS))

DEPS = $(CPP_SOURCES:.cpp=.d)

.PHONY: all run clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(EXEC).exe) $(OBJS_WIN) $(DEPS)
else ifeq ($(shell uname), Linux)
	rm -f $(EXEC) $(OBJS) $(DEPS)
else ifeq ($(shell uname), Darwin)
	rm -f $(EXEC) $(OBJS) $(DEPS)
else
	@echo "Unsupported OS: Please manually delete the files."
endif

run: $(EXEC)
	./$(EXEC) $(ARGS)

# Include dependency files
-include $(DEPS) 