#ifndef S21_LIST_HPP
#define S21_LIST_HPP

#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>

namespace s21 {
template <typename T, typename A = std::allocator<T>>
class list {
 public:
  using valuetype = T;
  using reference = valuetype &;
  using pointer = valuetype *;
  using const_reference = const valuetype &;
  using size_type = std::size_t;
  using allocator_type = A;

 private:
  struct Node {
    valuetype value;
    Node *next;
    Node *prev;
  };

  using node_allocator = typename std::allocator_traits<
      allocator_type>::template rebind_alloc<Node>;

 public:
  class ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    friend class list;

    ListIterator() noexcept {}
    ListIterator(const ListIterator &it) noexcept : ptr_(it.ptr_) {}
    ListIterator(Node *node) noexcept : ptr_(node) {}
    ListIterator &operator=(const ListIterator &other) {
      if (&other != this) {
        ptr_ = other.ptr_;
      }
      return *this;
    }
    ~ListIterator() {}

    bool operator==(const ListIterator &other) noexcept {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ListIterator &other) const noexcept {
      return ptr_ != other.ptr_;
    }
    reference operator*() const noexcept { return ptr_->value; }
    pointer operator->() const noexcept { return &(ptr_->value); }

    ListIterator &operator++() noexcept {
      ptr_ = ptr_->next;
      return *this;
    }
    ListIterator &operator--() noexcept {
      ptr_ = ptr_->prev;
      return *this;
    }

    ListIterator operator++(int) noexcept {
      ListIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    ListIterator operator--(int) noexcept {
      ListIterator tmp(*this);
      --(*this);
      return tmp;
    }

    ListIterator &operator+=(const size_type n) {
      for (size_t i = 0; i < n && ptr_; i++) ++(*this);
      return *this;
    }

    ListIterator &operator-=(const size_type n) {
      for (auto i = 0; i < n && ptr_; i++) --(*this);
      return *this;
    }

   private:
    Node *ptr_;
  };

  class ListConstIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    friend class list;

    ListConstIterator() noexcept {}
    ListConstIterator(const ListConstIterator &it) noexcept : ptr_(it.ptr_) {}
    ListConstIterator(const ListIterator &it) noexcept : ptr_(it.ptr_) {}
    ListConstIterator(const Node *node) noexcept : ptr_(node) {}
    ListConstIterator &operator=(const ListConstIterator &other) {
      if (&other != this) {
        ptr_ = other.ptr_;
      }
      return *this;
    }
    ~ListConstIterator() {}

    const_reference operator*() { return ptr_->value; }
    ListConstIterator &operator++() {
      ptr_ = ptr_->next;
      return *this;
    }

    ListConstIterator &operator--() {
      ptr_ = ptr_->prev;
      return *this;
    }
    ListConstIterator operator++(int) noexcept {
      ListConstIterator temp(*this);
      ++(*this);
      return temp;
    }

    ListConstIterator operator--(int) noexcept {
      ListConstIterator temp(*this);
      --(*this);
      return temp;
    }

    bool operator==(const ListConstIterator &other) noexcept {
      return ptr_ == other.ptr_;
    }

    bool operator!=(const ListConstIterator &other) const noexcept {
      return ptr_ != other.ptr_;
    }

   private:
    const Node *ptr_;
  };

  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 public:
  list(const allocator_type &alloc = allocator_type())
      : alloc_(alloc), sz_(0), end_(CreateEnd()) {}

  explicit list(size_type n, const allocator_type &alloc = allocator_type())
      : alloc_(alloc), sz_(0), end_(CreateEnd()) {
    insert(end(), n);
  }

  template <class InputIt>
  list(InputIt first, InputIt last,
       const allocator_type &alloc = allocator_type())
      : alloc_(alloc), sz_(0), end_(CreateEnd()) {
    for (; first != last; ++first) push_back(*first);
  }

  list(std::initializer_list<valuetype> const &items,
       const allocator_type &alloc = allocator_type())
      : alloc_(alloc), sz_(0), end_(CreateEnd()) {
    for (const_reference item : items) push_back(item);
  }

  list(const list &l) : alloc_(l.alloc_), sz_(0), end_(CreateEnd()) {
    for (const_iterator it = l.begin(); it != l.end(); ++it) push_back(*it);
  }

  list(list &&l) : alloc_(allocator_type()), sz_(0), end_(CreateEnd()) {
    swap(l);
  }

  list &operator=(list &&l) {
    if (l != *this) swap(l);
    return *this;
  }

  ~list() noexcept {
    clear();
    node_alloc_.deallocate(end_, 1);
  }

  void clear() noexcept {
    while (sz_) pop_back();
  }

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  iterator begin() { return iterator(end_->next); }
  const_iterator begin() const { return const_iterator(end_->next); }
  iterator end() { return iterator(end_); }
  const_iterator end() const { return const_iterator(end_); }

  void push_back(const_reference value = valuetype{}) { insert(end(), value); }
  void pop_back() {
    if (sz_) erase(--end());
  }
  void push_front(const_reference value = valuetype{}) {
    insert(begin(), value);
  }
  void pop_front() {
    if (sz_) erase(begin());
  }

  bool empty() const noexcept { return sz_ == 0; }
  size_type size() const noexcept { return sz_; }
  size_type max_size() const noexcept { return alloc_.max_size(); }

  iterator insert(iterator pos, const_reference value) {
    Node *new_node = CreateNode(value);
    new_node->next = pos.ptr_;
    if (pos.ptr_->prev == end_) {
      new_node->prev = end_;
      end_->next = new_node;
    } else {
      new_node->prev = pos.ptr_->prev;
      pos.ptr_->prev->next = new_node;
    }
    pos.ptr_->prev = new_node;
    ++sz_;
    return (iterator(--pos));
  }

  iterator insert(iterator pos, size_type count,
                  const_reference value = valuetype{}) {
    while (count--) insert(pos, value);
    return begin();
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    iterator it = iterator(const_cast<Node *>(pos.ptr_));
    for (const auto &arg : {args...}) {
      insert(it, arg);
    }
    return it;
  }

  template <class... Args>
  void insert_many_back(Args &&...args) {
    for (const auto &arg : {args...}) push_back(arg);
  }

  template <class... Args>
  void insert_many_front(Args &&...args) {
    iterator it = begin();
    for (const auto &arg : {args...}) insert(it, arg);
  }

  iterator erase(iterator pos) {
    if (pos == end()) throw std::out_of_range("Cannot erase the end iterator");
    iterator tmp(pos.ptr_->next);
    if (pos.ptr_->prev == end_) {
      end_->next = pos.ptr_->next;
    } else {
      pos.ptr_->prev->next = pos.ptr_->next;
    }
    if (pos.ptr_->next == end_) {
      end_->prev = pos.ptr_->prev;
    } else {
      pos.ptr_->next->prev = pos.ptr_->prev;
    }
    node_alloc_.deallocate(pos.ptr_, 1);
    --sz_;
    return tmp;
  }

  void swap(list &other) noexcept {
    std::swap(end_, other.end_);
    std::swap(sz_, other.sz_);
    std::swap(alloc_, other.alloc_);
    std::swap(node_alloc_, other.node_alloc_);
  }

  void merge(list &other) {
    CheckAllocator(other);
    if (this != &other && other.sz_) {
      iterator it = begin();
      iterator jt = other.begin();
      while (it != end() && jt != other.end()) {
        if (*jt < *it) {
          insert(it, std::move(*jt));
          ++jt;
        } else
          ++it;
        while (jt != other.end()) {
          push_back(*jt);
          ++jt;
        }
        other.clear();
      }
    }
  }

  void splice(iterator pos, list &other) {
    CheckAllocator(other);
    if (other.sz_) {
      iterator it = other.end();
      it.ptr_->next->prev = pos.ptr_->prev;
      it.ptr_->prev->next = pos.ptr_;

      pos.ptr_->prev->next = it.ptr_->next;
      pos.ptr_->prev = it.ptr_->prev;

      sz_ += other.sz_;
      other.sz_ = 0;
      other.end_->next = it.ptr_;
      other.end_->prev = it.ptr_;
    }
  }

  void reverse() noexcept {
    Node *cur = end_->next;
    Node *tmp;
    end_->next = end_->prev;
    end_->prev = cur;
    while (cur != end_) {
      tmp = cur->next;
      cur->next = cur->prev;
      cur->prev = tmp;
      cur = tmp;
    }
  }

  void unique() {
    iterator it = begin();
    while (it != end()) {
      valuetype val = *it;
      iterator next = it;
      ++next;
      if (next != end() && *next == val) {
        erase(next);
      } else {
        ++it;
      }
    }
  }

  void sort() {
    if (sz_) end_->next = MergeSort(end_->next);
    Node *tmp = end_->next;
    Node *prev;
    while (tmp != end_) {
      prev = tmp;
      tmp = tmp->next;
    }
    end_->prev = prev;
  }

  /*** NON MEMBER ***/
  friend bool operator==(const s21::list<valuetype, allocator_type> &lhs,
                         const s21::list<valuetype, allocator_type> &rhs) {
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
  node_allocator node_alloc_;
  size_type sz_;
  // 1st item (if it exists) is at end_->next, the last one is at end_->prev
  Node *end_;

  /*** UTILS ***/
  Node *CreateNode(const_reference value = valuetype{}) {
    Node *node = node_alloc_.allocate(1);
    node_alloc_.construct(&node->value, value);
    return node;
  }

  Node *CreateEnd() {
    Node *end = CreateNode();
    end->prev = end;
    end->next = end;
    return end;
  }

  Node *Split(Node *src) {
    Node *fast = src;
    Node *slow = src;
    while (fast->next != end_ && fast->next->next != end_) {
      fast = fast->next->next;
      slow = slow->next;
    }
    Node *back_ref = slow->next;
    slow->next = end_;
    return back_ref;
  }

  void CheckAllocator(list &other) {
    if (alloc_ != other.alloc_)
      throw std::invalid_argument("The behavior is undefined");
  }

  Node *MergeSort(Node *head_ref) {
    if (head_ref == end_ || head_ref->next == end_) return head_ref;
    Node *second = Split(head_ref);
    return SortedMerge(MergeSort(head_ref), MergeSort(second));
  }

  Node *SortedMerge(Node *first, Node *second) {
    if (first == end_) return second;
    if (second == end_) return first;

    if (first->value <= second->value) {
      first->next = SortedMerge(first->next, second);
      first->next->prev = first;
      first->prev = end_;
      return first;
    } else {
      second->next = SortedMerge(first, second->next);
      second->next->prev = second;
      second->prev = end_;
      return second;
    }
  }
};

}  // namespace s21

#endif