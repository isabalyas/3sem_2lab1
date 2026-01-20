CXX = g++
CXXFLAGS = -Wall -std=c++20 
MODULES = array hashtable stack queue 1list 2list tree
SOURCES = main.cpp $(foreach dir,$(MODULES),$(wildcard $(dir)/*.cpp))
OBJECTS = $(SOURCES:%.cpp=build/%.o)
TARGET = bin/main

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p bin
	$(CXX) $(OBJECTS) -o $@

build/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf build bin

run: $(TARGET)
	./$(TARGET)

-include $(OBJECTS:.o=.d)