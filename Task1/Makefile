CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -O2

SRC = FileSystem.cpp Main.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = vfs

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp FileSystem.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
