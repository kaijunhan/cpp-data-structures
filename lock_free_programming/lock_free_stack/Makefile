# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

# Source files and target
SRC = lock_free_stack.cpp   lock_free_stack.h           # Add more .cpp files here, e.g., main.cpp utils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = lock_free_stack        # Name of the final executable

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

# Phony targets
.PHONY: all clean
