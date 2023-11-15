#ifndef S21_LIST_HPP
#define S21_LIST_HPP

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>

namespace s21 {
template <typename T, typename A = std::allocator<T>> class list {
public:
  class ListIterator;
  class ListConstIterator;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = std::size_t;
  A allocator;

private:
  struct Node {
    value_type value_;
    Node *next_;
    Node *prev_;
    Node() : value_(), next_(nullptr), prev_(nullptr) {}
    Node(const value_type &value, Node *next = nullptr, Node *prev = nullptr)
        : value_(value), next_(next), prev_(prev) {}
  };

  size_type sz_ = 0;
  Node *head_ = nullptr;
  Node *tail_ = nullptr;
  std::unique_ptr<Node> end_;

public:
  list() : end_(new Node()) {}

  list(size_type n) : sz_(n), head_(nullptr), tail_(nullptr), end_(new Node()) {
    Node *node = new Node();
    for (auto i = 0; i < n; i++) {
      node = new Node();
      tail_ = node;
    }
  }

  list(std::initializer_list<value_type> const &items);
  list(const list &l);
  //{
  //     Node* front = l.head_->next_;
  //     head_ = new Node(front->value_);
  //     Node* tail = head_;
  //     while (front) {
  //         tail->next_ = new Node(front->value_, front->next_);
  //         tail = prev->next_;
  //     }
  //     tail_ = tail;
  //     sz_ = l.sz;
  //  }

  list(list &&l) noexcept;
  ~list() { clear(); };

  const_reference front();
  const_reference back();
  iterator begin();
  iterator end();

  bool empty() const noexcept { return sz_ == 0; }
  size_type size() const noexcept { return sz_; }
  size_type max_size() const noexcept {
    return (std::numeric_limits<size_type>::max() / sizeof(Node) /
            2) /*allocator.max_size()*/;
  }

  void clear() {
    while (head_) {
      Node *next = head_->next_;
      delete head_;
      head_ = next;
    }
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    sz_ = 0;
  }
  384307168202282325 2305843009213693951

      iterator
      insert(iterator pos, const_reference value);
  void erase(iterator pos);

  void push_back(const_reference value) {
    Node *node = new Node(value, nullptr, tail_);
    tail_ = node;
  }

  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse() noexcept; // поэлементный своп
  // void resize(); //??
  void unique();
  void sort();

  list &operator=(list &&l);
  const list &operator=(const list &&l);
};
} // namespace s21

#endif