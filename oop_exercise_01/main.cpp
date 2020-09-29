#include <iostream>
#include <typeinfo>
#include "Position.hpp"

int main() {
    Position a; Position b; int num;

    std::cout << "Введите a (два целых числа через пробел): "; std::cin >> a; std::cout << "\n";
    std::cout << "Введите b (два целых числа через пробел): "; std::cin >> b; std::cout << "\n";
    std::cout << "a = " << a << "\n" << "b = " << b << "\n";

    std::cout << "Сумма a и b: " << a+b << "\n";
    std::cout << "Разность a и b: " << a-b << "\n";
    std::cin.clear();
    std::cin.ignore(32767,'\n');
    std::cout << "Введите число, на которое хотите умножить переменную а: "; std::cin >> num; std::cout << "\n";
    std::cout << "Умножение a на число " << num << ": " << a*num << "\n";
    std::cin.clear();
    std::cin.ignore(32767,'\n');
    std::cout << "Введите число на которое хотите разделить переменную а: "; std::cin >> num; std::cout << "\n";
    std::cout << "Деление a на число " << num << ": " << a/num << "\n";

    std::cout << "Меньше: " << (a<b) << "\n";
    std::cout << "Больше: " << (a>b) << "\n";
    std::cout << "Равно: " << (a==b) << "\n";
    std::cout << "Меньше или равно: " << (a<=b) << "\n";
    std::cout << "Больше или равно: " << (a>=b) << "\n\n";
    return 0;
}
