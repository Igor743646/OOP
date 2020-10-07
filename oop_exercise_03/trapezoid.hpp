#ifndef TRAPEZOID_HPP
#define TRAPEZOID_HPP

#include "figure.hpp"

	class Trapezoid : public Figure {
		public:
			double base1;
			double base2;
			double height;

			Trapezoid();
			Trapezoid(Point cen, double a, double b, double c);

			void CreatePoints();
			double Area();

			friend std::ostream& operator<< (std::ostream& out, const Trapezoid* A);
			friend std::istream& operator>> (std::istream& in, const Trapezoid* A);

	};

Trapezoid::Trapezoid(): Figure(Point(0, 0), 4), base1(0), base2(0), height(0)  {
	CreatePoints();
}

Trapezoid::Trapezoid(Point cen, double a, double b, double c): Figure(cen, 4), base1(a), base2(b), height(c)  {
	CreatePoints();
}

void Trapezoid::CreatePoints() {
	points = new Point[sizeof(Point) * numberPoints];
	if (base1<=base2) {
		points[0] = Point(center.x, center.y - height);
		points[1] = Point(center.x + (base2-base1)/2, center.y);
		points[2] = Point(center.x + (base2-base1)/2 + base1, center.y);
		points[3] = Point(center.x + base2, center.y - height);
	} else {
		points[0] = Point(center.x - (base2-base1)/2, center.y - height);
		points[1] = Point(center.x, center.y);
		points[2] = Point(center.x + base1, center.y);
		points[3] = Point(center.x + base2 - (base2-base1)/2, center.y - height);
	}
}

double Trapezoid::Area() {
	return (base2+base1)/2*height;
}

std::ostream& operator<< (std::ostream& out, const Trapezoid* A) {
	for (unsigned int i = 0; i<A->numberPoints; ++i) out << A->points[i] << " ";
	return out;
}

std::istream& operator>> (std::istream& in, Trapezoid* A) {
	std::cout << "Введите координаты положения трапеции: ";
	in >> A->center;
	std::cout << "Введите верхнее основание трапеции: ";
	in >> A->base1;
	std::cout << "Введите нижнее основание трапеции: ";
	in >> A->base2;
	std::cout << "Введите высоту трапеции: ";
	in >> A->height;
	A->CreatePoints();
	return in;
}

#endif