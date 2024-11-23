CXX = g++
CXXFLAGS = -I./../include -std=c++17 -Wall
OUT = run.out

MAIN_SRC = run.cpp
APP_SRC = $(wildcard ../src/*.cpp)

OBJ = $(MAIN_SRC:.cpp=.o) $(APP_SRC:../src/%.cpp=../src/%.o)
OUT_OBJ = $(MAIN_SRC:.cpp=.out) $(APP_SRC:../src/%.cpp=../src/%.out)

SRC = $(MAIN_SRC) $(APP_SRC)

run: $(OBJ)
	@$(CXX) $(OBJ) $(CXXFLAGS) -o $(OUT) -lm
	@./$(OUT)

plot: $(OBJ)
	$(CXX) $(OBJ) $(CXXFLAGS) -o $(OUT) -lm
	@./$(OUT) -p | gnuplot -p -e "set xrange [0:101]; plot '-' with lines" 

clean:
	rm -f $(OBJ) $(OUT_OBJ) *.out

