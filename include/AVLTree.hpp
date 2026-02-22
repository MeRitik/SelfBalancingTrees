#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "SelfBalancingBST.hpp"

#include <algorithm>
#include <iostream>

using namespace std;

template <typename T, typename Compare = less<T>>
class AVLTree : public SelfBalancingBST<T, Compare> {
private:
  using Node = typename SelfBalancingBST<T, Compare>::Node;

  int balance_factor(Node* node) {
    return this->height(node->left) - this->height(node->right);
  }

  Node* balance(Node* node) override {
    if (!node)
      return node;

    this->update_height(node);

    int bf = balance_factor(node);

    // LEFT HEAVY
    if (bf > 1) {

      // LL Case
      if (balance_factor(node->left) >= 0)
        return this->rotate_right(node);

      // LR Case
      node->left = this->rotate_left(node->left);
      return this->rotate_right(node);
    }

    // RIGHT HEAVY
    if (bf < -1) {

      // RR Case
      if (balance_factor(node->right) <= 0)
        return this->rotate_left(node);

      // RL Case
      node->right = this->rotate_right(node->right);
      return this->rotate_left(node);
    }

    return node; // already balanced
  }

  Node* insert(Node* node, const T& value) override {

    if (!node)
      return new Node(value);

    if (this->comp(value, node->data))
      node->left = insert(node->left, value);
    else
      node->right = insert(node->right, value);

    return balance(node);
  }

  Node* find_min(Node* node) {
    while (node->left)
      node = node->left;
    return node;
  }

  Node* remove(Node* node, const T& value) override {
    if (!node)
      return node;

    if (this->comp(value, node->data))
      node->left = remove(node->left, value);

    else if (this->comp(node->data, value))
      node->right = remove(node->right, value);

    else {
      if (!node->left || !node->right) {

        Node* temp = node->left ? node->left : node->right;

        if (!temp) {
          temp = node;
          node = nullptr;
        } else {
          *node = *temp;
        }

        delete temp;
      }

      else {
        Node* successor = find_min(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
      }
    }

    if (!node)
      return node;

    return balance(node);
  }

public:
  void insert(const T& value) { this->root = insert(this->root, value); }

  void remove(const T& value) { this->root = remove(this->root, value); }
};

#endif