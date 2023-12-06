#ifndef RB_TREE_H
#define RB_TREE_H

#include <memory>

template <typename T, typename ValueType = T,
          typename Allocator = std::allocator<T>>
class RedBlackTree {
 private:
  struct Node;
  Node *root;
  Node *TNULL;
  unsigned _size = 0;

  using node_allocator =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

  node_allocator node_alloc;

  Node *searchTreeHelper(Node *node, T key);
  void deleteFix(Node *x);
  void rbTransplant(Node *u, Node *v);
  void deleteNodeHelper(Node *node, T key);
  void insertFix(Node *k);

 public:
  class RedBlackTreeIterator;
  class RedBlackTreeConstIterator;

  using iterator = RedBlackTreeIterator;
  using const_iterator = RedBlackTreeConstIterator;

  RedBlackTree<T, ValueType, Allocator>();
  ~RedBlackTree<T, ValueType, Allocator>();
  Node *searchTree(T k);
  Node *minimum(Node *node);
  Node *maximum(Node *node);
  Node *getNullNode();
  void leftRotate(Node *x);
  void rightRotate(Node *x);
  void insert(T key);
  Node *getRoot() { return this->root; }
  void deleteNode(T key) { deleteNodeHelper(this->root, key); }

  iterator begin() { return iterator(minimum(root)); }
  const_iterator begin() const { return const_iterator(minimum(root)); }
  iterator end() { return iterator(maximum(root))++; }
  const_iterator end() const { return const_iterator(maximum(root))++; }
  unsigned size() const noexcept { return _size; }
  bool empty() const noexcept { return _size == 0; }
};

template <typename T, typename ValueType, typename Allocator>
struct RedBlackTree<T, ValueType, Allocator>::Node {
  T key;
  ValueType value;
  Node *parent, *left, *right;
  int color;

  Node()
      : key(),
        value(),
        parent(nullptr),
        left(nullptr),
        right(nullptr),
        color() {}
};

template <typename T, typename ValueType, typename Allocator>
RedBlackTree<T, ValueType, Allocator>::RedBlackTree() {
  TNULL = node_alloc.allocate(1);
  node_alloc.construct(TNULL);
  root = TNULL;
}

template <typename T, typename ValueType, typename Allocator>
RedBlackTree<T, ValueType, Allocator>::~RedBlackTree() {
  while (root != TNULL) deleteNode(root->key);
  // delete TNULL;
  // node_alloc.destroy(TNULL);
  node_alloc.deallocate(TNULL, 1);
}

template <typename T, typename ValueType, typename Allocator>
typename RedBlackTree<T, ValueType, Allocator>::Node *
RedBlackTree<T, ValueType, Allocator>::searchTreeHelper(Node *node, T key) {
  if (node == TNULL || key == node->key) {
    return node;
  }

  if (key < node->key) {
    return searchTreeHelper(node->left, key);
  }
  return searchTreeHelper(node->right, key);
}

// For balancing the tree after deletion
template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::deleteFix(Node *x) {
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

template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::rbTransplant(Node *u, Node *v) {
  if (u->parent == nullptr) {
    root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::deleteNodeHelper(Node *node,
                                                             T key) {
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
  _size--;
  // node_alloc.destroy(z);
  node_alloc.deallocate(z, 1);
  // delete z;
  if (y_original_color == 0) {
    deleteFix(x);
  }
}

// For balancing the tree after insertion
template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::insertFix(Node *k) {
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

template <typename T, typename ValueType, typename Allocator>
typename RedBlackTree<T, ValueType, Allocator>::Node *
RedBlackTree<T, ValueType, Allocator>::searchTree(T k) {
  return searchTreeHelper(this->root, k);
}

template <typename T, typename ValueType, typename Allocator>
typename RedBlackTree<T, ValueType, Allocator>::Node *
RedBlackTree<T, ValueType, Allocator>::minimum(Node *node) {
  while (node->left != TNULL) {
    node = node->left;
  }
  return node;
}

template <typename T, typename ValueType, typename Allocator>
typename RedBlackTree<T, ValueType, Allocator>::Node *
RedBlackTree<T, ValueType, Allocator>::maximum(Node *node) {
  while (node->right != TNULL) {
    node = node->right;
  }
  return node;
}

template <typename T, typename ValueType, typename Allocator>
typename RedBlackTree<T, ValueType, Allocator>::Node *
RedBlackTree<T, ValueType, Allocator>::getNullNode() {
  return TNULL;
}

template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::leftRotate(Node *x) {
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

template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::rightRotate(Node *x) {
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
template <typename T, typename ValueType, typename Allocator>
void RedBlackTree<T, ValueType, Allocator>::insert(T key) {
  Node *node = node_alloc.allocate(1);
  node_alloc.construct(node);

  _size++;
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

#include "rb_tree_const_iterator.h"
#include "rb_tree_iterator.h"

#endif
