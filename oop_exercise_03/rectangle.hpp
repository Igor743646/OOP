#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "figure.hpp"

	class Rectangle : public Figure {
		public:
			double width;
			double height;

			Rectangle();
			Rectangle(Point cen, double a, double b);

			void CreatePoints();
			double Area();

			friend std::ostream& operator<< (std::ostream& out, const Rectangle* A);
			friend std::istream& operator>> (std::istream& in, const Rectangle* A);

	};

Rectangle::Rectangle(): Figure(Point(0, 0), 4), width(0), height(0) {
	CreatePoints();
}

Rectangle::Rectangle(Point cen, double a, double b): Figure(cen, 4), width(a), height(b) {
	CreatePoints();
}

void Rectangle::CreatePoints() {
	points = new Point[sizeof(Point) * numberPoints];
	points[0] = center;
	points[1] = Point(center.x + width, center.y);
	points[2] = Point(center.x + width, center.y - height);
	points[3] = Point(center.x, center.y - height);
}

double Rectangle::Area() {
	return width*height;
}

std::ostream& operator<< (std::ostream& out, const Rectangle* A) {
	for (unsigned int i = 0; i<A->numberPoints; ++i) out << A->points[i] << " ";
	return out;
}

std::istream& operator>> (std::istream& in, Rectangle* A) {
	std::cout << "Введите координаты положения прямоугольника: ";
	in >> A->center;
	std::cout << "Введите ширину прямоугольника: ";
	in >> A->width;
	std::cout << "Введите высоту прямоугольника: ";
	in >> A->height;
	A->CreatePoints();
	return in;
}

#endif