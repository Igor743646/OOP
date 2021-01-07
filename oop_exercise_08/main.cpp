/*
	Глушатов Игорь Сергеевич. М80-207Б-19. Лабораторная работа №8.
	Асинхронное программирование
*/

#include <iostream>
#include <vector> // vector
#include <memory> // shared_ptr
#include <string> // string
#include <string.h>
#include <stdlib.h>
#include <algorithm> // for_each
#include <fstream>
#include <thread>
#include "publisher.hpp"

void writeInfo() {
	std::cout << "Лабораторная работа №8\nСтудент: Глушатов Игорь\nГруппа: М80-207Б-19\n\n";
}

using figure_value_type = int;
using ptr = std::shared_ptr<Figure<figure_value_type>>;

int main(int argc, char* argv[]) {

	std::vector<ptr> buffer;
	const unsigned int buffer_size = (argc < 2 ? 10 : atoi(argv[1])); // устанавливает размер буфера, по дефолту 10

	bool main = true;
	short command = -1;
	short figcommand = -1;
	ptr in;

	Publisher<void, std::vector<ptr>> pub;

	pub.Add([](std::vector<ptr> buf){ // Добавляем обработчик с выводом на экран
		for (unsigned int i = 0; i < buf.size(); ++i) {
			std::cout << typeid(*buf[i]).name() << ": ";
			std::cout << buf[i]->Figure::GetStringCharacteristics();
		}
		std::cout << std::endl;
		return;
	});

	pub.Add([](std::vector<ptr> buf){ // Добавляем обработчик с выводом в файл
		std::ofstream in;
		in.open("file.txt");

		if (!in) {
			std::cout << "Ошибка записи в файл\n\n";
			return;
		}

		for (unsigned int i = 0; i < buf.size(); ++i) {
			in << typeid(*buf[i]).name() << ": ";
			in << buf[i]->Figure::GetStringCharacteristics();
		}

		in.close();
	});
	
	std::cout << "Меню:\n\t0 - выйти из программы\n\t1 - добавить фигуру\n\t2 - распечатать буфер\n\n";
	while (main) {
		std::cout << "Введите команду: ";
		std::cin >> command;

		switch(command) {
			case 0:
				main = false;
				break;
			case 1:
				std::cout << "Какую фигуру вставить?\n0 - Прямоугольник\n1 - Ромб\n2 - Трапеция\n: ";
				std::cin >> figcommand; 
				std::cout << "\n";
				switch(figcommand) {
					case 0:
						in = ptr(Factory<
								 Rectangle<
								 figure_value_type
								 >>::CreatFigureAndEnterIt());
						buffer.push_back(in);
						std::cout << "Фигура была успешно добавлена\n\n";
						break;
					case 1:
						in = ptr(Factory<Rhombus<figure_value_type>>::CreatFigureAndEnterIt());
						buffer.push_back(in);
						std::cout << "Фигура была успешно добавлена\n\n";
						break;
					case 2:
						in = ptr(Factory<Trapezoid<figure_value_type>>::CreatFigureAndEnterIt());
						buffer.push_back(in);
						std::cout << "Фигура была успешно добавлена\n\n";
						break;
					default:
						std::cout << "Такой фигуры нет :(\n\n";
						break;
				}

				if (buffer.size() == buffer_size) { // отправляем на обработку
					std::thread thread(pub, buffer);
					thread.join();
					buffer.clear();
				}

				break;
			case 2:
				std::for_each(buffer.begin(), buffer.end(), [](ptr a){a->Print();});
				std::cout << "\n";
				break;
			default:
				std::cout << "Неправильно введенная команда\n";
				break;
		}

	}

	return 0;
}