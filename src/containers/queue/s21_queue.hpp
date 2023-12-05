#ifndef S21_QUEUE_HPP
#define S21_QUEUE_HPP

#include "../list/s21_list.hpp"

namespace s21 {
template <typename T, class Container = s21::List<T>>
class Queue {
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using container_type = Container;

 public:
  Queue() try : container_(container_type()) {
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    throw;
  }

  Queue(std::initializer_list<value_type> const &items) try
      : container_(container_type(items)) {
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    throw;
  }

  Queue(const Queue &q) try : container_(q.container_) {
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    throw;
  }

  Queue(Queue &&q) try : container_(q.container_) {
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    throw;
  }

  ~Queue() {}

  Queue &operator=(Queue &&q) {
    if (q != *this) swap(q);
    return *this;
  }

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
  void swap(Queue &other) noexcept { container_.swap(other.container_); }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) container_.push_back(arg);
  }

  /*** NON-MEMBER ***/
  friend bool operator==(const Queue &lhs, const Queue &rhs) {
    return lhs.container_ == rhs.container_;
  }

 private:
  container_type container_;
};

}  // namespace s21

#endif
