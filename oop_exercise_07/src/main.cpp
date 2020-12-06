/*
	Глушатов Игорь Сергеевич. М80-207Б-19. Лабораторная работа №7.
	Проектирование структуры классов.
*/

#include <iostream>
#include <vector> // vector
#include <memory> // shared_ptr
#include <string> // string

#include "include/document.hpp" // Document

void writeInfo() {
	std::cout << "Лабораторная работа №7\nСтудент: Глушатов Игорь\nГруппа: М80-207Б-19\n\n";
}

void writeMenu() {
	std::cout << "0\tВыход из программы\n";
	std::cout << "1\tЗапрос меню\n";
	std::cout << "2\tСоздать новый документ\n";
	std::cout << "3\tИмпорт документа из файла\n";
	std::cout << "4\tЭкспорт документа в файл\n";
	std::cout << "5\tСоздание фигуры\n";
	std::cout << "6\tУдаление фигуры\n";
	std::cout << "7\tПечать фигур и их характеристик\n";
	std::cout << "8\tОтмена последнего действия (добавление или удаление фигуры)\n";
	std::cout << "9\tВыбрать документ из существующих\n";
	std::cout << "10\tИзменить название документа\n\n";
}

using doc_type = int;
using doc_ptr = std::shared_ptr<Document<doc_type>>;

enum Comand {
	END,
	WRITE_MENU,
	CREATE_DOCUMENT,
	IMPORT,
	EXPORT,
	ADD,
	DELETE,
	PRINT,
	UNDO,
	SELECT_DOCUMENT,
	RENAME_DOCUMENT,
};

int main() {

	std::vector<doc_ptr> documents = {doc_ptr(new Document<doc_type>())};
	doc_ptr curent = documents[0];

	short comand;
	bool menu = true;
	std::string path;

	writeInfo();
	writeMenu();
	while(menu) {

		std::cout << "Введите команду: ";
		std::cin >> comand;

		switch(comand) {
			case END:
				menu = false;
				break;
			case WRITE_MENU:
				writeMenu();
				break;
			case CREATE_DOCUMENT:
				std::cout << "Введите имя нового файла: ";
				std::cin >> path;
				int flag; 
				flag = false;
				for (unsigned int i=0; i<documents.size(); ++i) {
					if (path == documents[i]->GetName()) flag = true;
				}

				if (flag) {
					std::cout << "Документ с таким именем уже существует!\n\n";
				} else {
					documents.push_back(doc_ptr(new Document<doc_type>(path)));
					curent = documents[documents.size()-1];
					std::cout << "Новый документ был создан\n\n";
				}
				break;
			case IMPORT:
				std::cout << "Введите имя файла: ";
				std::cin >> path;
				curent->Import(path);
				break;
			case EXPORT:
				curent->Export();
				break;
			case ADD:
				try {
					curent->AddFigure();
				} catch (const char* exeption) {
					std::cout << "ERROR with adding: " << exeption << std::endl;
				}
				break;
			case DELETE:
				curent->DelFigure();
				break;
			case PRINT:
				curent->PrintFigures();
				break;
			case UNDO:
				curent->Undo();
				break;
			case SELECT_DOCUMENT:
				std::cout << "Открытые документы:\n";
				for (unsigned int i = 0; i < documents.size(); ++i) 
					std::cout << "\t" << (i+1) << ": " << documents[i]->GetName() << "\n";
				std::cout << std::endl;

				std::cout << "Вы сейчас находитесь здесь: " << curent->GetName() << std::endl;

				unsigned int doc_number;
				std::cout << "Введите номер документа, который хотите выбрать: ";
				std::cin >> doc_number;
				if (doc_number-1 >= documents.size()) {
					std::cout << "Такого документа нет\n\n";
				} else {
					curent = documents[doc_number-1];
					std::cout << "Текущий документ был выбран\n\n";
				}
				break;
			case RENAME_DOCUMENT:
				std::cout << "Введите новое название файла: ";
				std::cin >> path;
				curent->SetName(path);
				std::cout << "Название было изменено\n\n";
				break;
			default:
				std::cout << "Неправильно введенная команда!\n\n";
				break;
		}
	}

	return 0;
}