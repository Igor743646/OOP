#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP

#include "figure.hpp"

template <class T>
class Rhombus: public Figure<T> {

	using pair = std::pair<T,T>;
	using vector = std::vector<pair>;

	private:

		T _height;
		T _width;

		void CreatePoints() override {
			this->_points[0] = pair(this->_point.first, this->_point.second - _height/2);
			this->_points[1] = pair(this->_point.first+_width/2, this->_point.second);
			this->_points[2] = pair(this->_point.first+_width, this->_point.second-_height/2);
			this->_points[3] = pair(this->_point.first+_width/2, this->_point.second-_height);
		}

	public:
		Rhombus(): Figure<T>(pair(0,0), 4), _height(0), _width(0) {};

		Rhombus(const pair cen, const T h, const T w): Figure<T>(cen, 4), _height(h), _width(w) {
			if ((_width <= 0) or (_height <= 0)) throw "Ширина и высота должны быть положительными!";
			CreatePoints();
		}

		~Rhombus() = default;

		void Print() { std::cout << *this; }

		std::string GetStringCharacteristics() {
			return std::string(std::to_string(this->_point.first) + " " + \
				   std::to_string(this->_point.second) + " " + \
				   std::to_string(_height) + " " + \
				   std::to_string(_width) + "\n");
		}

		friend std::ostream& operator<< (std::ostream& out, const Rhombus<T>* A) {
			out << "Точки ромба: ";
			for (unsigned int i = 0; i<A->_numberPoints; ++i) out << A->_points[i] << " ";
			return out << "\n";
		}

		friend std::istream& operator>> (std::istream& in, Rhombus<T>* A) {
			std::cout << "Введите точку (два числа заданного типа через пробел): "; 
			in >> A->_point;
			std::cout << "Введите высоту ромба: ";
			in >> A->_height;
			std::cout << "Введите ширину ромба: ";
			in >> A->_width;
			if ((A->_width <= 0) or (A->_height <= 0)) throw "Ширина и высота должны быть положительными!";
			A->CreatePoints();
			return in;
		}

		friend std::ostream& operator<< (std::ostream& out, const Rhombus<T> A) {return out << &A; }
		friend std::istream& operator>> (std::istream& in, Rhombus<T>& A) { return in >> &A; }
};

#endif