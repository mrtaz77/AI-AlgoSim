# This Makefile is designed for separate compilation.
# It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -MMD # Add dependency generation flags

EXEC = main

# List of all source files
CPP_SOURCES = main.cpp \
classes/game/GameSnapshot.cpp \
classes/game/GameIO.cpp \
classes/turn/PlayerATurn.cpp \
classes/turn/PlayerBTurn.cpp \
classes/util/util.cpp \
classes/turn/Turn.cpp \
classes/game/modes/HumanVsHuman.cpp \
classes/game/modes/Mode.cpp \
classes/game/modes/ModeFactory.cpp \

CPP_OBJS = $(CPP_SOURCES:.cpp=.o)
OBJS = $(CPP_OBJS)

OBJS_WIN = $(subst /,\,$(OBJS))
DEPS = $(OBJS:.o=.d)  # Create a dependency list

.PHONY: all run clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Include dependency files
-include $(DEPS)

clean:
ifeq ($(OS),Windows_NT)
	del /Q $(subst /,\,$(EXEC).exe) $(OBJS_WIN) $(subst /,\,$(DEPS))
else ifeq ($(shell uname), Linux)
	rm -f $(EXEC) $(OBJS) $(DEPS)
else ifeq ($(shell uname), Darwin)
	rm -f $(EXEC) $(OBJS) $(DEPS)
else
	@echo "Unsupported OS: Please manually delete the files."
endif

run: $(EXEC)
	./$(EXEC)
