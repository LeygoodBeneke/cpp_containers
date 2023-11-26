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
  using value_type = T;
  using reference = value_type &;
  using pointer = value_type *;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using allocator = A;

 private:
  struct Node {
    value_type value_;
    Node *next_;
    Node *prev_;
  };

  using node_allocator =
      typename std::allocator_traits<allocator>::template rebind_alloc<Node>;

 public:
  class ListIterator {
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    friend class list;
    friend class ListConstIterator;

    ListIterator() noexcept {}
    ListIterator(const ListIterator &it) noexcept : ptr_(it.ptr_) {}
    ListIterator(Node *node) noexcept : ptr_(node) {}
    ~ListIterator() {}

    ListIterator &operator=(const ListIterator &other) {
      if (&other != this) {
        ptr_ = other.ptr_;
      }
      return *this;
    }

    bool operator==(const ListIterator &other) noexcept {
      return ptr_ == other.ptr_;
    }
    bool operator!=(const ListIterator &other) const noexcept {
      return ptr_ != other.ptr_;
    }
    reference operator*() const noexcept { return ptr_->value_; }
    pointer operator->() const noexcept { return &(ptr_->value_); }

    ListIterator &operator++() noexcept {
      ptr_ = ptr_->next_;
      return *this;
    }
    ListIterator &operator--() noexcept {
      ptr_ = ptr_->prev_;
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
    friend class ListIterator;

    ListConstIterator() noexcept {}
    ListConstIterator(const ListConstIterator &it) noexcept : ptr_(it.ptr_) {}
    ListConstIterator(const ListIterator &it) noexcept : ptr_(it.ptr_) {}
    ListConstIterator(const Node *node) noexcept : ptr_(node) {}
    ~ListConstIterator() {}

    ListConstIterator &operator=(const ListConstIterator &other) {
      if (&other != this) {
        ptr_ = other.ptr_;
      }
      return *this;
    }

    const_reference operator*() { return ptr_->value_; }
    ListConstIterator &operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListConstIterator &operator--() {
      ptr_ = ptr_->prev_;
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
  friend iterator;

 private:
  allocator alloc_;
  node_allocator node_alloc_;
  size_type sz_;

  // 1st item (if it exists) is at end_->next_, the last one is at end_->prev_
  Node *end_;

 public:
  list(const allocator &alloc = allocator()) try
      : alloc_(alloc), sz_(0), end_(create_end()) {
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  explicit list(size_type n, const allocator &alloc = allocator()) try
      : alloc_(alloc), sz_(0), end_(create_end()) {
    insert(end(), n);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  template <class InputIt>
  list(InputIt first, InputIt last, const allocator &alloc = allocator()) try
      : alloc_(alloc), sz_(0), end_(create_end()) {
    for (; first != last; ++first) push_back(*first);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  list(std::initializer_list<value_type> const &items,
       const allocator &alloc = allocator()) try
      : alloc_(alloc), sz_(0), end_(create_end()) {
    for (const_reference item : items) push_back(item);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  list(const list &l) try : alloc_(l.alloc_), sz_(0), end_(create_end()) {
    for (const_iterator it = l.begin(); it != l.end(); ++it) {
      push_back(*it);
    }
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  list(list &&l) try : alloc_(allocator()), sz_(0), end_(create_end()) {
    swap(l);
  } catch (std::bad_alloc &t) {
    std::cerr << t.what() << std::endl;
    clear();
    throw;
  }

  ~list() noexcept {
    clear();
    node_alloc_.deallocate(end_, 1);
  }

  list &operator=(list &&l) {
    if (l != *this) swap(l);
    return *this;
  }

  void clear() noexcept {
    while (sz_) pop_back();
  }

  reference front() { return *begin(); }
  const_reference front() const { return *begin(); }
  reference back() { return *(--end()); }
  const_reference back() const { return *(--end()); }

  iterator begin() { return iterator(end_->next_); }
  const_iterator begin() const { return const_iterator(end_->next_); }
  iterator end() { return iterator(end_); }
  const_iterator end() const { return const_iterator(end_); }

  void push_back(const_reference value = value_type{}) { insert(end(), value); }
  void pop_back() {
    if (sz_) erase(--end());
  }
  void push_front(const_reference value = value_type{}) {
    insert(begin(), value);
  }
  void pop_front() {
    if (sz_) erase(begin());
  }

  bool empty() const noexcept { return sz_ == 0; }
  size_type size() const noexcept { return sz_; }
  size_type max_size() const noexcept { return alloc_.max_size(); }

  iterator insert(iterator pos, const_reference value) {
    Node *new_node = create_node(value);
    new_node->next_ = pos.ptr_;
    if (pos.ptr_->prev_ == end_) {
      new_node->prev_ = end_;
      end_->next_ = new_node;
    } else {
      new_node->prev_ = pos.ptr_->prev_;
      pos.ptr_->prev_->next_ = new_node;
    }
    pos.ptr_->prev_ = new_node;
    ++sz_;
    return (iterator(--pos));
  }

  iterator insert(iterator pos, size_type count,
                  const_reference value = value_type{}) {
    while (count--) insert(pos, value);
    return begin();
  }

  iterator erase(iterator pos) {
    if (pos == end()) throw std::out_of_range("Cannot erase the end iterator");
    iterator tmp(pos.ptr_->next_);
    if (pos.ptr_->prev_ == end_) {
      end_->next_ = pos.ptr_->next_;
    } else {
      pos.ptr_->prev_->next_ = pos.ptr_->next_;
    }
    if (pos.ptr_->next_ == end_) {
      end_->prev_ = pos.ptr_->prev_;
    } else {
      pos.ptr_->next_->prev_ = pos.ptr_->prev_;
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
    if (alloc_ != other.alloc_)
      throw std::invalid_argument("The behavior is undefined");
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
    if (alloc_ != other.alloc_)
      throw std::invalid_argument("The behavior is undefined");
    if (other.sz_) {
      iterator it = other.end();
      it.ptr_->next_->prev_ = pos.ptr_->prev_;
      it.ptr_->prev_->next_ = pos.ptr_;

      pos.ptr_->prev_->next_ = it.ptr_->next_;
      pos.ptr_->prev_ = it.ptr_->prev_;

      sz_ += other.sz_;
      other.sz_ = 0;
      other.end_->next_ = it.ptr_;
      other.end_->prev_ = it.ptr_;
    }
  }

  void reverse() noexcept {
    Node *cur = end_->next_;
    Node *tmp;
    end_->next_ = end_->prev_;
    end_->prev_ = cur;
    while (cur != end_) {
      tmp = cur->next_;
      cur->next_ = cur->prev_;
      cur->prev_ = tmp;
      cur = tmp;
    }
  }

  void unique() {
    iterator it = begin();
    while (it != end()) {
      value_type val = *it;
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
    if (sz_) end_->next_ = merge_sort(end_->next_);
    Node *tmp = end_->next_;
    Node *prev;
    while (tmp != end_) {
      prev = tmp;
      tmp = tmp->next_;
    }
    end_->prev_ = prev;
  }

  /*** NON MEMBER ***/
  friend bool operator==(const s21::list<value_type, allocator> &lhs,
                         const s21::list<value_type, allocator> &rhs) {
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

  /*** UTILS ***/
 private:
  Node *create_node(const_reference value = value_type{}) {
    Node *node = node_alloc_.allocate(1);
    node_alloc_.construct(&node->value_, value);
    return node;
  }

  Node *create_end() {
    Node *end = create_node();
    end->prev_ = end;
    end->next_ = end;
    return end;
  }

  Node *split(Node *src) {
    Node *fast = src;
    Node *slow = src;
    while (fast->next_ != end_ && fast->next_->next_ != end_) {
      fast = fast->next_->next_;
      slow = slow->next_;
    }
    Node *back_ref = slow->next_;
    slow->next_ = end_;
    return back_ref;
  }

  Node *merge_sort(Node *head_ref) {
    if (head_ref == end_ || head_ref->next_ == end_) return head_ref;
    Node *second = split(head_ref);
    return sorted_merge(merge_sort(head_ref), merge_sort(second));
  }

  Node *sorted_merge(Node *first, Node *second) {
    if (first == end_) return second;
    if (second == end_) return first;

    if (first->value_ <= second->value_) {
      first->next_ = sorted_merge(first->next_, second);
      first->next_->prev_ = first;
      first->prev_ = end_;
      return first;
    } else {
      second->next_ = sorted_merge(first, second->next_);
      second->next_->prev_ = second;
      second->prev_ = end_;
      return second;
    }
  }
};

}  // namespace s21

#endif