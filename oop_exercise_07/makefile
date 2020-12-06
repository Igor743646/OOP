CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
INCLUDES = -I "."
OBJS = main.o

all: main.out

# сборка исполняемого файла
main.out: main.o
	${CC} ${FLAGS} ${INCLUDES} ${OBJS} -o $@

# сборка объектных файлов
main.o: src/main.cpp
	${CC} ${FLAGS} ${INCLUDES} -c $<

run:
	./main.out < test0.txt

runv:
	valgrind --leak-check=full -s ./main.out < tests/test0.txt