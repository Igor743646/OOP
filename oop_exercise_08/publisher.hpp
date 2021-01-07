#ifndef PUBLISHER_HPP
#define PUBLISHER_HPP

#include <memory> // shared_ptr
#include <string> // string
#include <fstream> // {i/o}fstream
#include <typeinfo> // typeid
#include <algorithm> // for_each

#include "factory.hpp"

template <class _Return_type, class... _Args_types>
class Publisher {
	using _function = std::function<_Return_type(_Args_types...)>;
	using _functions_vector = std::vector<_function>;

	private:
		_functions_vector _subs;

	public:

		void operator()(_Args_types... param) const {
			for (unsigned int i = 0; i < _subs.size(); ++i) {
				try {
					_subs[i](param...);
				} catch (const char* ex) {
					std::cout << “Error: ” << ex << std::endl;
				}	
			}
		}

		void Add(_function s) {
			_subs.push_back(s);
		}
};

#endif