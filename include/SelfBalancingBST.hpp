#ifndef SELF_BALANCING_BST_HPP
#define SELF_BALANCING_BST_HPP

#include <algorithm>
#include <iostream>

template <typename T, typename Compare = less<T>> class SelfBalancingBST {
protected:
  struct Node {
    T data;
    Node* left;
    Node* right;
    int height;

    Node(const T& value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
  };

  Node* root;
  Compare comp;

  virtual Node* insert(Node* node, const T& value) = 0;
  virtual Node* remove(Node* node, const T& value) = 0;
  virtual Node* balance(Node* node) = 0;

  int height(Node* node) const { return node ? node->height : 0; }

  void update_height(Node* node) {
    if (!node)
      return;

    node->height = 1 + max(height(node->left), height(node->right));
  }

  Node* rotate_right(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
  }

  Node* rotate_left(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
  }

  bool search(Node* node, const T& value) const {
    if (!node)
      return false;

    if (!comp(value, node->data) && !comp(node->data, value))
      return true;

    if (comp(value, node->data))
      return search(node->left, value);

    return search(node->right, value);
  }

  void inorder(Node* node) const {
    if (!node)
      return;

    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
  }

public:
  SelfBalancingBST() : root(nullptr) {}

  void insert(const T& value) { root = insert(root, value); }

  void remove(const T& value) { root = remove(root, value); }

  bool search(const T& value) const { return search(root, value); }

  void print_inorder() const {
    inorder(root);
    cout << endl;
  }
};

#endif