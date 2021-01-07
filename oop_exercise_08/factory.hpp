#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "figure.hpp"
#include "rectangle.hpp"
#include "rhombus.hpp"
#include "trapezoid.hpp"

template <class _FIGURE> // FIGURE = Rectangle<int>
class Factory {

	public:
		
		static _FIGURE* CreatFigure() { return new _FIGURE; }
		
		static _FIGURE* CreatFigureAndEnterIt() {
			_FIGURE* x = CreatFigure();
			std::cin >> x;
			return x;
		}

};

#endif