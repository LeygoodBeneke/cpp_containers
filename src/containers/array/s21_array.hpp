#ifndef S21_LIST_HPP
#define S21_LIST_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

namespace s21 {
template <typename T, std::size_t N>
struct array {
 public:
  using value_type = T;
  using reference = value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = pointer;
  using const_iterator = const_pointer;

  /* Initialization is implicitly declared */
  array() = default;
  array(const array &) = default;
  array(array &&) = default;
  array(std::initializer_list<value_type> const &items) {
    size_type i = 0;
    for (auto item : items) {
      data[i++] = item;
    }
  }
  array &operator=(const array &) = default;
  array &operator=(array &&) = default;
  ~array() = default;

  constexpr reference at(size_type pos) {
    CheckPos(pos);
    return data[pos];
  }
  constexpr const_reference at(size_type pos) const {
    CheckPos(pos);
    return data[pos];
  }

  reference operator[](size_type pos) { return data[pos]; }

  reference front() { return *begin(); }
  reference back() { return *(data + N - 1); }
  constexpr const_reference front() const { return *begin(); }
  constexpr const_reference back() const { return *(data + N - 1); }

  constexpr iterator data() noexcept { return data; }
  constexpr const_iterator data() const noexcept { return data; }

  iterator begin() noexcept { return data; }
  iterator end() noexcept { return data + N; }
  const_iterator begin() const noexcept { return data; }
  const_iterator end() const noexcept { return data + N; }

  constexpr bool empty() const noexcept { return begin() == end(); }
  constexpr size_type size() const noexcept { return end() - begin(); }
  constexpr size_type max_size() const noexcept { return size(); }

  void swap(array &other) {
    for (size_type i = 0; i < size(); ++i) std::swap(data[i], other.data[i]);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size(); ++i) data[i] = value;
  }

  /*** NON MEMBER ***/
  friend bool operator==(const array<T, N> &lhs, const array<T, N> &rhs) {
    for (size_t i = 0; i < N; ++i) {
      if (lhs.data[i] != rhs.data[i]) {
        return false;
      }
    }
    return true;
  }

  value_type data[N]{};

  /*** UTILS ***/
  void CheckPos(size_type pos) {
    if (pos >= size()) throw std::out_of_range("Invalid position in the array");
  }
};

// partial specialisation for zero-size array
template <typename T>
struct array<T, 0> {
  using value_type = T;
  using reference = value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using iterator = pointer;
  using const_iterator = const_pointer;

  constexpr reference at(size_type pos) {
    std::terminate();
    return data;
  }
  constexpr const_reference at(size_type pos) const {
    std::terminate();
    return data;
  }

  reference operator[](size_type pos) {
    ThrowZero();
    return data;
  }

  reference front() {
    ThrowZero();
    return data;
  }
  reference back() {
    ThrowZero();
    return data;
  }
  constexpr const_reference front() const {
    std::terminate();
    return data;
  }
  constexpr const_reference back() const {
    std::terminate();
    return data;
  }

  constexpr iterator data() noexcept {
    std::terminate();
    return data;
  }
  constexpr const_iterator data() const noexcept { return nullptr; }

  iterator begin() noexcept { return nullptr; }
  iterator end() noexcept { return nullptr; }
  const_iterator begin() const noexcept { return nullptr; }
  const_iterator end() const noexcept { return nullptr; }

  constexpr bool empty() const noexcept { return true; }
  constexpr size_type size() const noexcept { return 0; }
  constexpr size_type max_size() const noexcept { return 0; }

  void swap(array &other) { std::swap(data, other.data); }

  void fill(const_reference value) { ThrowZero(); }

  value_type data[1]{};

  /*** UTILS ***/
  void ThrowZero() {
    throw std::out_of_range("Undefined Behavior: Zero size array");
  }
};

}  // namespace s21

#endif