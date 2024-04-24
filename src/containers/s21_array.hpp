#ifndef S21_ARRAY_HPP
#define S21_ARRAY_HPP

#include <initializer_list>
#include <iterator>

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
      data_[i++] = item;
    }
  }

  ~array() = default;
  array &operator=(const array &) = default;
  array &operator=(array &&) = default;

  constexpr reference at(size_type pos) {
    if (pos >= size()) throw std::out_of_range("Invalid position in the array");
    return data_[pos];
  }
  constexpr const_reference at(size_type pos) const {
    if (pos >= size()) throw std::out_of_range("Invalid position in the array");
    return data_[pos];
  }

  reference operator[](size_type pos) { return data_[pos]; }

  reference front() { return *begin(); }
  reference back() { return *(data_ + N - 1); }
  constexpr const_reference front() const { return *begin(); }
  constexpr const_reference back() const { return *(data_ + N - 1); }

  constexpr iterator data() noexcept { return data_; }
  constexpr const_iterator data() const noexcept { return data_; }

  iterator begin() noexcept { return data_; }
  iterator end() noexcept { return data_ + N; }
  const_iterator begin() const noexcept { return data_; }
  const_iterator end() const noexcept { return data_ + N; }

  constexpr bool empty() const noexcept { return begin() == end(); }
  constexpr size_type size() const noexcept { return end() - begin(); }
  constexpr size_type max_size() const noexcept { return size(); }

  void swap(array &other) {
    for (size_type i = 0; i < size(); ++i) std::swap(data_[i], other.data_[i]);
  }

  void fill(const_reference value) {
    for (size_type i = 0; i < size(); ++i) data_[i] = value;
  }

  /*** NON MEMBER ***/
  friend bool operator==(const array<T, N> &lhs, const array<T, N> &rhs) {
    for (size_t i = 0; i < N; ++i) {
      if (lhs.data_[i] != rhs.data_[i]) {
        return false;
      }
    }
    return true;
  }

 private:
  value_type data_[N]{};
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
    return data_;
  }
  constexpr const_reference at(size_type pos) const {
    std::terminate();
    return data_;
  }

  reference operator[](size_type pos) {
    throw_zero();
    return data_;
  }

  reference front() {
    throw_zero();
    return data_;
  }
  reference back() {
    throw_zero();
    return data_;
  }
  constexpr const_reference front() const {
    std::terminate();
    return data_;
  }
  constexpr const_reference back() const {
    std::terminate();
    return data_;
  }

  constexpr iterator data() noexcept {
    std::terminate();
    return data_;
  }
  constexpr const_iterator data() const noexcept { return nullptr; }

  iterator begin() noexcept { return nullptr; }
  iterator end() noexcept { return nullptr; }
  const_iterator begin() const noexcept { return nullptr; }
  const_iterator end() const noexcept { return nullptr; }

  constexpr bool empty() const noexcept { return true; }
  constexpr size_type size() const noexcept { return 0; }
  constexpr size_type max_size() const noexcept { return 0; }

  void swap(array &other) { std::swap(data_, other.data_); }

  void fill(const_reference value) { throw_zero(); }

 private:
  value_type data_[1]{};

  /*** UTILS ***/
  void throw_zero() {
    throw std::out_of_range("Undefined Behavior: Zero size array");
  }
};

}  // namespace s21

#endif
