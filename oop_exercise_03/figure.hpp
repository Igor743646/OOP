#ifndef FIGURE_HPP
#define FIGURE_HPP

#include "point.hpp"

	class Figure {
		public:
			Figure(): center(Point()), numberPoints(0) {};
			Figure(Point cen, unsigned int num);
			~Figure();
			Point center;
			unsigned int numberPoints;
			Point *points;
			
			Point GeometricCenter();
			virtual void CreatePoints();
			virtual double Area();
			friend std::ostream& operator<< (std::ostream& out, const Figure* A);
			friend std::istream& operator>> (std::istream& in, const Figure* A);
	};

Figure::Figure(Point cen, unsigned int num): center(cen), numberPoints(num) {
	CreatePoints();
}

Figure::~Figure() {
	numberPoints = 0;
	delete[] points;
}

Point Figure::GeometricCenter() {
	Point res(0, 0);
	for (unsigned int i=0; i<numberPoints; ++i) {
		res = res + points[i]/numberPoints;
	}
	return res;
}

void Figure::CreatePoints() {
	points = new Point[sizeof(Point) * numberPoints];
	for (unsigned int i = 0; i<numberPoints; ++i) points[i] = center + RandomPoint();
}

double Figure::Area() {
	throw "Non-member object";
}

std::ostream& operator<< (std::ostream& out, const Figure* A) {
	out << "Точки: ";
	for (unsigned int i = 0; i<A->numberPoints; ++i) out << A->points[i] << " ";
	out << "\n";
	return out;
}

std::istream& operator>> (std::istream& in, Figure* A) {
	in >> A->center;
	in >> A->numberPoints;
	A->CreatePoints();
	return in;
}

#endif