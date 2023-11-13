#ifndef RB_TREE_H
#define RB_TREE_H

struct Node {
  int data;
  Node *parent;
  Node *left;
  Node *right;
  int color;
};

class RedBlackTree {
 private:
  Node *root;
  Node *TNULL;

  void initializeNULLNode(Node *node, Node *parent);
  Node *searchTreeHelper(Node *node, int key);
  void deleteFix(Node *x);
  void rbTransplant(Node *u, Node *v);
  void deleteNodeHelper(Node *node, int key);
  void insertFix(Node *k);

 public:
  RedBlackTree();
  Node *searchTree(int k);
  Node *minimum(Node *node);
  Node *maximum(Node *node);
  Node *successor(Node *x);
  Node *predecessor(Node *x);
  void leftRotate(Node *x);
  void rightRotate(Node *x);
  void insert(int key);
  Node *getRoot() { return this->root; }
  void deleteNode(int data) { deleteNodeHelper(this->root, data); }
};

#endif
