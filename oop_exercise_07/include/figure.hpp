#ifndef FIGURE_HPP
#define FIGURE_HPP

#include <iostream>
#include <string>

template<class T>
std::istream& operator>> (std::istream& in, std::pair<T,T>& A) { return in >> A.first >> A.second; }

template<class T>
std::istream& operator>> (std::istream& in, std::pair<T,T>* A) { return in >> *A; }

template<class T>
std::ostream& operator<< (std::ostream& out, const std::pair<T,T>& A) { return out << "(" << A.first << ", " << A.second << ")"; }

template<class T>
std::ostream& operator<< (std::ostream& out, const std::pair<T,T>* A) { return out << *A; }

template <class T>
class Figure {

	using pair = std::pair<T,T>;
	using vector = std::vector<pair>;

	protected:

		pair _point;
		unsigned int _numberPoints;
		vector _points;

	public:
		Figure(): _point(pair(0,0)), _numberPoints(0) { CreatePoints(); };

		Figure(const pair cen, const unsigned int num): _point(cen), _numberPoints(num) {
			if (num < 0) throw "Отрицательное количество вершин";
			CreatePoints();
		}

		~Figure() = default;

		virtual std::string GetStringCharacteristics() {
			std::string str;

			for (unsigned int i = 0; i < _points.size(); ++i)
				str += std::to_string(_points[i].first) + " " +
					   std::to_string(_points[i].second);

			return str + "\n";
		}

		virtual void Print() { std::cout << *this; }

		virtual void CreatePoints() {
			for (unsigned int i = 0; i<_numberPoints; ++i) _points.push_back(pair(0,0));
		}

		friend std::ostream& operator<< (std::ostream& out, const Figure<T>* A) {
			out << "Точки фигуры: ";
			for (unsigned int i = 0; i<A->_numberPoints; ++i) out << A->_points[i] << " ";
			return out << "\n";
		}

		friend std::istream& operator>> (std::istream& in, Figure<T>* A) {
			std::cout << "Введите точку (два числа заданного типа через пробел): "; 
			in >> A->_point;
			std::cout << "Введите количество точек фигуры: ";
			in >> A->_numberPoints;
			if (A->_numberPoints < 0) throw "Отрицательное количество вершин";
			A->CreatePoints();
			return in;
		}

		friend std::ostream& operator<< (std::ostream& out, const Figure<T> A) { return out << &A; }
		friend std::istream& operator>> (std::istream& in, Figure<T>& A) { return in >> &A; }
};

#endif