#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include <memory> // shared_ptr
#include <string> // string
#include <fstream> // {i/o}fstream
#include <typeinfo> // typeid
#include <algorithm> // for_each

#include "factory.hpp"

template <class T>
class Document {

	using path = std::string;
	using figure_value_type = T;
	using ptr = std::shared_ptr<Figure<figure_value_type>>;

	enum undo {
		INSERT,
		ERASE,
	};

	private:

		std::vector<ptr> v;
		std::vector<std::pair<ptr, undo>> stack;
		std::string document_name;

	public:
		Document(): document_name("untitled") {};
		Document(std::string name): document_name(name) {};
		Document(char* name): document_name(name) {};
		~Document() = default;

		std::string GetName() {
			return document_name;
		}

		void SetName(std::string &name) {
			document_name = name;
		}

		void Import(std::string path) {
			std::ifstream out;
			out.open("saved/" + path + ".fig_doc");

			if (!out) {
				std::cout << "Такого файла не существует или он не смог открыться\n\n";
				return;
			} 

			stack.clear();
			v.clear();

			int key;
			std::vector<figure_value_type> numbers;
			ptr in;

			while (out >> key) {
				switch (key) {
					case 0:
						numbers.reserve(4);
						for (int i = 0; i < 4; ++i) out >> numbers[i];
						in = ptr(new Rectangle<figure_value_type> 
							(std::pair<figure_value_type, figure_value_type> (numbers[0], numbers[1]), 
								numbers[2], numbers[3]));
						v.push_back(in);
						break;
					case 1:
						numbers.reserve(4);
						for (int i = 0; i < 4; ++i) out >> numbers[i];
						in = ptr(new Rhombus<figure_value_type> 
							(std::pair<figure_value_type, figure_value_type> (numbers[0], numbers[1]), 
								numbers[2], numbers[3]));
						v.push_back(in);
						break;
					case 2:
						numbers.reserve(5);
						for (int i = 0; i < 5; ++i) out >> numbers[i];
						in = ptr(new Trapezoid<figure_value_type> 
							(std::pair<figure_value_type, figure_value_type> (numbers[0], numbers[1]), 
								numbers[2], numbers[3], numbers[4]));
						v.push_back(in);
						break;
					default:
						std::cout << "Такой фигуры нет :(\n\n";
						break;
				}

			}

			std::cout << "Файл успешно импортирован\n\n";
			
			out.close();
			if (document_name == "untitled") SetName(path);
		}

		void Export() {
			std::ofstream in;
			in.open("saved/" + document_name + ".fig_doc");

			if (!in) {
				std::cout << "Экспорт в файл не удался\n\n";
				return;
			}

			for (unsigned int i = 0; i < v.size(); ++i) {

				if (typeid(*v[i]) == typeid(Rectangle<figure_value_type>)) {
					std::cout << "Прямоугольник сохраняется..." << std::endl;
					in << "0 " << v[i]->GetStringCharacteristics();
				} else if (typeid(*v[i]) == typeid(Rhombus<figure_value_type>)) {
					std::cout << "Ромб сохраняется..." << std::endl;
					in << "1 " << v[i]->GetStringCharacteristics();
				} else if (typeid(*v[i]) == typeid(Trapezoid<figure_value_type>)) {
					std::cout << "Трапеция сохраняется..." << std::endl;
					in << "2 " << v[i]->GetStringCharacteristics();
				} else {
					throw "Непонятный тип данных";
				}
			}

			in.close();
			std::cout << "Файл был экспортирован\n\n";
		}

		void AddFigure() {
			short figcomand;
			ptr in;
			std::cout << "Какую фигуру вставить?\n0 - Прямоугольник\n1 - Ромб\n2 - Трапеция\n: ";
			std::cin >> figcomand; 
			std::cout << "\n";

			switch (figcomand) {
				case 0:
					in = ptr(Factory<Rectangle<figure_value_type>>::CreatFigureAndEnterIt());
					v.push_back(in);
					std::cout << "Фигура была успешно добавлена\n\n";
					stack.push_back(std::pair<ptr, undo>(in, INSERT));
					break;
				case 1:
					in = ptr(Factory<Rhombus<figure_value_type>>::CreatFigureAndEnterIt());
					v.push_back(in);
					std::cout << "Фигура была успешно добавлена\n\n";
					stack.push_back(std::pair<ptr, undo>(in, INSERT));
					break;
				case 2:
					in = ptr(Factory<Trapezoid<figure_value_type>>::CreatFigureAndEnterIt());
					v.push_back(in);
					std::cout << "Фигура была успешно добавлена\n\n";
					stack.push_back(std::pair<ptr, undo>(in, INSERT));
					break;
				default:
					std::cout << "Такой фигуры нет :(\n\n";
					break;
			}
		}

		void DelFigure() {
			unsigned int ind;
			std::cout << "Введите номер фигуры, которую хотите удалить: ";
			std::cin >> ind;
			if (ind >= v.size()) {
				std::cout << "Фигуры с таким индексом нет\n\n";
			} else {
				stack.push_back(std::pair<ptr, undo>(v[ind], ERASE));
				v.erase(v.begin()+ind);
				std::cout << "Фигура была успешно удалена\n\n";
			}
		}

		void Undo() {
			if (stack.empty()) {
				std::cout << "Действий больше не производилось\n\n";
				return;
			}
			switch (stack[stack.size()-1].second) {
				case 0:
					for (auto iterator = v.begin(); iterator != v.end(); ++iterator) {
						if (*iterator == stack[stack.size()-1].first) {
							v.erase(iterator);
							break;
						}
					}
					std::cout << "Добавленная фигура была успешно удалена\n\n";
					break;
				case 1:
					v.push_back(stack[stack.size()-1].first);
					std::cout << "Удаленная фигура была успешно восстановлена\n\n";
					break;
				default:
					throw "В стэке неопределенная команда для undo";
			}
			stack.pop_back();
		}

		void PrintFigures() noexcept {
			std::for_each(v.begin(), v.end(), [](ptr a){a->Print();});
			std::cout << "\n";
		}

};

#endif