CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic

all: main.out

main.out: main.cpp rectangle.hpp queue.hpp
	${CC} ${FLAGS} main.cpp -o main.out

run:
	./main.out