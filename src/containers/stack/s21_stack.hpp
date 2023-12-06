#ifndef S21_STACK_HPP
#define S21_STACK_HPP

#include "../list/s21_list.hpp"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class stack {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using container_type = Container;

 public:
  stack() : container_(container_type()) {}
  stack(std::initializer_list<value_type> const &items)
      : container_(container_type(items)) {}
  stack(const stack &s) : container_(container_type(s.container_)) {}
  stack(stack &&s) : container_(container_type()) { swap(s); }
  stack &operator=(stack &&s) {
    if (s != *this) swap(s);
    return *this;
  }
  ~stack() {}

  reference top() { return container_.back(); }
  const_reference top() const { return container_.back(); }

  bool empty() const { return container_.empty(); }
  size_type size() const { return container_.size(); }

  void push(const_reference value) {
    try {
      container_.push_back(value);
    } catch (std::bad_alloc &t) {
      std::cerr << t.what() << std::endl;
      throw;
    }
  }

  void pop() { container_.pop_back(); }
  void swap(stack &other) noexcept { container_.swap(other.container_); }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    typename s21::list<T>::ListIterator it = container_.begin();
    for (const auto &arg : {args...}) container_.insert(it, arg);
  }

  /*** NON-MEMBER ***/
  friend bool operator==(const stack &lhs, const stack &rhs) {
    return lhs.container_ == rhs.container_;
  }

 private:
  container_type container_;
};

}  // namespace s21

#endif