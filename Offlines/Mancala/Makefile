# This Makefile is designed for separate compilation.
# It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -MMD

EXEC = main

# List of all source files
CPP_SOURCES = main.cpp \
classes/util/util.cpp \
classes/game/GameSnapshot.cpp \
classes/game/GameIO.cpp \
classes/turn/Turn.cpp \
classes/turn/PlayerATurn.cpp \
classes/turn/PlayerBTurn.cpp \
classes/game/modes/Mode.cpp \
classes/game/modes/ModeFactory.cpp \
classes/ai/AI.cpp \
classes/game/modes/HumanVsHuman.cpp \
classes/game/modes/HumanVsAI.cpp \
classes/game/modes/AIVsAI.cpp \
classes/heuristics/H1.cpp \
classes/heuristics/H2.cpp \
classes/heuristics/H3.cpp \
classes/heuristics/H4.cpp \
classes/heuristics/HeuristicFactory.cpp

CPP_OBJS = $(CPP_SOURCES:.cpp=.o)
OBJS = $(CPP_OBJS)

OBJS_WIN = $(subst /,\,$(OBJS))

.PHONY: all run clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

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

run: $(EXEC)
	./$(EXEC)

-include $(CPP_SOURCES:.cpp=.d) # Include dependency files
