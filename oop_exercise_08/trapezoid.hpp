#ifndef TRAPEZOID_HPP
#define TRAPEZOID_HPP

#include "figure.hpp"
template <class T>
class Trapezoid: public Figure<T> {

	using pair = std::pair<T,T>;
	using vector = std::vector<pair>;

	private:

		T _height;
		T _base1;
		T _base2;

		void CreatePoints() override {
			if (_base1<=_base2) {
				this->_points[0] = pair(this->_point.first, this->_point.second - _height);
				this->_points[1] = pair(this->_point.first+(_base2-_base1)/2, this->_point.second);
				this->_points[2] = pair(this->_point.first+(_base2-_base1)/2+_base1, this->_point.second);
				this->_points[3] = pair(this->_point.first+_base2, this->_point.second-_height);
			} else {
				this->_points[0] = pair(this->_point.first-(_base2-_base1)/2, this->_point.second - _height);
				this->_points[1] = pair(this->_point.first, this->_point.second);
				this->_points[2] = pair(this->_point.first+_base1, this->_point.second);
				this->_points[3] = pair(this->_point.first+_base2-(_base2-_base1)/2, this->_point.second-_height);
			}
		}

	public:
		Trapezoid(): Figure<T>(pair(0,0), 4), _height(0), _base1(0), _base2(0) {};

		Trapezoid(const pair cen, const T h, const T b1, const T b2): Figure<T>(cen, 4), _height(h), _base1(b1), _base2(b2) {
			if ((_base1 <= 0) or (_height <= 0) or (_base2 <= 0)) throw "Основания и высота должны быть положительными!";
			CreatePoints();
		}

		~Trapezoid() = default;

		void Print() { std::cout << *this; }

		std::string GetStringCharacteristics() {
			return std::string(std::to_string(this->_point.first) + " " + \
				   std::to_string(this->_point.second) + " " + \
				   std::to_string(_height) + " " + \
				   std::to_string(_base1) + " " + \
				   std::to_string(_base1) + "\n");
		}

		friend std::ostream& operator<< (std::ostream& out, const Trapezoid<T>* A) {
			out << "Точки трапеции: ";
			for (unsigned int i = 0; i<A->_numberPoints; ++i) out << A->_points[i] << " ";
			return out << "\n";
		}

		friend std::istream& operator>> (std::istream& in, Trapezoid<T>* A) {
			std::cout << "Введите координаты положения трапеции (два числа заданного типа через пробел): ";
			in >> A->_point;
			std::cout << "Введите высоту трапеции: ";
			in >> A->_height;
			std::cout << "Введите верхнее основание трапеции: ";
			in >> A->_base1;
			std::cout << "Введите нижнее основание трапеции: ";
			in >> A->_base2;
			if ((A->_base1 <= 0) or (A->_height <= 0) or (A->_base2 <= 0)) throw "Основания и высота должны быть положительными!";
			A->CreatePoints();
			return in;
		}

		friend std::ostream& operator<< (std::ostream& out, const Trapezoid<T> A) { return out << &A; }
		friend std::istream& operator>> (std::istream& in, Trapezoid<T>& A) { return in >> &A; }
};

#endif