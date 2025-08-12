CC = g++
CFLAGS = -Wall -Wextra -std=c++11
TARGET = bank_system
SOURCES = Main.cpp BankSystem.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = BankSystem.hpp

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean