#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include "SelfBalancingBST.hpp"

#include <iostream>

using namespace std;

template <typename T, typename Compare = less<T>>
class RedBlackTree : public SelfBalancingBST<T, Compare> {
private:
  enum Color { RED, BLACK };

  struct RedBlackNode {
    T data;
    RedBlackNode* left;
    RedBlackNode* right;
    RedBlackNode* parent;
    Color color;

    RedBlackNode(const T& value)
        : data(value), left(nullptr), right(nullptr), parent(nullptr),
          color(RED) {}
  };

  RedBlackNode root = nullptr;

  // null nodes treated as BLACK
  Color get_color(RedBlackNode* node) const {
    return node ? node->color : BLACK;
  }

  bool is_red(RedBlackNode* node) const { return get_color(node) == RED; }

  bool is_black(RedBlackNode* node) const { return get_color(node) == BLACK; }

  RedBlackNode* get_grandparent(RedBlackNode* node) const {
    if (node && node->parent)
      return node->parent->parent;
    return nullptr;
  }

  RedBlackNode* get_uncle(RedBlackNode* node) const {
    RedBlackNode* gp = get_grandparent(node);

    if (!gp)
      return nullptr;

    if (node->parent == gp->left)
      return gp->right;

    return gp->left;
  }
};

#endif