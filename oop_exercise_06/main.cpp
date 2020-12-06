// Глушатов Игорь М80-207Б-19 Лабораторная работа №6 
// Аллокаторы

#include <iostream>
#include <memory> // unique_ptr
#include <algorithm> // for_each, count_if
#include <vector>
#include "rectangle.hpp"
#include "queue.hpp"

using figure_type = int;

void writeMenu() {
	std::cout << "0\tВыход из программы\n";
	std::cout << "1\tЗапрос меню\n";
	std::cout << "2\tДобавить фигуру в очередь\n";
	std::cout << "3\tУдалить фигуру из очереди по номеру\n";
	std::cout << "4\tПечать фигур в очереди\n";
}

int main() {
	Queue <Rectangle<figure_type>, Allocator<Rectangle<figure_type>, 10000>> st;

	short comand;
	bool menu=1;

	writeMenu();
	while(menu) {

		std::cout << '\n';
		std::cout << "Введите команду: ";
		std::cin >> comand; 
		std::cout << std::endl;

		switch(comand) 
		{
			case 0:
				menu = 0;
				break;
			case 1:
				writeMenu();
				break;
			case 2:
				{
					Rectangle<figure_type> rec;
					try {
						std::cin >> rec;
						st.Push(rec);
					} catch(const char* exception) {
						std::cerr << "ERROR: " << exception << '\n';
					}
					
				}
				break;
			case 3:
				{
					unsigned int id;
					std::cout << "Введите индекс элемента, который нужно удалить: ";
					std::cin >> id;
					std::cout << std::endl;
					try {
						st.Remove(id);
					} catch(const char* exception) {
						std::cerr << "ERROR: " << exception << '\n';
					}
					
				}
				break;
			case 4:
				std::for_each(st.begin(), st.end(), print<figure_type>);
				break;
		}
	}

	return 0;
}