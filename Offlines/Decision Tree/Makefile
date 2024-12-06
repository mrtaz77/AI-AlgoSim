# This Makefile is designed for separate compilation.
# It requires GNU Make.

CXX = g++
CXXFLAGS = -Wall -Wextra -O2 -MMD

EXEC = main

# List of all source files
CPP_SOURCES = main.cpp \
classes/validator/ColumnValidator.cpp \
classes/validator/FileExists.cpp \
classes/validator/RowValidator.cpp \
classes/validator/Validator.cpp \
classes/DatasetConstants.cpp \
classes/Dataset.cpp \
classes/attribute/BestAttribute.cpp \
classes/attribute/RandomTopAttribute.cpp \
classes/heuristic/GiniImpurity.cpp \
classes/heuristic/InformationGain.cpp \
classes/tree/InternalNode.cpp \
classes/tree/TerminalNode.cpp \
classes/TreeBuilder.cpp \
classes/util/util.cpp

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
	./$(EXEC) $(file) $(run)

# Include dependency files
-include $(DEPS)
