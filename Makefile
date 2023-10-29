CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -DWITHOUT_NUMPY -I /usr/include/python3.10 -lpython3.10
TARGET = sorting_algorithms

all: $(TARGET)

$(TARGET): sorting_algorithms.cpp
	$(CXX) sorting_algorithms.cpp $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

setup-ubuntu-focal:
	sudo apt install g++ python3 python3-matplotlib

run-docker:
	docker build --file Dockerfile --output . .
