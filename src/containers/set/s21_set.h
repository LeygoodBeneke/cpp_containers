#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>
#include <iostream>
#include <iterator>

#include "../../utilities/rb_tree.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class set {
 public:
  using value_type = Key;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using allocator = Allocator;
  using iterator = typename RedBlackTree<Key>::RedBlackTreeIterator;
  using const_iterator = const iterator;

  set() : rb(), _size(0) {}

  set(std::initializer_list<Key> const &items) {
    for (const auto item : items) {
      insert(item);
    }
  }

  set(const set &s) {
    for (iterator it : s) {
      insert(*it);
    }
  }

  set(set &&s) {
    rb = std::move(s.rb);
    _size = std::move(s._size);
    alloc = std::move(s.alloc);
  }

  ~set() {}

  set operator=(set &&s) {
    clear();
    alloc = std::move(s.alloc);
    rb = std::move(s.rb);
    _size = std::move(s._size);
  }

  iterator begin() {
    iterator it(rb.minimum(rb.getRoot()));
    return it;
  }

  iterator end() {
    iterator it(rb.maximum(rb.getRoot()));
    it++;
    return it;
  }

  constexpr inline bool empty() const noexcept { return _size == 0; }
  constexpr inline size_type size() const noexcept { return _size; }
  size_type max_size() const noexcept { return alloc.max_size(); }

  void clear() noexcept { rb.deleteNode(rb.getRoot()->value); }

  std::pair<iterator, bool> insert(value_type value) {
    iterator place(*rb.searchTree(value));
    bool placed = false;
    if (place == rb.getNullNode()) {
      placed = true;
      rb.insert(value);
      _size++;
      iterator new_place(*rb.searchTree(value));
      place = new_place;
    }
    return std::pair<iterator, bool>(place, placed);
  }

  void erase(iterator pos) {
    value_type value = *pos;
    rb.deleteNode(value);
    --_size;
  }

  void swap(set &other) noexcept {
    std::swap(alloc, other.alloc);
    std::swap(rb, other.rb);
    std::swap(_size, other._size);
  }

  void merge(set &other) {
    for (iterator it : other) {
      insert(it.data);
    }
  }

  iterator find(const Key &key) { return rb.searchTree(key); }

  bool contains(const Key &key) const noexcept {
    return rb.searchTree(key) == nullptr;
  }

 private:
  RedBlackTree<Key> rb;
  size_type _size;
  allocator alloc;

 public:
};

}  // namespace s21
#endif
