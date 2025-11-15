# Makefile for Railway Simulation (C++98)

CXX = g++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -I./include
LDFLAGS =

# Source files
SRCS = src/main.cpp \
       src/Types.cpp \
       src/Node.cpp \
       src/Rail.cpp \
       src/Train.cpp \
       src/RailwayNetwork.cpp \
       src/SimulationManager.cpp \
       src/SimulationManagerUpdate.cpp \
       src/DijkstraPathfinding.cpp \
       src/EventFactory.cpp \
       src/InputParser.cpp \
       src/InputParserHelp.cpp \
       src/OutputWriter.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = railway_simulation

# Default target
all: $(TARGET)

# Link
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Build complete: $(TARGET)"

# Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJS) $(TARGET)
	rm -f output/*.result
	@echo "Clean complete"

fclean: clean
	rm -f $(TARGET)

# Rebuild
re: fclean all

# Run with example files
run: $(TARGET)
	./$(TARGET) examples/network.txt examples/trains.txt

# Help
help:
	./$(TARGET) --help

# Test
test: $(TARGET)
	@echo "Running simulation..."
	./$(TARGET) examples/network.txt examples/trains.txt
	@echo "\nChecking output files..."
	@ls -lh output/

.PHONY: all clean fclean re run help test
