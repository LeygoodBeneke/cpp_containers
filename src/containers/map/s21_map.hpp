#ifndef S21_MAP_HPP
#define S21_MAP_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

namespace s21 {
template<typename Key, typename T, typename Allocator = std::allocator<std::pair<const Key, T>>
> class map {
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type &;
  using const_reference = const value_type &;
  using pointer = value_type *;
  using const_pointer = const value_type *;
  using iterator = pointer;
  using const_iterator = const_pointer;
  using allocator_type = Allocator;
  
    

};
} //namespace 21

#endif
