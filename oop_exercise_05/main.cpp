#include <iostream>
#include <memory> // unique_ptr
#include <algorithm> // for_each, count_if
#include "rectangle.hpp"
#include "queue.hpp"

using figure_type = int;

void writeMenu() {
	std::cout << "0\tВыход из программы\n";
	std::cout << "1\tЗапрос меню\n";
	std::cout << "2\tДобавить фигуру в очередь\n";
	std::cout << "3\tУдалить фигуру из очереди по номеру\n";
	std::cout << "4\tПечать фигур в очереди\n";
	std::cout << "5\tПечать количества фигур, площадь которых меньше заданной\n";
}

int main() {
	Queue <Rectangle<figure_type>> st;

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
					std::unique_ptr<Rectangle<figure_type>> rec = std::make_unique<Rectangle<figure_type>>();
					try {
						std::cin >> rec;
						st.Push(std::move(rec));
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
			case 5:
				{
					int max=0;
					std::cout << "Введите площадь: ";
					std::cin >> max;
					std::cout << std::endl;
					size_t a = std::count_if(st.begin(), st.end(), [max](std::unique_ptr<Rectangle<figure_type>>& elem){return elem->Area()<max;});
					std::cout << a << std::endl;
				}
				break;
			
		}
	}

	return 0;
}