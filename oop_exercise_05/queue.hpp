#include <iostream>
#include <memory> // unique_ptr
#pragma once
using namespace std;

template <class T>
struct Queue_iterator {
	
	using figure = T;
	using iterator_category = forward_iterator_tag;
	using value_type = unique_ptr<T>;
	using pointer = unique_ptr<T>*;
	using reference = unique_ptr<T>&;
	using difference_type = unsigned int;

	pointer it;

	Queue_iterator(){}
	Queue_iterator(pointer queue): it(queue) {}

	void next() {
		it+=1;
	}

	reference operator*() {
		return *it;
	}

	Queue_iterator<figure>& operator++() {
		it+=1;
		return *this;
	}

	Queue_iterator<figure>& operator+(int a) {
		it+=a;
		return *this;
	}

	Queue_iterator<figure>& operator-(int a) {
		it-=a;
		return *this;
	}

	bool operator!=(const Queue_iterator& rvl) {
		return it != rvl.it;
	}

};

template <class T>
struct Queue {

	using figure = T;
	using iterator = Queue_iterator<T>;
	using value_type = unique_ptr<T>;
	using pointer = unique_ptr<T>*;

	unsigned int size;
	unsigned int buffer;
	pointer queue;

	Queue(): size(0), buffer(0), queue(NULL) {}
	~Queue() {
		delete []queue;
	}

	void Push(value_type elem) {
		if (buffer == 0) {
			queue = new value_type[1];
			buffer = 1;
		}
		if (size == buffer) {
			value_type *temp = new value_type[buffer << 1];
			buffer<<=1;
			for (unsigned int i = 0; i < size; ++i) {
				temp[i] = move(queue[i]);
			}
			delete []queue;
			queue = temp;
		}
		queue[size] = move(elem);
		++size;
	}

	void Pop() {
		if (size==0) return;
		if (size>1) {
			for (unsigned int i = 0; i < size-1; ++i) {
				queue[i] = move(queue[i+1]);
			}
		}
		--size;
		if (size*2 < buffer) {
			value_type *temp = new value_type[buffer >> 1];
			buffer>>=1;
			for (unsigned int i = 0; i < size; ++i) {
				temp[i] = move(queue[i]);
			}
			delete []queue;
			queue = temp;
		}
	}

	void Remove(unsigned int id) {
		if (id >= size) throw "Индекс больше размера очереди!";
		for (unsigned int i=0; i<id; ++i) {
			value_type s = Top();
			Pop();
			Push(move(s));
		}
		Pop();
		for (unsigned int i = 0; i < size - id; ++i) {
			Push(Top());
			Pop();
		}
	}

	value_type Top() {
		if (size>0) {
			return make_unique<figure>(*queue[0]);
		} else {
			throw "Очередь пуста!";
		}
	}

	void insert(iterator it, value_type elem) {
		*it = elem;
	}

	void erase(iterator it) {
		while (it+1 != end()) {
			*it = *(it+1);
			it++;
		}
		size--;
	}

	iterator begin() {
		return iterator(queue);
	}

	iterator end() {
		return iterator(queue + size);
	}
};