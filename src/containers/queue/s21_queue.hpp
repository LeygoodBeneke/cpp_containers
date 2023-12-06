#ifndef S21_QUEUE_HPP
#define S21_QUEUE_HPP

#include "../list/s21_list.hpp"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using container_type = Container;

 public:
  queue() : container_(container_type()) {}
  queue(std::initializer_list<value_type> const &items)
      : container_(container_type(items)) {}
  queue(const queue &q) : container_(q.container_) {}
  explicit queue(queue &&q) : container_(q.container_) {}
  queue &operator=(queue &&q) {
    if (q != *this) swap(q);
    return *this;
  }
  ~queue() {}

  reference front() { return container_.front(); }
  const_reference front() const { return container_.front(); }
  reference back() { return container_.back(); }
  const_reference back() const { return container_.back(); }

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

  void pop() { container_.pop_front(); }
  void swap(queue &other) noexcept { container_.swap(other.container_); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) container_.push_back(arg);
  }

  /*** NON-MEMBER ***/
  friend bool operator==(const queue &lhs, const queue &rhs) {
    return lhs.container_ == rhs.container_;
  }

 private:
  container_type container_;
};

}  // namespace s21

#endif
