#include <iostream>
#include <vector>
#include "figure.hpp"
#include "trapezoid.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"

void writeInfo() {
	std::cout << "Лабораторная работа №3\nСтудент: Глушатов Игорь\nГруппа: М80-207Б-19\n\n";
	// std::cout << "Создать класс Money для работы с денежными суммами.\n";
	// std::cout << "Сумма денег должна быть представлено двумя полями: типа unsigned long long для рублей и типа unsigned char – для копеек.\n";
	// std::cout << "Дробная часть (копейки) при выводе на экран должна быть отделена от целой части запятой.\n";
	// std::cout << "Реализовать сложение сумм, вычитание, деление сумм, деление суммы на дробное число, умножение на дробное число и операции сравнения.\n";
	// std::cout << "Операции сложения, вычитания, умножения, деления, сравнения (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов.\n";
	// std::cout << "Необходимо реализовать пользовательский литерал для работы с константами типа Money.\n\n";
}

void writeMenu() {
	std::cout << "0\tВыход из программы\n";
	std::cout << "1\tЗапрос меню\n";
	std::cout << "2\tВвести фигуру\n";
	std::cout << "3\tУдалить фигуру по индексу\n";
	std::cout << "4\tПосчитать общую площадь фигур в векторе\n";
	std::cout << "5\tВывести для всех фигур координаты их вершин\n";
	std::cout << "6\tВывести для всех фигур их площадь\n";
	std::cout << "7\tВывести для всех фигур их геометрический центр\n";
	std::cout << "8\tВывести для фигуры её координаты, геометрический центр и площадь по индексу\n\n";
}

int main() {
	std::vector<Figure*> v;

	short comand, figcomand;
	bool menu=1;

	writeInfo();
	writeMenu();
	while(menu) {

		std::cout << "Введите команду: ";
		std::cin >> comand; 
		std::cout << '\n';

		switch(comand) 
		{
			case 0:
				menu = 0;
				break;
			case 1:
				writeMenu();
				break;
			case 2:
				std::cout << "Какую фигуру вставить?\n0 - Прямоугольник\n1 - Трапеция\n2 - Ромб\n: ";
				std::cin >> figcomand; 
				std::cout << "\n";
				switch (figcomand) 
				{
					case 0:
						Rectangle* x; x = new Rectangle();
						std::cin >> x;
						v.push_back(x);
						break;
					case 1:
						Trapezoid* y; y = new Trapezoid();
						std::cin >> y;
						v.push_back(y);
						break;
					case 2:
						Rhombus* z; z = new Rhombus();
						std::cin >> z;
						v.push_back(z);
						break;
				}
				std::cout << "\n";
				break;
			case 3:
				unsigned int id;
				std::cout << "Какой элемент удалить?\n:";
				std::cin >> id;
				if (id>=v.size()) {
					std::cout << "Элемента с таким индексом нет\n";
				} else {
					v.erase(v.begin()+id);
					std::cout << "Элемент удален\n";
				}
				break;
			case 4:
				double sumArea; 
				sumArea = 0;
				for (unsigned int i = 0; i < v.size(); ++i) {
					sumArea += v[i]->Area();
				}
				std::cout << "Суммарная площадь фигур: " << sumArea << "\n\n";
				break;
			case 5:
				for (unsigned int i = 0; i < v.size(); ++i) {
					std::cout << v[i];
				}
				std::cout << "\n";
				break;
			case 6:
				for (unsigned int i = 0; i < v.size(); ++i) {
					std::cout << v[i]->Area() << "\n";
				}
				std::cout << "\n";
				break;
			case 7:
				for (unsigned int i = 0; i < v.size(); ++i) {
					std::cout << v[i]->GeometricCenter() << "\n";
				}
				std::cout << "\n";
				break;
			case 8:
				std::cout << "Какой элемент вывести?\n:";
				std::cin >> id;
				if (id>=v.size()) {
					std::cout << "Элемента с таким индексом нет\n";
				} else {
					std::cout << v[id] << "Геометрический центр: " << v[id]->GeometricCenter() << "\nПлощадь: " << \
					v[id]->Area() << "\n";
				}
				std::cout << "\n";
				break;
		}
	}

	return 0;
}