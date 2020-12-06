#include <tuple>
#include <iostream>

template <class T>
struct Rectangle {
    std::pair<T,T> point;
    T hight, width;
    Rectangle (T x, T y, T h, T w): point(x, y), hight(h), width(w) {}
};

template <class T>
struct Rhombus {
    std::pair<T,T> point;
    T diagonal1, diagonal2;
    Rhombus (T x, T y, T w, T h): point(x, y), diagonal1(w), diagonal2(h) {}
};

template <class T>
struct Trapezoid {
    std::pair<T,T> point;
    T base1, base2, hight;
    Trapezoid (T x, T y, T b1, T b2, T h): point(x, y), base1(b1), base2(b2), hight(h) {}
};

template <class T, size_t index>
typename std::enable_if<index>=std::tuple_size<T>::value, void>::type print(T) {
    std::cout << std::endl;
}

template <class T, size_t index>
typename std::enable_if<index<std::tuple_size<T>::value, void>::type print(T tuple) {
    print(std::get<index>(tuple));
    print<T, index+1>(tuple);
}

template <class T, size_t index>
typename std::enable_if<index>=std::tuple_size<T>::value, long double>::type square(T) {
    return 0;
}

template <class T, size_t index>
typename std::enable_if<index<std::tuple_size<T>::value, long double>::type square(T tuple) {
    return square(std::get<index>(tuple)) + square<T, index+1>(tuple);
}

template <class T>
void print(Rectangle<T> a) {
    std::cout << "Точки прямоугольника: " << "(" << a.point.first << ", " << a.point.second << ") " 
        << "(" << a.point.first+a.width << ", " << a.point.second << ") " 
        << "(" << a.point.first+a.width << ", " << a.point.second-a.hight << ") " 
        << "(" << a.point.first<< ", " << a.point.second-a.hight << ") " 
        << std::endl;
}

template <class T>
long double square(Rectangle<T> a) {
    return a.hight*a.width;
}

template <class T>
void print(Rhombus<T> a) {
    std::cout << "Точки ромба: " << "(" << a.point.first+a.diagonal1/2 << ", " << a.point.second << ") " 
        << "(" << a.point.first+a.diagonal1 << ", " << a.point.second-a.diagonal2/2 << ") "
        << "(" << a.point.first+a.diagonal1/2 << ", " << a.point.second-a.diagonal2 << ") "
        << "(" << a.point.first << ", " << a.point.second-a.diagonal2/2 << ") "
        << std::endl;
}

template <class T>
long double square(Rhombus<T> a) {
    return a.diagonal1*a.diagonal2/2;
}

template <class T>
void print(Trapezoid<T> a) {
    std::cout << "Точки трапеции: " << "(" << a.point.first+(a.base2-a.base1)/2 << ", " << a.point.second << ") " 
        << "(" << a.point.first+a.base2-(a.base2-a.base1)/2 << ", " << a.point.second << ") "
        << "(" << a.point.first+a.base2 << ", " << a.point.second-a.hight << ") "
        << "(" << a.point.first << ", " << a.point.second-a.hight << ") "
        << std::endl;
}

template <class T>
long double square(Trapezoid<T> a) {
    return a.hight*((a.base1+a.base2)/2);
}

int main() {

    // Кортеж 1
    std::tuple tuple(Rectangle<int>(1,1,5,10), Rectangle<int>(15,1,50,10), Rhombus<double>(5, 5, 10, 5.5), Trapezoid<int>(50, 50, 10, 20, 5));

    // Кортеж 2
    Rhombus<int> romb {20, 5, 10, 50};
    Rectangle<int> pryam {20, 5, 40, 50};
    Trapezoid<int> trap {20, 5, 30, 50, 10};
    std::tuple tuple2(romb, pryam, trap);

    // Кортеж 3, как объединение первого, элемента прямоугольника и второго кортежа
    auto tuple3 = std::tuple_cat(tuple, std::make_tuple(Rectangle<float>(0, 0, 5, 5)), tuple2);

    print<decltype(tuple), 0>(tuple);
    std::cout << "Суммарная площадь фигур: " << square<decltype(tuple), 0>(tuple) << std::endl;

    print<decltype(tuple2), 0>(tuple2);
    std::cout << "Суммарная площадь фигур: " << square<decltype(tuple2), 0>(tuple2) << std::endl;

    print<decltype(tuple3), 0>(tuple3);
    std::cout << "Суммарная площадь фигур: " << square<decltype(tuple3), 0>(tuple3) << std::endl;

    return 0;
}