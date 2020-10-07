#ifndef RHOMBUS_HPP
#define RHOMBUS_HPP

#include "figure.hpp"

	class Rhombus : public Figure {
		public:
			double width;
			double height;

			Rhombus();
			Rhombus(Point cen, double a, double b);

			void CreatePoints();
			double Area();

			friend std::ostream& operator<< (std::ostream& out, const Rhombus* A);
			friend std::istream& operator>> (std::istream& in, const Rhombus* A);

	};

Rhombus::Rhombus(): Figure(Point(0, 0), 4), width(0), height(0) {
	CreatePoints();
}

Rhombus::Rhombus(Point cen, double a, double b): Figure(cen, 4), width(a), height(b) {
	CreatePoints();
}

void Rhombus::CreatePoints() {
	points = new Point[sizeof(Point) * numberPoints];
	points[0] = Point(center.x, center.y - height/2);
	points[1] = Point(center.x + width/2, center.y);
	points[2] = Point(center.x + width, center.y - height/2);
	points[3] = Point(center.x + width/2, center.y - height);
}

double Rhombus::Area() {
	return width*height/2;
}

std::ostream& operator<< (std::ostream& out, const Rhombus* A) {
	out << "Точки: ";
	for (unsigned int i = 0; i<A->numberPoints; ++i) out << A->points[i] << " ";
	out << "\n";
	return out;
}

std::istream& operator>> (std::istream& in, Rhombus* A) {
	std::cout << "Введите координаты положения ромба: ";
	in >> A->center;
	std::cout << "Введите ширину ромба: ";
	in >> A->width;
	std::cout << "Введите высоту ромба: ";
	in >> A->height;
	A->CreatePoints();
	return in;
}

#endif