#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>

	class Point {
		public:
			double x, y;
			Point(): x(0), y(0) {};
			Point(double a, double b): x(a), y(b) {};
			~Point(){};
			Point operator+(Point a);
			Point operator*(double a);
			Point operator/(double a);
			friend std::ostream& operator<< (std::ostream& out, const Point& A); 

	};

Point RandomPoint() {
	srand(static_cast<unsigned int>(time(0))*rand());
	double x, y;
	x = (double)((int)(rand() * 100)%10000)/100;
	y = (double)((int)(rand() * 100)%10000)/100;
	return Point(x, y);
}

Point Point::operator+ (Point a) {
	return Point(x+a.x, y+a.y);
}

Point Point::operator* (double a) {
	return Point(x*a, y*a);
}

Point Point::operator/ (double a) {
	return Point(x/a, y/a);
}

std::ostream& operator<< (std::ostream& out, const Point& A) {
	out << "(" << A.x << ", " << A.y << ")";
	return out;
}

std::istream& operator>> (std::istream& in, Point& A) {
	in >> A.x;
	in >> A.y;
	return in;
}

#endif