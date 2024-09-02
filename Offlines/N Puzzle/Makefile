# This Makefile is designed to be simple and readable. It does not
# aim at portability. It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2

EXEC = main

CPP_SOURCES = main.cpp util/util.cpp
CPP_OBJS = $(CPP_SOURCES:.cpp=.o)
OBJS = $(CPP_OBJS)

.PHONY: all run clean

all: $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(EXEC): $(OBJS)
	$(CXX) -o $@ $(OBJS)

run: $(EXEC)
	./$(EXEC)

clean:
	del /Q $(EXEC).exe $(OBJS)