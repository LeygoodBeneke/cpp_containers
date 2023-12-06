#ifndef RB_TREE_ITERATOR
#define RB_TREE_ITERATOR

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree;

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree<T, ValueType, Allocator>::RedBlackTreeIterator {
 public:
  RedBlackTreeIterator() noexcept {}
  RedBlackTreeIterator(RedBlackTreeIterator &it) noexcept : ptr(it.ptr) {}
  RedBlackTreeIterator(Node &node_ptr) noexcept : ptr(&node_ptr) {}
  RedBlackTreeIterator(Node *node_ptr) noexcept : ptr(node_ptr) {}
  ~RedBlackTreeIterator() noexcept {}

  RedBlackTreeIterator &operator=(const RedBlackTreeIterator &other) noexcept {
    ptr = other.ptr;
    return *this;
  }

  bool operator==(const RedBlackTreeIterator &other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator==(Node *other) const noexcept { return ptr == other; }

  bool operator!=(const RedBlackTreeIterator &other) const noexcept {
    return ptr != other.ptr;
  }

  T &operator*() { return ptr->value; }

  RedBlackTreeIterator operator++() noexcept {
    RedBlackTreeIterator it(*this);
    ptr = next(ptr);
    return it;
  }

  RedBlackTreeIterator &operator++(int) noexcept {
    ptr = next(ptr);
    return *this;
  }

  RedBlackTreeIterator operator--() noexcept {
    RedBlackTreeIterator it(*this);
    ptr = prev(*this);
    return it;
  }

  RedBlackTreeIterator &operator--(int) noexcept {
    ptr = prev(ptr);
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
    if (!root->right->right && !root->right->left) {
      Node *parent = root->parent;
      while (parent) {
        if (parent->key >= root->key) {
          return parent;
        }
        parent = parent->parent;
      }
      return nullptr;
    }
    Node *right = root->right;
    while (right->left->left && right->left->right) right = right->left;
    return right;
  }

  Node *prev(RedBlackTreeIterator &root) noexcept {
    if (!root->left->right && !root->left->left) {
      Node *parent = root->parent;
      while (parent) {
        if (parent->key <= root->key) {
          return parent;
        }
        parent = parent->parent;
      }
      return nullptr;
    }
    Node *left = root->left;
    while (left->right->left && left->right->right) left = left->right;
    return left;
  }

  Node *ptr;
};

#endif
