FLAGS = -std=c++17

calculator: calculator.o
	g++ calculator.o -o calculator

calculator.o: calculator.cpp
	g++ -c $(FLAGS) calculator.cpp

clean:
	rm *.o calculator