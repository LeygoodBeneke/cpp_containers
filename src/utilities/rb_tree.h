#ifndef RB_TREE_H
#define RB_TREE_H

template <typename T>
class RedBlackTree {
 private:
  class RedBlackTreeIterator;
  struct Node;

  Node *root;
  Node *TNULL;

  void initializeNULLNode(Node *node, Node *parent);
  Node *searchTreeHelper(Node *node, T key);
  void deleteFix(Node *x);
  void rbTransplant(Node *u, Node *v);
  void deleteNodeHelper(Node *node, T key);
  void insertFix(Node *k);

 public:
  RedBlackTree<T>();
  ~RedBlackTree<T>();
  Node *searchTree(T k);
  Node *minimum(Node *node);
  Node *maximum(Node *node);
  Node *successor(Node *x);
  Node *predecessor(Node *x);
  void leftRotate(Node *x);
  void rightRotate(Node *x);
  void insert(T key);
  Node *getRoot() { return this->root; }
  void deleteNode(T data) { deleteNodeHelper(this->root, data); }
};

template <typename T>
struct RedBlackTree<T>::Node {
  T data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

template <typename T>
class RedBlackTree<T>::RedBlackTreeIterator {
 public:
  RedBlackTreeIterator() noexcept;
  RedBlackTreeIterator(const RedBlackTreeIterator &it) noexcept : ptr(it) {}
  RedBlackTreeIterator(const Node &node_ptr) noexcept : ptr(node_ptr) {}
  ~RedBlackTreeIterator() noexcept;

  RedBlackTreeIterator &operator=(const RedBlackTreeIterator &other) noexcept {
    ptr = other.ptr;
    return *this;
  }

  bool operator==(const RedBlackTreeIterator &other) const noexcept {
    return ptr == other.ptr;
  }

  bool operator!=(const RedBlackTreeIterator &other) const noexcept {
    return ptr != other.ptr;
  }

  T &operator*() { return ptr->data; }

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
    ptr = prev(ptr);
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
  Node *next(const RedBlackTreeIterator &root) noexcept {
    if (root.ptr->right == nullptr) {
      Node *parent = root.ptr->parent;
      while (parent) {
        if (parent->data > root.ptr->data) {
          return parent;
        }
        parent = parent->parent;
      }
      return nullptr;
    }
    Node *right = root.ptr->right;
    while (right->left) right = right->left;
    return right;
  }

  Node *prev(const RedBlackTreeIterator &root) noexcept {
    if (root.ptr->left == nullptr) {
      Node *parent = root.ptr->parent;
      while (parent) {
        if (parent->data < root.ptr->data) {
          return parent;
        }
        parent = parent->parent;
      }
      return nullptr;
    }
    Node *left = root.ptr->left;
    while (left->right) left = left->right;
    return left;
  }

  Node *ptr;
};

template <typename T>
RedBlackTree<T>::RedBlackTree() {
  TNULL = new Node;
  TNULL->color = 0;
  TNULL->left = nullptr;
  TNULL->right = nullptr;
  root = TNULL;
}

template <typename T>
RedBlackTree<T>::~RedBlackTree() {
  deleteNode(root->data);
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::searchTree(T k) {
  return searchTreeHelper(this->root, k);
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::minimum(Node *node) {
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::maximum(Node *node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::successor(Node *x) {
  if (x->right != TNULL) {
    return minimum(x->right);
  }

  Node *y = x->parent;
  while (y != TNULL && x == y->right) {
    x = y;
    y = y->parent;
  }
  return y;
}

template <typename T>
typename RedBlackTree<T>::Node *RedBlackTree<T>::predecessor(Node *x) {
  if (x->left != TNULL) return maximum(x->left);

  Node *y = x->parent;
  while (y != TNULL && x == y->left) {
    x = y;
    y = y->parent;
  }

  return y;
}

template <typename T>
void RedBlackTree<T>::leftRotate(Node *x) {
  Node *y = x->right;
  x->right = y->left;
  if (y->left != TNULL) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename T>
void RedBlackTree<T>::rightRotate(Node *x) {
  Node *y = x->left;
  x->left = y->right;
  if (y->right != TNULL) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == nullptr) {
    this->root = y;
  } else if (x == x->parent->right) {
    x->parent->right = y;
  } else {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
}

// Inserting a node
template <typename T>
void RedBlackTree<T>::insert(T key) {
  Node *node = new Node;
  node->parent = nullptr;
  node->data = key;
  node->left = TNULL;
  node->right = TNULL;
  node->color = 1;

  Node *y = nullptr;
  Node *x = this->root;

  while (x != TNULL) {
    y = x;
    if (node->data < x->data) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  node->parent = y;
  if (y == nullptr) {
    root = node;
  } else if (node->data < y->data) {
    y->left = node;
  } else {
    y->right = node;
  }

  if (node->parent == nullptr) {
    node->color = 0;
    return;
  }

  if (node->parent->parent == nullptr) return;

  insertFix(node);
}

#endif
