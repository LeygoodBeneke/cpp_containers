#ifndef S21_MULTISET_H
#define S21_MULTISET_H

#include <initializer_list>

#include "../utilities/rb_tree.h"
#include "s21_vector.hpp"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class multiset {
  class MultisetIterator;
  class MultisetConstIterator;

 public:
  using value_type = Key;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using allocator = Allocator;
  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;

  multiset() : rb() {}

  multiset(std::initializer_list<Key> const &items) {
    for (const auto item : items) rb.insert(item, item);
  }

  multiset(const multiset &s) : rb(s.rb) {}
  multiset(multiset &&s) { rb = std::move(s.rb); }

  ~multiset() {}

  multiset &operator=(multiset s) {
    std::swap(rb, s.rb);
    return *this;
  }

  iterator begin() { return MultisetIterator(rb.begin()); }
  iterator end() { return MultisetIterator(rb.end()); }
  const_iterator begin() const { return MultisetIterator(rb.begin()); }
  const_iterator end() const { return MultisetIterator(rb.end()); }

  constexpr inline bool empty() const noexcept { return rb.empty(); }
  constexpr inline size_type size() const noexcept { return rb.size(); }
  size_type max_size() const noexcept { return rb.max_size(); }

  void clear() noexcept { rb.clear(); }

  std::pair<iterator, bool> insert(const_reference value) {
    iterator place(rb.searchTree(value));
    bool placed = false;
    if (place == rb.getNullNode()) {
      placed = true;
    }
    rb.insert(value, value);
    place = iterator(rb.searchTree(value));
    return std::pair<iterator, bool>(place, placed);
  }

  std::pair<iterator, bool> insert(value_type &&value) {
    iterator place(rb.searchTree(std::move(value)));
    bool placed = false;
    if (place == rb.getNullNode()) {
      placed = true;
    }
    rb.insert(std::move(value), std::move(value));
    place = iterator(rb.searchTree(std::move(value)));
    return std::pair<iterator, bool>(place, placed);
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...}) vec.push_back(insert(arg, arg));
    return vec;
  }

  void erase(iterator pos) { rb.deleteNode(*pos); }

  void swap(multiset &other) noexcept { std::swap(rb, other.rb); }

  void merge(multiset &other) {
    for (iterator it : other) {
      insert(*it);
    }
  }

  iterator find(const_reference key) { return rb.searchTree(key); }

  bool contains(const_reference key) const noexcept {
    return rb.searchTree(key) == rb.getNullNode();
  }

  friend bool operator==(const multiset &lhs, const multiset &rhs) noexcept {
    return lhs.rb == rhs.rb;
  }

  friend bool operator!=(
      const multiset<Key, Compare, Allocator> &lhs,
      const s21::multiset<Key, Compare, Allocator> &rhs) noexcept {
    return !(lhs == rhs);
  }

  friend bool operator==(const std::pair<Key, Key> &lhs,
                         const std::pair<Key, Key> &rhs) {
    return lhs.first == rhs.first && lhs.second == rhs.second;
  }

 private:
  RedBlackTree<Key, Key, Allocator> rb;
};

template <typename Key, typename Compare, typename Allocator>
class multiset<Key, Compare, Allocator>::MultisetIterator {
 public:
  MultisetIterator() noexcept {}

  MultisetIterator(const MultisetIterator &it) noexcept : rb_it(it.rb_it) {}
  MultisetIterator(MultisetIterator &&it) noexcept
      : rb_it(std::move(it.rb_it)) {}

  MultisetIterator(const typename RedBlackTree<Key>::iterator &it) noexcept
      : rb_it(it) {}
  MultisetIterator(typename RedBlackTree<Key>::iterator &&it) noexcept
      : rb_it(std::move(it)) {}
  ~MultisetIterator() {}

  MultisetIterator &operator=(const MultisetIterator &other) {
    if (&other != this) {
      rb_it = other.rb_it;
    }
    return *this;
  }

  friend bool operator==(const MultisetIterator &lhs,
                         const MultisetIterator &rhs) noexcept {
    return lhs.rb_it == rhs.rb_it;
  }

  friend bool operator!=(const MultisetIterator &lhs,
                         const MultisetIterator &rhs) noexcept {
    return lhs.rb_it != rhs.rb_it;
  }

  reference operator*() noexcept { return (*rb_it)->value; }

  MultisetIterator &operator++() noexcept {
    rb_it++;
    return *this;
  }
  MultisetIterator &operator--() noexcept {
    rb_it--;
    return *this;
  }

  MultisetIterator operator++(int) noexcept {
    MultisetIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  MultisetIterator operator--(int) noexcept {
    MultisetIterator tmp(*this);
    --(*this);
    return tmp;
  }

  MultisetIterator &operator+=(const size_type n) {
    for (size_t i = 0; i < n; i++) ++(*this);
    return *this;
  }

  MultisetIterator &operator-=(const size_type n) {
    for (auto i = 0; i < n; i++) --(*this);
    return *this;
  }

  friend bool operator==(MultisetIterator &lhs, MultisetIterator &rhs) {
    return *lhs == *rhs;
  }

 private:
  typename RedBlackTree<Key>::iterator rb_it;
};

template <typename Key, typename Compare, typename Allocator>
class multiset<Key, Compare, Allocator>::MultisetConstIterator {
 public:
  MultisetConstIterator() noexcept {}

  MultisetConstIterator(const MultisetConstIterator &it) noexcept
      : rb_it(it.rb_it) {}
  MultisetConstIterator(MultisetConstIterator &&it) noexcept
      : rb_it(std::move(it.rb_it)) {}

  MultisetConstIterator(
      const typename RedBlackTree<Key>::const_iterator &it) noexcept
      : rb_it(it) {}
  MultisetConstIterator(
      typename RedBlackTree<Key>::const_iterator &&it) noexcept
      : rb_it(std::move(it)) {}
  ~MultisetConstIterator() {}

  MultisetConstIterator &operator=(const MultisetConstIterator &other) {
    if (&other != this) {
      rb_it = other.rb_it;
    }
    return *this;
  }

  friend bool operator==(const MultisetConstIterator &lhs,
                         const MultisetConstIterator &rhs) noexcept {
    return lhs.rb_it == rhs.rb_it;
  }

  friend bool operator!=(const MultisetConstIterator &lhs,
                         const MultisetConstIterator &rhs) noexcept {
    return lhs.rb_it != rhs.rb_it;
  }

  reference operator*() noexcept { return (*rb_it)->value; }

  MultisetConstIterator &operator++() noexcept {
    rb_it++;
    return *this;
  }
  MultisetConstIterator &operator--() noexcept {
    rb_it--;
    return *this;
  }

  MultisetConstIterator operator++(int) noexcept {
    MultisetConstIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  MultisetConstIterator operator--(int) noexcept {
    MultisetConstIterator tmp(*this);
    --(*this);
    return tmp;
  }

  MultisetConstIterator &operator+=(const size_type n) {
    for (size_t i = 0; i < n; i++) ++(*this);
    return *this;
  }

  MultisetConstIterator &operator-=(const size_type n) {
    for (auto i = 0; i < n; i++) --(*this);
    return *this;
  }

  friend bool operator==(MultisetConstIterator &lhs,
                         MultisetConstIterator &rhs) {
    return *lhs == *rhs;
  }

 private:
  typename RedBlackTree<Key>::const_iterator rb_it;
};

}  // namespace s21
#endif
