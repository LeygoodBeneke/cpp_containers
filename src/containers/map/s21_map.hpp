#ifndef S21_MAP_HPP
#define S21_MAP_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include "../../utilities/rb_tree.h"

namespace s21 {
template <typename Key, typename T, typename A = std::allocator<std::pair<const Key, T>>>
class map {
  public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type,mapped_type>;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using allocator_type = A;

  map() {}
  map(std::initializer_list<value_type> const &items) {}
  map(const map &m) {}
  map(map &&m) {}
  ~map() {}
  operator=(map &&m) {}

  T& at(const Key& key);
  T& operator[](const Key& key);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
  bool contains(const Key& key);

  private:
  allocator_type allocator_;
  RedBlackTree<T>
};

} //namespace s21
#endif