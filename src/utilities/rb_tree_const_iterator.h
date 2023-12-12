#ifndef RB_TREE_CONSTITERATOR
#define RB_TREE_CONSTITERATOR

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree;

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree<T, ValueType, Allocator>::RedBlackTreeConstIterator {
 public:
  RedBlackTreeConstIterator() noexcept {}
  RedBlackTreeConstIterator(const RedBlackTreeConstIterator &it) noexcept
      : ptr(it.ptr) {}
  RedBlackTreeConstIterator(RedBlackTreeConstIterator &&it) noexcept
      : ptr(std::move(it.ptr)) {}
  RedBlackTreeConstIterator(Node &node_ptr) noexcept : ptr(&node_ptr) {}
  RedBlackTreeConstIterator(Node *node_ptr) noexcept : ptr(node_ptr) {}
  ~RedBlackTreeConstIterator() noexcept {}

  RedBlackTreeConstIterator &operator=(
      const RedBlackTreeConstIterator &other) noexcept {
    ptr = other.ptr;
    return *this;
  }

  bool operator==(const RedBlackTreeConstIterator &other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator==(const Node *other) const noexcept { return ptr == other; }

  bool operator!=(const RedBlackTreeConstIterator &other) const noexcept {
    return ptr != other.ptr;
  }

  const Node *operator*() { return ptr; }

  RedBlackTreeConstIterator operator++(int) noexcept {
    RedBlackTreeConstIterator it(*this);
    ptr = next(ptr);
    return it;
  }

  RedBlackTreeConstIterator &operator++() noexcept {
    ptr = next(ptr);
    return *this;
  }

  RedBlackTreeConstIterator operator--(int) noexcept {
    RedBlackTreeConstIterator it(*this);
    ptr = prev(*this);
    return it;
  }

  RedBlackTreeConstIterator &operator--() noexcept {
    ptr = prev(ptr);
    return *this;
  }

  RedBlackTreeConstIterator &operator-=(const unsigned tmp) noexcept {
    for (unsigned i = 0; i < tmp; i++) --(*this);
    return *this;
  }

  RedBlackTreeConstIterator &operator+=(const unsigned tmp) noexcept {
    for (unsigned i = 0; i < tmp; i++) ++(*this);
    return *this;
  }

 private:
  const Node *next(const Node *root) noexcept {
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

  const Node *prev(const Node *root) noexcept {
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

  const Node *ptr;
};

#endif
