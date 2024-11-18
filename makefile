CXX = g++
CXXFLAGS = -I./include -std=c++17 -Wall -fopenmp
OUT = main.out

SRC = main.cpp src/*.cpp

run:
	@$(CXX) $(SRC) $(CXXFLAGS) -o $(OUT) -lm
	@./$(OUT)
