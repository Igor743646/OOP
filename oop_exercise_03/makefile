CC = g++
FLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic

all: main.out

main.out: main.cpp figure.hpp point.hpp rectangle.hpp trapezoid.hpp rhombus.hpp
	${CC} ${FLAGS} main.cpp -o main.out

run:
	./main.out