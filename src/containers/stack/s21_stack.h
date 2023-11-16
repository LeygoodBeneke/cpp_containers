#ifndef S21_STACK_H
#define S21_STACK_H

#include "../../utilities/rb_tree.h"

namespace s21 {

template <typename T>
class stack {
 public:
  stack() : data(new T[128]()) {}
  stack(unsigned size) : data(new T[size]) {}

  ~stack() { delete[] data; }

  inline unsigned size() const noexcept { return _size; }
  inline bool empty() const noexcept { return _size == 0; }
  inline T top() noexcept { return data[_size - 1]; }
  inline T& top() const noexcept { return data[_size - 1]; }

  void push(const T& value);
  void push(T&& value);

  inline void pop() noexcept { _size--; }

 private:
  inline T* begin() const noexcept { return data; }
  inline T* end() const noexcept { return data + _size; }

  T* data;
  unsigned _size;
  unsigned capacity;
};
}  // namespace s21
#endif
