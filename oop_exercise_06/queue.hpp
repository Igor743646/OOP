//Глушатов Игорь. Реализация очереди с итератором и аллокатором. ЛР №6

#include <iostream>
#include <stack>
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

template<class T, size_t COUNT_OF_BLOCKS>
struct Allocator {
	
	std::stack<T*> _buffer;
	T* all;

	using value_type = T;
	using pointer = T*;
	using const_pointer = const T*;
	using size_type = std::size_t;

	Allocator(): _buffer{} {
		static_assert(COUNT_OF_BLOCKS>0);
	}

	~Allocator() {
		delete []all;
	}

	template<class U>
	struct rebind {
		using other = Allocator<U, COUNT_OF_BLOCKS>;
	};

	T *allocate(size_t n) {
		if (_buffer.empty()) {
			
			all = new value_type[sizeof(value_type)*COUNT_OF_BLOCKS];
			for (size_t i=0; i<COUNT_OF_BLOCKS; ++i) {
				_buffer.push(&all[COUNT_OF_BLOCKS-i-1]);
			}
		}

		if (_buffer.size() < n) throw std::bad_alloc();
		T* pointer = _buffer.top();
		for (size_t i=0; i<n; ++i) _buffer.pop();

		return pointer;
	}

	template<class U, class ...Args>
	void constract(U* p, Args &&...args) {
		new (p) U(std::forward<Args>(args)...);
	}

	void deallocate(T* p, size_t n) {
		for (size_t i=0; i<n; ++i) {
			p[i] = 0;
		}
	}

	void destroy(T* p) {
		p->~T();
	}

};

template <class T, class ALLOCATOR>
struct Queue {

	using figure = T;
	using iterator = Queue_iterator<T>;
	using value_type = unique_ptr<T>;
	using pointer = unique_ptr<T>*;
	using allocator_type = typename ALLOCATOR::template rebind<value_type>::other;

	unsigned int size;
	unsigned int buffer;
	pointer queue;
	

	Queue(): size(0), buffer(0), queue(NULL) {}
	~Queue() {
	}

	static allocator_type& get_allocator() {
		static allocator_type allocator;
		return allocator;
	}

	bool Empty() {
		return size==0;
	}

	void Push(T elem) {
		if (buffer == 0) {
			queue = new (get_allocator().allocate(sizeof(value_type))) value_type;
			buffer = 1;
		}
		if (size == buffer) {

			value_type *temp = new (get_allocator().allocate(sizeof(value_type)*(buffer*2))) value_type[(buffer*2)];

			buffer<<=1;
			for (unsigned int i = 0; i < size; ++i) {
				temp[i] = move(queue[i]);
			}
			queue = temp;
		}

		queue[size] = move(std::make_unique<T>(elem));
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
			value_type *temp = new (get_allocator().allocate(sizeof(value_type)*(buffer/2))) value_type[(buffer/2)];
			buffer>>=1;
			for (unsigned int i = 0; i < size; ++i) {
				temp[i] = move(queue[i]);
			}
			queue = temp;
		}
	}

	void Remove(unsigned int id) {
		if (id >= size) throw "Индекс больше размера очереди!";
		for (unsigned int i=0; i<id; ++i) {
			value_type s = Top();
			Pop();
			Push(*s);
		}
		Pop();
		for (unsigned int i = 0; i < size - id; ++i) {
			Push(*Top());
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