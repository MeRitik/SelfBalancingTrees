#include <bits/stdc++.h>
using namespace std;

template <typename T, typename Compare = less<T>> class SelfBalancingBST {
protected:
  struct Node {
    T data;
    Node *left;
    Node *right;
    int height;

    Node(const T &value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
  };

  Node *root;
  Compare comp;

  virtual Node *insert(Node *node, const T &value) = 0;
  virtual Node *remove(Node *node, const T &value) = 0;
  virtual Node *balance(Node *node) = 0;

  int height(Node *node) { return node ? node->height : 0; }

  void update_height(Node *node) {
    node->height = 1 + max(height(node->left), height(node->right));
  }

  Node *rotate_right(Node *node) {
    Node *left_child = node->left;
    Node *T2 = left_child->right;

    left_child->right = node;
    node->left = T2;

    update_height(node);
    update_height(left_child);

    return left_child;
  }

  bool search(Node *node, const T &value) const {
    if (!node)
      return false;

    if (!comp(value, node->data) && !comp(node->data, value))
      return true;

    if (comp(value, node->data))
      return search(node->left, value);

    return search(node->right, value);
  }
};

int main() { return 0; }