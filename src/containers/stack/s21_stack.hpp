#ifndef S21_STACK_HPP
#define S21_STACK_HPP

// #include <cstddef>
// #include <initializer_list>
// #include <iostream>
// #include <iterator>
// #include <limits>
// #include <memory>

#include "../list/s21_list.hpp"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;

 public:
  stack() : obj_(Container()) {}
  stack(std::initializer_list<value_type> const &items)
      : obj_(Container(items)) {}
  stack(const stack &s) : obj_(Container(s.obj_)) {}
  stack(stack &&s) : obj_(Container(s.obj_)) {}
  ~stack() {}

  stack operator=(stack &&s) {
    if (s != *this) swap(s);
    return *this;
  }

  reference top() { return obj_.back(); }
  const_reference top() const { return obj_.back(); }

  bool empty() const { return obj_.empty(); }
  size_type size() const { return obj_.size(); }

  void push(const_reference value) { obj_.push_back(value); }
  void pop() { obj_.pop_back(); }
  void swap(stack &other) noexcept { obj_.swap(other.obj_); }

  /*** NON-MEMBER ***/
  friend bool operator==(const stack &lhs, const stack &rhs) {
    return lhs.obj_ == rhs.obj_;
  }

 private:
  Container obj_;
};

}  // namespace s21

#endif