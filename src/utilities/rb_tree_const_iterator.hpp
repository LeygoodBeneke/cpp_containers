#ifndef RB_TREE_CONSTITERATOR
#define RB_TREE_CONSTITERATOR

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree;

template <typename T, typename ValueType, typename Allocator>
class RedBlackTree<T, ValueType, Allocator>::RedBlackTreeConstIterator {
 public:
  RedBlackTreeConstIterator() noexcept {}
  RedBlackTreeConstIterator(const RedBlackTreeConstIterator &it) noexcept
      : ptr(it.ptr), prev_ptr(it.prev_ptr), next_ptr(it.next_ptr) {}
  RedBlackTreeConstIterator(RedBlackTreeConstIterator &&it) noexcept
      : ptr(std::move(it.ptr)),
        prev_ptr(std::move(it.prev_ptr)),
        next_ptr(std::move(it.next_ptr)) {}
  RedBlackTreeConstIterator(Node &node_ptr) noexcept : ptr(&node_ptr) {
    prev_ptr = prev(ptr);
    next_ptr = next(ptr);
  }
  RedBlackTreeConstIterator(const Node *node_ptr) noexcept : ptr(node_ptr) {
    prev_ptr = prev(ptr);
    next_ptr = next(ptr);
  }
  ~RedBlackTreeConstIterator() noexcept {}

  RedBlackTreeConstIterator &operator=(
      const RedBlackTreeConstIterator &other) noexcept {
    ptr = other.ptr;
    prev_ptr = other.prev_ptr;
    next_ptr = other.next_ptr;
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
    prev_ptr = ptr;
    ptr = next_ptr;
    next_ptr = next(next_ptr);
    return it;
  }

  RedBlackTreeConstIterator &operator++() noexcept {
    prev_ptr = ptr;
    ptr = next_ptr;
    next_ptr = next(next_ptr);
    return *this;
  }

  RedBlackTreeConstIterator operator--(int) noexcept {
    RedBlackTreeConstIterator it(*this);
    next_ptr = ptr;
    ptr = prev_ptr;
    prev_ptr = prev(prev_ptr);
    return it;
  }

  RedBlackTreeConstIterator &operator--() noexcept {
    next_ptr = ptr;
    ptr = prev_ptr;
    prev_ptr = prev(prev_ptr);
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

  const Node *prev(const Node *root) noexcept {
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

  const Node *ptr, *prev_ptr, *next_ptr;
};

#endif
