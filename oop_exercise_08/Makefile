CC = g++
FLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic
INCLUDES = -I "."
OBJS = main.o

all: main.out

# сборка исполняемого файла
main.out: main.o *.hpp
	${CC} ${FLAGS} ${INCLUDES} ${OBJS} -o $@ -lpthread

# сборка объектных файлов
main.o: main.cpp
	${CC} ${FLAGS} ${INCLUDES} -c $<

run:
	./main.out 

runv:
	valgrind --leak-check=full -s ./main.out