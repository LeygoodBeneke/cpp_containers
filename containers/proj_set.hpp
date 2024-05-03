#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>

#include "../utilities/rb_tree.hpp"
#include "proj_vector.hpp"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class set {
  class SetIterator;
  class SetConstIterator;

 public:
  using value_type = Key;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using allocator = Allocator;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;

  set() : rb() {}

  set(std::initializer_list<Key> const &items) {
    for (const auto item : items) rb.insert(item, item);
  }

  set(const set &s) : rb(s.rb) {}
  set(set &&s) { rb = std::move(s.rb); }

  ~set() {}

  set &operator=(set s) {
    std::swap(rb, s.rb);
    return *this;
  }

  iterator begin() { return SetIterator(rb.begin()); }
  iterator end() { return SetIterator(rb.end()); }
  const_iterator begin() const { return SetIterator(rb.begin()); }
  const_iterator end() const { return SetIterator(rb.end()); }

  constexpr inline bool empty() const noexcept { return rb.empty(); }
  constexpr inline size_type size() const noexcept { return rb.size(); }
  size_type max_size() const noexcept { return rb.max_size(); }

  void clear() noexcept { rb.clear(); }

  std::pair<iterator, bool> insert(const_reference value) {
    iterator place(rb.searchTree(value));
    bool placed = false;
    if (place == rb.getNullNode()) {
      placed = true;
      rb.insert(value, value);
      place = iterator(rb.searchTree(value));
    }
    return std::pair<iterator, bool>(place, placed);
  }

  std::pair<iterator, bool> insert(value_type &&value) {
    iterator place(rb.searchTree(std::move(value)));
    bool placed = false;
    if (place == rb.getNullNode()) {
      placed = true;
      rb.insert(std::move(value), std::move(value));
      place = iterator(rb.searchTree(std::move(value)));
    }
    return std::pair<iterator, bool>(place, placed);
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...})
      vec.push_back({insert(arg), rb.searchTree(arg) == rb.getNullNode()});
    return vec;
  }

  void erase(iterator pos) { rb.deleteNode(*pos); }
  void erase(iterator &pos) { rb.deleteNode(*pos); }

  void swap(set &other) noexcept { std::swap(rb, other.rb); }

  void merge(set &other) {
    for (iterator it : other) {
      insert(*it);
    }
  }

  iterator find(const_reference key) const {
    return iterator(rb.searchTree(key));
  }

  bool contains(const_reference key) const noexcept {
    return rb.searchTree(key) == rb.getNullNode();
  }

  friend bool operator==(const set &lhs, const set &rhs) noexcept {
    return lhs.rb == rhs.rb;
  }

  friend bool operator!=(const set &lhs, const set &rhs) noexcept {
    return !(lhs == rhs);
  }

 private:
  RedBlackTree<Key, Key, Allocator> rb;
};

template <typename Key, typename Compare, typename Allocator>
class set<Key, Compare, Allocator>::SetIterator {
 public:
  SetIterator() noexcept {}

  SetIterator(const SetIterator &it) noexcept : rb_it(it.rb_it) {}
  SetIterator(SetIterator &&it) noexcept : rb_it(std::move(it.rb_it)) {}

  SetIterator(const typename RedBlackTree<Key>::iterator &it) noexcept
      : rb_it(it) {}
  SetIterator(typename RedBlackTree<Key>::iterator &&it) noexcept
      : rb_it(std::move(it)) {}
  ~SetIterator() {}

  SetIterator &operator=(const SetIterator &other) {
    if (&other != this) {
      rb_it = other.rb_it;
    }
    return *this;
  }

  friend bool operator==(const SetIterator &lhs,
                         const SetIterator &rhs) noexcept {
    return lhs.rb_it == rhs.rb_it;
  }

  friend bool operator!=(const SetIterator &lhs,
                         const SetIterator &rhs) noexcept {
    return lhs.rb_it != rhs.rb_it;
  }

  reference operator*() noexcept { return (*rb_it)->value; }

  SetIterator &operator++() noexcept {
    rb_it++;
    return *this;
  }
  SetIterator &operator--() noexcept {
    rb_it--;
    return *this;
  }

  SetIterator operator++(int) noexcept {
    SetIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  SetIterator operator--(int) noexcept {
    SetIterator tmp(*this);
    --(*this);
    return tmp;
  }

  SetIterator &operator+=(const size_type n) {
    for (size_t i = 0; i < n; i++) ++(*this);
    return *this;
  }

  SetIterator &operator-=(const size_type n) {
    for (auto i = 0; i < n; i++) --(*this);
    return *this;
  }

  friend bool operator==(SetIterator &lhs, SetIterator &rhs) {
    return *lhs == *rhs;
  }

 private:
  typename RedBlackTree<Key>::iterator rb_it;
};

template <typename Key, typename Compare, typename Allocator>
class set<Key, Compare, Allocator>::SetConstIterator {
 public:
  SetConstIterator() noexcept {}

  SetConstIterator(const SetConstIterator &it) noexcept : rb_it(it.rb_it) {}
  SetConstIterator(SetConstIterator &&it) noexcept
      : rb_it(std::move(it.rb_it)) {}

  SetConstIterator(
      const typename RedBlackTree<Key>::const_iterator &it) noexcept
      : rb_it(it) {}
  SetConstIterator(typename RedBlackTree<Key>::const_iterator &&it) noexcept
      : rb_it(std::move(it)) {}
  ~SetConstIterator() {}

  SetConstIterator &operator=(const SetConstIterator &other) {
    if (&other != this) {
      rb_it = other.rb_it;
    }
    return *this;
  }

  friend bool operator==(const SetConstIterator &lhs,
                         const SetConstIterator &rhs) noexcept {
    return lhs.rb_it == rhs.rb_it;
  }

  friend bool operator!=(const SetConstIterator &lhs,
                         const SetConstIterator &rhs) noexcept {
    return lhs.rb_it != rhs.rb_it;
  }

  reference operator*() noexcept { return (*rb_it)->value; }

  SetConstIterator &operator++() noexcept {
    rb_it++;
    return *this;
  }
  SetConstIterator &operator--() noexcept {
    rb_it--;
    return *this;
  }

  SetConstIterator operator++(int) noexcept {
    SetConstIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  SetConstIterator operator--(int) noexcept {
    SetConstIterator tmp(*this);
    --(*this);
    return tmp;
  }

  SetConstIterator &operator+=(const size_type n) {
    for (size_t i = 0; i < n; i++) ++(*this);
    return *this;
  }

  SetConstIterator &operator-=(const size_type n) {
    for (auto i = 0; i < n; i++) --(*this);
    return *this;
  }

  friend bool operator==(SetConstIterator &lhs, SetConstIterator &rhs) {
    return *lhs == *rhs;
  }

 private:
  typename RedBlackTree<Key>::const_iterator rb_it;
};

}  // namespace s21
#endif
