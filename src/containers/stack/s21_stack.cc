#include "s21_stack.h"

#include <iostream>

template <typename T>
void s21::stack<T>::push(const T& value) {
    data[_size++] = value;
}

template <typename T>
void s21::stack<T>::push(T&& value) {
    std::swap(data[_size++], value);
}
