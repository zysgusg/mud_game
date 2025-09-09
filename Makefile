# Makefile for the game project
CXX = g++
CXXFLAGS = -g -Wall -std=c++17
TARGET = mud
SRCDIR = .
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET).exe $(TARGET)

.PHONY: clean

# Manual compilation command:
# g++ -g -Wall -std=c++17 *.cpp -o game_cre