#ifndef S21_map_HPP
#define S21_map_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include "../vector/s21_vector.hpp"
#include "../../utilities/rb_tree.h"

namespace s21 {
template <typename Key, typename T>
class map {
  public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type,mapped_type>;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using tree_type = RedBlackTree<Key, T>;
  using iterator = typename tree_type::iterator;
  using const_iterator = typename tree_type::RedBlackTreeConstIterator;

  map() : rb_tree_() {}

  map(std::initializer_list<value_type> const &items) :  rb_tree_() {
     for (const_reference item : items) insert(item.first, item.second);
  } 

  map(const map &m) : rb_tree_(m.rb_tree_) {}

  map(map &&m) : rb_tree_() {
    swap(m);
  }

  map& operator=(map &&m) {
    if (m != *this) swap(m);
    return *this;
  }

  ~map() {}

  mapped_type& at(const key_type& key) {
    if (!contains(key)) throw std::out_of_range("Key not found in the map");
    return rb_tree_.searchTree(key)->value;
  }

  mapped_type& operator[](const key_type& key) {
    if (!rb_tree_.searchTree(key)) {
    ++rb_tree_._size;
    insert(key);
    }
    return rb_tree_.searchTree(key)->value;
  }

  iterator begin() { return rb_tree_.begin(); }
  iterator end() { return rb_tree_.end(); }
  const_iterator begin() const { return rb_tree_.begin(); }
  const_iterator end() const { return rb_tree_.end(); }

  bool empty() const noexcept { return rb_tree_.empty(); } 
  size_type size() const noexcept { return rb_tree_.size(); }
  size_type max_size() const noexcept { return rb_tree_.max_size(); }

  void clear() noexcept {
    rb_tree_.clear();
  }

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

  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj) {
    iterator place(rb_tree_.searchTree(key));
    bool placed = false;
    if (place == rb_tree_.getNullNode()) {
      placed = true;
      rb_tree_.insert(key, obj);
      place = iterator(rb_tree_.searchTree(key));
    }
    return std::pair<iterator, bool>(rb_tree_.getNullNode(), placed);
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj) {
    iterator place(rb_tree_.searchTree(key));
    bool placed = false;
    if (place == rb_tree_.getNullNode()) {
      placed = true;
      rb_tree_.insert(key, obj);
      place = iterator(rb_tree_.searchTree(key));
    } else {
      rb_tree_.searchTree(key).value = obj;
    }
    return std::pair<iterator, bool>(rb_tree_.getNullNode(), placed);
  }
  
  void erase(iterator pos) {
    rb_tree_.deleteNode(*pos);
  }

  void swap(map& other) {
    std::swap(rb_tree_, other.rb_tree_);
  }

  void merge(map& other) {
    if (this == &other) return;
    for (iterator it = other.begin(); it != other.end(); ++it) {
      insert_or_assign(it.key, it.value); //нужен доступ к ключу-значению. лучше реализовать в дереве
    }
  }

  bool contains(const Key& key) const {
    return rb_tree_.searchTree(key) == rb_tree_.getNullNode();
  }

  template <typename... Args>
  vector<std::pair<iterator,bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> vec;
    for (const auto &arg : {args...}) vec.push_back(insert(arg, arg));
    return vec;
  }
  
  /*** NON MEMBER ***/
  friend bool operator==( const map& lhs,
                 const map& rhs ) {
    return lhs.rb_tree_ == rhs.rb_tree_;
  }

  private:
  tree_type rb_tree_;
};

} //namespace s21
#endif