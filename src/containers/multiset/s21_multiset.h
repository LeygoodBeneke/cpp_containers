#ifndef S21_SET_H
#define S21_SET_H

#include <initializer_list>

#include "../../utilities/rb_tree.h"
#include "../stack/s21_stack.hpp"
#include "../vector/s21_vector.hpp"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>,
          typename Allocator = std::allocator<Key>>
class multiset {
 public:
  using value_type = Key;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using allocator = Allocator;
  using iterator = typename RedBlackTree<Key>::iterator;
  using const_iterator = typename RedBlackTree<Key>::const_iterator;

  multiset() : rb() {}

  multiset(std::initializer_list<Key> const &items) {
    for (const auto item : items) insert(item, item);
  }

  multiset(const multiset &s) { rb = s.rb; }

  multiset(multiset &s) {
    for (const_iterator it : s) insert(*it, *it);
  }

  multiset(const multiset &&s) { rb = std::move(s.rb); }

  multiset(multiset &&s) { rb = std::move(s.rb); }

  ~multiset() {}

  multiset &operator=(multiset s) {
    std::swap(rb, s.rb);
    return *this;
  }

  iterator begin() { return rb.begin(); }
  iterator end() { return rb.end(); }
  const_iterator begin() const { return rb.begin(); }
  const_iterator end() const { return rb.end(); }

  constexpr inline bool empty() const noexcept { return rb.empty(); }
  constexpr inline size_type size() const noexcept { return rb.size(); }
  size_type max_size() const noexcept { return rb.max_size(); }

  void clear() noexcept { rb.deleteNode(rb.getRoot()->value); }

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

  iterator find(const_reference key) { return iterator(rb.searchTree(key)); }

  bool contains(const_reference key) const noexcept {
    return rb.searchTree(key) == rb.getNullNode();
  }

  size_type count(const Key &key) {
    stack<typename RedBlackTree<Key>::Node *> st;
    st.push(rb.searchTree(key));
    size_type count = 0;
    while (st.size()) {
      typename RedBlackTree<Key>::Node *node = st.top();
      st.pop();
      if (node != rb.getNullNode()) {
        count++;
        if (node->left->value == key) st.push(node->left);
        if (node->right->value == key) st.push(node->right);
      }
    }
    return count;
  }

  std::pair<iterator, iterator> equal_range(const Key &key) {
    typename RedBlackTree<Key>::Node *node = rb.searchTree(key);
    if (node == rb.getNullNode())
      return std::pair<iterator, iterator>({end(), end()});
    iterator lhs(node), rhs(node), ll, rr;
    while (*lhs == key) {
      ll = lhs;
      lhs--;
    }
    while (*rhs == key) {
      rr = rhs;
      rhs++;
    }
    return std::pair<iterator, iterator>({ll, rr});
  }

  iterator lower_bound(const Key &key) {
    typename RedBlackTree<Key>::Node *node = rb.searchTree(key);
    if (node == rb.getNullNode())
      return std::pair<iterator, iterator>({end(), end()});
    iterator lhs(node), ll;
    while (*lhs >= key) {
      ll = lhs;
      lhs--;
    }
    return ll;
  }

  iterator upper_bound(const Key &key) {
    typename RedBlackTree<Key>::Node *node = rb.searchTree(key);
    if (node == rb.getNullNode())
      return std::pair<iterator, iterator>({end(), end()});
    iterator lhs(node), ll;
    while (*lhs <= key) {
      lhs++;
      ll = lhs;
    }
    return ll;
  }

  friend bool operator==(
      const multiset<Key, Compare, Allocator> &lhs,
      const s21::multiset<Key, Compare, Allocator> &rhs) noexcept {
    if (lhs.size() != rhs.size()) return false;
    const_iterator lhs_it = lhs.begin(), rhs_it = rhs.begin();
    for (unsigned i = 0; i < lhs.size(); i++) {
      if (*lhs_it != *rhs_it) return false;
      lhs_it++;
      rhs_it++;
    }
    return true;
  }

  friend bool operator!=(
      const multiset<Key, Compare, Allocator> &lhs,
      const s21::multiset<Key, Compare, Allocator> &rhs) noexcept {
    return !(lhs == rhs);
  }

 private:
  RedBlackTree<Key, Key, Allocator> rb;
};

}  // namespace s21
#endif
