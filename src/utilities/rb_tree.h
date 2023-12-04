#ifndef RB_TREE_H
#define RB_TREE_H

#include <iostream>
template <typename T, typename ValueType = T>
class RedBlackTree {
 private:
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
  class RedBlackTreeIterator;

  RedBlackTree<T, ValueType>();
  ~RedBlackTree<T, ValueType>();
  Node *searchTree(T k);
  Node *minimum(Node *node);
  Node *maximum(Node *node);
  Node *successor(Node *x);
  Node *predecessor(Node *x);
  Node *getNullNode();
  void leftRotate(Node *x);
  void rightRotate(Node *x);
  void insert(T key);
  Node *getRoot() { return this->root; }
  void deleteNode(T key) { deleteNodeHelper(this->root, key); }
};

template <typename T, typename ValueType>
struct RedBlackTree<T, ValueType>::Node {
  T key;
  ValueType value;
  Node *parent;
  Node *left;
  Node *right;
  int color;

  Node()
      : key(),
        value(),
        parent(nullptr),
        left(nullptr),
        right(nullptr),
        color(0) {}

  friend bool operator==(const typename RedBlackTree<T, ValueType>::Node &lhs,
                         const typename RedBlackTree<T, ValueType>::Node &rhs) {
    return lhs.value == rhs.value && lhs.parent == rhs.parent &&
           lhs.left == rhs.left && lhs.right == rhs.right &&
           lhs.color == rhs.color;
  }
  friend bool operator!=(const typename RedBlackTree<T, ValueType>::Node &lhs,
                         const typename RedBlackTree<T, ValueType>::Node &rhs) {
    return !(lhs == rhs);
  }
};

template <typename T, typename ValueType>
class RedBlackTree<T, ValueType>::RedBlackTreeIterator {
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

  T operator*() { return ptr->value; }

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
        if (parent->key > root->key) {
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
    if (root.ptr->left == Node()) {
      Node *parent = root.ptr->parent;
      while (parent) {
        if (parent->key < root.ptr->key) {
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

template <typename T, typename ValueType>
RedBlackTree<T, ValueType>::RedBlackTree() {
  TNULL = new Node();
  root = TNULL;
}

template <typename T, typename ValueType>
RedBlackTree<T, ValueType>::~RedBlackTree() {
  while (root != TNULL) deleteNode(root->key);
  delete TNULL;
}

template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::initializeNULLNode(Node *node, Node *parent) {
  node->key = {};
  node->parent = parent;
  node->left = nullptr;
  node->right = nullptr;
  node->color = 0;
}

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *
RedBlackTree<T, ValueType>::searchTreeHelper(Node *node, T key) {
  if (node == TNULL || key == node->key) {
    return node;
  }

  if (key < node->key) {
    return searchTreeHelper(node->left, key);
  }
  return searchTreeHelper(node->right, key);
}

// For balancing the tree after deletion
template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::deleteFix(Node *x) {
  Node *s;
  while (x != root && x->color == 0) {
    if (x == x->parent->left) {
      s = x->parent->right;
      if (s->color == 1) {
        s->color = 0;
        x->parent->color = 1;
        leftRotate(x->parent);
        s = x->parent->right;
      }

      if (s->left->color == 0 && s->right->color == 0) {
        s->color = 1;
        x = x->parent;
      } else {
        if (s->right->color == 0) {
          s->left->color = 0;
          s->color = 1;
          rightRotate(s);
          s = x->parent->right;
        }

        s->color = x->parent->color;
        x->parent->color = 0;
        s->right->color = 0;
        leftRotate(x->parent);
        x = root;
      }
    } else {
      s = x->parent->left;
      if (s->color == 1) {
        s->color = 0;
        x->parent->color = 1;
        rightRotate(x->parent);
        s = x->parent->left;
      }

      if (s->right->color == 0 && s->right->color == 0) {
        s->color = 1;
        x = x->parent;
      } else {
        if (s->left->color == 0) {
          s->right->color = 0;
          s->color = 1;
          leftRotate(s);
          s = x->parent->left;
        }

        s->color = x->parent->color;
        x->parent->color = 0;
        s->left->color = 0;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = 0;
}

template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::rbTransplant(Node *u, Node *v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::deleteNodeHelper(Node *node, T key) {
  Node *z = TNULL;
  Node *x, *y;
  while (node != TNULL) {
    if (node->key == key) {
      z = node;
    }

    if (node->key <= key) {
      node = node->right;
    } else {
      node = node->left;
    }
  }

  if (z == TNULL) {  // not found
    return;
  }

  y = z;
  int y_original_color = y->color;
  if (z->left == TNULL) {
    x = z->right;
    rbTransplant(z, z->right);
  } else if (z->right == TNULL) {
    x = z->left;
    rbTransplant(z, z->left);
  } else {
    y = minimum(z->right);
    y_original_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      rbTransplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    rbTransplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  delete z;
  if (y_original_color == 0) {
    deleteFix(x);
  }
}

// For balancing the tree after insertion
template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::insertFix(Node *k) {
  Node *u;
  while (k->parent->color == 1) {
    if (k->parent == k->parent->parent->right) {
      u = k->parent->parent->left;
      if (u->color == 1) {
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      } else {
        if (k == k->parent->left) {
          k = k->parent;
          rightRotate(k);
        }
        k->parent->color = 0;
        k->parent->parent->color = 1;
        leftRotate(k->parent->parent);
      }
    } else {
      u = k->parent->parent->right;

      if (u->color == 1) {
        u->color = 0;
        k->parent->color = 0;
        k->parent->parent->color = 1;
        k = k->parent->parent;
      } else {
        if (k == k->parent->right) {
          k = k->parent;
          leftRotate(k);
        }
        k->parent->color = 0;
        k->parent->parent->color = 1;
        rightRotate(k->parent->parent);
      }
    }
    if (k == root) {
      break;
    }
  }
  root->color = 0;
}

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *
RedBlackTree<T, ValueType>::searchTree(T k) {
  return searchTreeHelper(this->root, k);
}

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *RedBlackTree<T, ValueType>::minimum(
    Node *node) {
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *RedBlackTree<T, ValueType>::maximum(
    Node *node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *
RedBlackTree<T, ValueType>::successor(Node *x) {
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

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *
RedBlackTree<T, ValueType>::predecessor(Node *x) {
  if (x->left != TNULL) return maximum(x->left);

  Node *y = x->parent;
  while (y != TNULL && x == y->left) {
    x = y;
    y = y->parent;
  }

  return y;
}

template <typename T, typename ValueType>
typename RedBlackTree<T, ValueType>::Node *
RedBlackTree<T, ValueType>::getNullNode() {
  return TNULL;
}

template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::leftRotate(Node *x) {
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

template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::rightRotate(Node *x) {
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
template <typename T, typename ValueType>
void RedBlackTree<T, ValueType>::insert(T key) {
  Node *node = new Node;
  node->parent = nullptr;
  node->key = key;
  node->value = key;
  node->left = TNULL;
  node->right = TNULL;
  node->color = 1;

  Node *y = nullptr;
  Node *x = this->root;

  while (x != TNULL) {
    y = x;
    if (node->key < x->key) {
      x = x->left;
    } else {
      x = x->right;
    }
  }

  node->parent = y;
  if (y == nullptr) {
    root = node;
  } else if (node->key < y->key) {
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
