#ifndef S21_map_HPP
#define S21_map_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

#include "../../utilities/rb_tree.h"
#include "../vector/s21_vector.hpp"

namespace s21 {
template <typename Key, typename T>
class map {
  class MapIterator;
  class MapConstIterator;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using tree_type = RedBlackTree<Key, T>;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;

  map() : rb_tree_() {}

  map(std::initializer_list<value_type> const &items) : rb_tree_() {
    for (const_reference item : items) rb_tree_.insert(item.first, item.second);
  }

  map(const map &m) : rb_tree_(m.rb_tree_) {}

  map(map &&m) : rb_tree_(std::move(m.rb_tree_)) {}

  map &operator=(map &&m) {
    if (m != *this) swap(m);
    return *this;
  }

  ~map() {}

  mapped_type &at(const key_type &key) {
    if (!contains(key)) throw std::out_of_range("Key not found in the map");
    return *iterator(rb_tree_.searchTree(key));
  }

  mapped_type &operator[](const key_type &key) {
    iterator place(rb_tree_.searchTree(key));
    if (place == rb_tree_.getNullNode()) {
      rb_tree_.insert(key, mapped_type());
    }
    return *place;
  }

  iterator begin() { return MapIterator(rb_tree_.begin()); }
  iterator end() { return MapIterator(rb_tree_.end()); }
  const_iterator begin() const { return MapConstIterator(rb_tree_.begin()); }
  const_iterator end() const { return MapConstIterator(rb_tree_.end()); }

  bool empty() const noexcept { return rb_tree_.empty(); }
  size_type size() const noexcept { return rb_tree_.size(); }
  size_type max_size() const noexcept { return rb_tree_.max_size(); }

  void clear() noexcept { rb_tree_.clear(); }

  std::pair<iterator, bool> insert(const_reference value) {
    iterator place(rb_tree_.searchTree(value.first));
    bool placed = false;
    if (place == rb_tree_.getNullNode()) {
      placed = true;
      rb_tree_.insert(value.first, value.second);
      place = iterator(rb_tree_.searchTree(value.first));
    }
    return std::pair<iterator, bool>(place, placed);
  }

  std::pair<iterator, bool> insert(const key_type &key,
                                   const mapped_type &obj) {
    iterator place(rb_tree_.searchTree(key));
    bool placed = false;
    if (place == rb_tree_.getNullNode()) {
      placed = true;
      rb_tree_.insert(key, obj);
      place = iterator(rb_tree_.searchTree(key));
    }
    return std::pair<iterator, bool>(rb_tree_.getNullNode(), placed);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj) {
    iterator place(rb_tree_.searchTree(key));
    bool placed = false;
    if (place == rb_tree_.getNullNode()) {
      placed = true;
      rb_tree_.insert(key, obj);
      place = rb_tree_.searchTree(key);
    } else {
      *place = obj;
    }
    return std::pair<iterator, bool>(rb_tree_.getNullNode(), placed);
  }

  void erase(iterator pos) { rb_tree_.deleteNode(pos->first); }

  void swap(map &other) {
    RedBlackTree new_tree(other.rb_tree_);
    other.rb_tree_ = rb_tree_;
    rb_tree_ = new_tree;
  }

  void merge(map &other) {
    if (this == &other) return;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert_or_assign(
          it->first, it->second);  // нужен доступ к ключу-значению.
                                   // лучше реализовать в дереве закостылировал
    }
  }

  bool contains(const Key &key) {
    return rb_tree_.searchTree(key) != rb_tree_.getNullNode();
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...}) vec.push_back(insert(arg, arg));
    return vec;
  }

  /*** NON MEMBER ***/
  friend bool operator==(const map &lhs, const map &rhs) {
    return lhs.rb_tree_ == rhs.rb_tree_;
  }

 private:
  tree_type rb_tree_;
};

template <typename Key, typename T>
class map<Key, T>::MapIterator {
 public:
  MapIterator() noexcept {}

  MapIterator(const MapIterator &it) noexcept : rb_it(it.rb_it) {}
  MapIterator(MapIterator &&it) noexcept : rb_it(std::move(it.rb_it)) {}

  MapIterator(const typename RedBlackTree<Key, T>::iterator &it) noexcept
      : rb_it(it) {}
  MapIterator(typename RedBlackTree<Key, T>::iterator &it) noexcept
      : rb_it(it) {}
  MapIterator(typename RedBlackTree<Key, T>::iterator &&it) noexcept
      : rb_it(std::move(it)) {}
  ~MapIterator() {}

  MapIterator &operator=(const MapIterator &other) {
    if (&other != this) {
      rb_it = other.rb_it;
    }
    return *this;
  }

  friend bool operator==(const MapIterator &lhs,
                         const MapIterator &rhs) noexcept {
    return lhs.rb_it == rhs.rb_it;
  }

  friend bool operator!=(const MapIterator &lhs,
                         const MapIterator &rhs) noexcept {
    return lhs.rb_it != rhs.rb_it;
  }

  T &operator*() noexcept { return (*rb_it)->value; }
  std::pair<Key, T> *operator->() noexcept {
    data.first = (*rb_it)->key;
    data.second = (*rb_it)->value;
    return &data;
  }

  MapIterator &operator++() noexcept {
    rb_it++;
    return *this;
  }
  MapIterator &operator--() noexcept {
    rb_it--;
    return *this;
  }

  MapIterator operator++(int) noexcept {
    MapIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  MapIterator operator--(int) noexcept {
    MapIterator tmp(*this);
    --(*this);
    return tmp;
  }

  MapIterator &operator+=(const size_type n) {
    for (size_t i = 0; i < n; i++) ++(*this);
    return *this;
  }

  MapIterator &operator-=(const size_type n) {
    for (auto i = 0; i < n; i++) --(*this);
    return *this;
  }

 private:
  typename RedBlackTree<Key, T>::iterator rb_it;
  std::pair<Key, T> data;
};

template <typename Key, typename T>
class map<Key, T>::MapConstIterator {
 public:
  MapConstIterator() noexcept {}

  MapConstIterator(const MapConstIterator &it) noexcept : rb_it(it.rb_it) {}
  MapConstIterator(MapConstIterator &&it) noexcept
      : rb_it(std::move(it.rb_it)) {}

  MapConstIterator(
      const typename RedBlackTree<Key, T>::const_iterator &it) noexcept
      : rb_it(it) {}
  MapConstIterator(typename RedBlackTree<Key, T>::const_iterator &&it) noexcept
      : rb_it(std::move(it)) {}
  ~MapConstIterator() {}

  MapConstIterator &operator=(const MapConstIterator &other) {
    if (&other != this) {
      rb_it = other.rb_it;
    }
    return *this;
  }

  friend bool operator==(const MapConstIterator &lhs,
                         const MapConstIterator &rhs) noexcept {
    return lhs.rb_it == rhs.rb_it;
  }

  friend bool operator!=(const MapConstIterator &lhs,
                         const MapConstIterator &rhs) noexcept {
    return lhs.rb_it != rhs.rb_it;
  }

  // const_reference operator*() const noexcept { return (*rb_it)->value; }
  std::pair<Key, T> operator->() noexcept {
    return {(*rb_it)->key, (*rb_it)->value};
  }

  MapConstIterator &operator++() noexcept {
    rb_it++;
    return *this;
  }
  MapConstIterator &operator--() noexcept {
    rb_it--;
    return *this;
  }

  MapConstIterator operator++(int) noexcept {
    MapConstIterator tmp(*this);
    ++(*this);
    return tmp;
  }

  MapConstIterator operator--(int) noexcept {
    MapConstIterator tmp(*this);
    --(*this);
    return tmp;
  }

  MapConstIterator &operator+=(const size_type n) {
    for (size_t i = 0; i < n; i++) ++(*this);
    return *this;
  }

  MapConstIterator &operator-=(const size_type n) {
    for (auto i = 0; i < n; i++) --(*this);
    return *this;
  }

 private:
  typename RedBlackTree<Key, T>::const_iterator rb_it;
};

}  // namespace s21
#endif
