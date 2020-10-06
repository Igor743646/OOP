#include <iostream>
#include <string.h>
#include "money.hpp"

void writeInfo() {
	std::cout << "Лабораторная работа №2\nСтудент: Глушатов Игорь\nГруппа: М80-207Б-19\n\n";
	std::cout << "Создать класс Money для работы с денежными суммами.\n";
	std::cout << "Сумма денег должна быть представлено двумя полями: типа unsigned long long для рублей и типа unsigned char – для копеек.\n";
	std::cout << "Дробная часть (копейки) при выводе на экран должна быть отделена от целой части запятой.\n";
	std::cout << "Реализовать сложение сумм, вычитание, деление сумм, деление суммы на дробное число, умножение на дробное число и операции сравнения.\n";
	std::cout << "Операции сложения, вычитания, умножения, деления, сравнения (на равенство, больше и меньше) должны быть выполнены в виде перегрузки операторов.\n";
	std::cout << "Необходимо реализовать пользовательский литерал для работы с константами типа Money.\n\n";
}

void writeMenu() {
	std::cout << "0\tВыход из программы\n";
	std::cout << "1\tЗапрос меню\n";
	std::cout << "2\tСложение переменных типа money\n";
	std::cout << "3\tВычитание переменных типа money\n";
	std::cout << "4\tУмножение переменных типа money\n";
	std::cout << "5\tДеление переменных типа money\n";
	std::cout << "6\tУмножение переменной типа money на число\n";
	std::cout << "7\tДеление переменной типа money на число\n";
	std::cout << "8\tСравнение переменных типа money\n";
	std::cout << "9\tПользовательский литерал для типа money\n\n";
}

int main() {

	Money x, y;
	double d;
	short comand;
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
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n';
				std::cout << "Введите переменную y (рубли и копейки через пробел): ";
				std::cin >> y; std::cout << '\n';
				std::cout << "x+y = " << x+y << std::endl;
				break;
			case 3:
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n'; 
				std::cout << "Введите переменную y (рубли и копейки через пробел): ";
				std::cin >> y; std::cout << '\n';
				std::cout << "x-y = " << x-y << std::endl;
				break;
			case 4:
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n'; 
				std::cout << "Введите переменную y (рубли и копейки через пробел): ";
				std::cin >> y; std::cout << '\n';
				std::cout << "x*y = " << x*y << std::endl;
				break;
			case 5:
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n'; 
				std::cout << "Введите переменную y (рубли и копейки через пробел): ";
				std::cin >> y; std::cout << '\n';
				std::cout << "x/y = " << x/y << std::endl;
				break;
			case 6:
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n'; 
				std::cout << "Введите переменную y (число типа double): ";
				std::cin >> d; std::cout << '\n';
				std::cout << "x*y = " << x*d << std::endl;
				break;
			case 7:
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n'; 
				std::cout << "Введите переменную y (число типа double): ";
				std::cin >> d; std::cout << '\n';
				std::cout << "x/y = " << x/d << std::endl;
				break;
			case 8:
				std::cout << "Введите переменную x (рубли и копейки через пробел): ";
				std::cin >> x; std::cout << '\n'; 
				std::cout << "Введите переменную y (рубли и копейки через пробел): ";
				std::cin >> y; std::cout << '\n';
				if (x<=y) {
					std::cout << "x<=y\n";
				}
				if (x>=y) {
					std::cout << "x>=y\n";
				}
				if (x<y) {
					std::cout << "x<y\n";
				}
				if (x>y) {
					std::cout << "x>y\n";
				}
				if (x==y) {
					std::cout << "x==y\n";
				}
				break;
			case 9:
				std::cout << "435,7"_mon << std::endl;
				std::cout << "86756545,6564"_mon << std::endl;
				std::cout << "9,0"_mon << std::endl;
				std::cout << "400,00"_mon << std::endl;
				break;
		}

	}

	return 0;
}