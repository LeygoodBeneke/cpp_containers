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
class Map {
  public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type,mapped_type>;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using allocator_type = A;
  using tree_allocator =
      typename std::allocator_traits<allocator_type>::template rebind_alloc<RedBlackTree<Key, T>>;
  using size_type = std::size_t;
  using tree_type = RedBlackTree<Key, T>;
  using iterator = typename tree_type::RedBlackTreeIterator;
  using const_iterator = typename tree_type::RedBlackTreeConstIterator;

  Map(const allocator_type &alloc = allocator_type()) try : alloc_(alloc), rb_tree_(tree_alloc_.allocate(1)) {
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  Map(std::initializer_list<value_type> const &items, const allocator_type &alloc = allocator_type()) try : alloc_(alloc), rb_tree_(tree_alloc_.allocate(1)) {
     for (const_reference item : items) insert(item);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  Map(const Map &m, const allocator_type &alloc = allocator_type()) try : alloc_(alloc), rb_tree_(tree_alloc_.allocate(1)) {
    for (const_iterator it = m.begin(); it != m.end(); ++it) insert(*it);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  Map(Map &&m) try : alloc_(alloc), rb_tree_(tree_alloc_.allocate(1)) {
    swap(m);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  ~Map() { rb_tree_.clear(); }

  Map &operator=(const Map &otherMap) {
    rb_tree_ = otherMap.tree_alloc_;
  }

  Map& operator=(Map &&m) {
    if (m != *this) swap(m);
    return *this;
  }

  reference at(const Key& key);
  reference operator[](const Key& key);
  iterator begin();
  iterator end();

  bool empty() const noexcept { return rb_tree_.size(); } //нужен метод size
  size_type size() const noexcept { return rb_tree_.size();  }
  size_type max_size() const noexcept { return alloc_.max_size(); }

  void clear() noexcept {
    rb_tree_.clear();
  }

  //нужно чтобы в tree возвращаемое значение было std::pair<iterator, bool> и далее аналогично
  std::pair<iterator, bool> insert(const_reference value) {
    return rb_tree_.insert(value);
  }

  std::pair<iterator, bool> insert(const Key& key, const T& obj) {
    value_type value = std::make_pair(key, obj);
    return rb_tree_.insert(value);
  }

  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj) {
    //вставка или замена значения по ключу
  }
  
  void erase(iterator pos) {
    rb_tree_.deleteNode(pos.ptr);
  }

  void swap(Map& other) {
    rb_tree_.swap(other); //нужна функция в tree
  }

  void merge(Map& other);

  bool contains(const Key& key) const {
    //return rb_tree_ поиск по дереву с булевым значением
  }
  
  /*** NON MEMBER ***/
  friend bool operator==( const std::map<Key, T, Compare, Alloc>& lhs,
                 const std::map<Key, T, Compare, Alloc>& rhs ) {
    if (lhs.size() != rhs.size())
      return false;
    else {
      for (std::pair<const_iterator, const_iterator> it(lhs.begin(),
                                                        rhs.begin());
           it.first != lhs.end(); ++it.first, ++it.second) {
        if (*(it.first) != *(it.second)) return false;
      }
    }
    return true;
  }

  private:
  allocator_type alloc_;
  tree_allocator tree_alloc_;
  tree_type rb_tree_;
};

} //namespace s21
#endif