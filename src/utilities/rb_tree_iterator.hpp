#ifndef RB_TREE_ITERATOR
#define RB_TREE_ITERATOR

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree;

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree<T, ValueType, Allocator>::RedBlackTreeIterator {
 public:
  RedBlackTreeIterator() noexcept {}
  RedBlackTreeIterator(const RedBlackTreeIterator &it) noexcept
      : ptr(it.ptr), prev_ptr(it.prev_ptr), next_ptr(it.next_ptr) {}
  RedBlackTreeIterator(RedBlackTreeIterator &&it) noexcept
      : ptr(std::move(it.ptr)),
        prev_ptr(std::move(it.prev_ptr)),
        next_ptr(std::move(it.next_ptr)) {}
  RedBlackTreeIterator(Node &node_ptr) noexcept : ptr(&node_ptr) {
    prev_ptr = prev(ptr);
    next_ptr = next(ptr);
  }
  RedBlackTreeIterator(Node *node_ptr) noexcept : ptr(node_ptr) {
    prev_ptr = prev(ptr);
    next_ptr = next(ptr);
  }
  ~RedBlackTreeIterator() noexcept {}

  RedBlackTreeIterator &operator=(const RedBlackTreeIterator &other) noexcept {
    ptr = other.ptr;
    prev_ptr = other.prev_ptr;
    next_ptr = other.next_ptr;
    return *this;
  }

  bool operator==(const RedBlackTreeIterator &other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator==(Node *other) const noexcept { return ptr == other; }

  bool operator!=(const RedBlackTreeIterator &other) const noexcept {
    return ptr != other.ptr;
  }

  Node *operator*() { return ptr; }

  RedBlackTreeIterator operator++(int) noexcept {
    RedBlackTreeIterator it(*this);
    prev_ptr = ptr;
    ptr = next_ptr;
    next_ptr = next(next_ptr);
    return it;
  }

  RedBlackTreeIterator &operator++() noexcept {
    prev_ptr = ptr;
    ptr = next_ptr;
    next_ptr = next(next_ptr);
    return *this;
  }

  RedBlackTreeIterator operator--(int) noexcept {
    RedBlackTreeIterator it(*this);
    next_ptr = ptr;
    ptr = prev_ptr;
    prev_ptr = prev(prev_ptr);
    return it;
  }

  RedBlackTreeIterator &operator--() noexcept {
    next_ptr = ptr;
    ptr = prev_ptr;
    prev_ptr = prev(prev_ptr);
    return *this;
  }

  RedBlackTreeIterator &operator-=(const unsigned tmp) noexcept {
    for (unsigned i = 0; i < tmp; i++) --(*this);
    return *this;
  }

  RedBlackTreeIterator &operator+=(const unsigned tmp) noexcept {
    for (unsigned i = 0; i < tmp; i++) ++(*this);
    return *this;
  }

 private:
  Node *next(Node *root) noexcept {
    if (!root->right) return nullptr;
    if (!root->right->right && !root->right->left) {
      Node *parent = root->parent;
      while (parent) {
        if (parent->key >= root->key) {
          return parent;
        }
        parent = parent->parent;
      }
      return root->right;
    }
    Node *right = root->right;
    while (right->left->left && right->left->right) right = right->left;
    return right;
  }

  Node *prev(Node *root) noexcept {
    if (!root->left) return nullptr;
    if (!root->left->right && !root->left->left) {
      Node *parent = root->parent;
      while (parent) {
        if (parent->key <= root->key) {
          return parent;
        }
        parent = parent->parent;
      }
      return root->left;
    }
    Node *left = root->left;
    while (left->right->left && left->right->right) left = left->right;
    return left;
  }

  Node *ptr, *prev_ptr, *next_ptr;
};

#endif
