#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <functional>
#include <iostream>

template <typename T, typename Compare = std::less<T>> class RedBlackTree {
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

  RedBlackNode* root = nullptr;
  Compare comp;

  /**
   * Color Helper Methods
   */
  Color get_color(RedBlackNode* node) const {
    return node ? node->color : BLACK;
  }

  bool is_red(RedBlackNode* node) const { return get_color(node) == RED; }

  bool is_black(RedBlackNode* node) const { return get_color(node) == BLACK; }

  /**
   * Relationship Helper Methods
   */
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

  /**
   * Rotation Methods
   */
  void rotate_left(RedBlackNode* node) {
    RedBlackNode* new_root = node->right;
    node->right = new_root->left;

    if (new_root->left != nullptr) {
      new_root->left->parent = node;
    }

    new_root->parent = node->parent;
    if (node->parent == nullptr) {
      root = new_root;
    } else if (node == node->parent->left) {
      node->parent->left = new_root;
    } else {
      node->parent->right = new_root;
    }

    new_root->left = node;
    node->parent = new_root;
  }

  void rotate_right(RedBlackNode* node) {
    RedBlackNode* new_root = node->left;
    node->left = new_root->right;

    if (new_root->right) {
      new_root->right->parent = node;
    }

    new_root->parent = node->parent;

    if (!node->parent) {
      root = new_root;
    } else if (node == node->parent->right) {
      node->parent->right = new_root;
    } else {
      node->parent->left = new_root;
    }

    new_root->right = node;
    node->parent = new_root;
  }

  /**
   * Insertion Methods
   */
  RedBlackNode* bst_insert(RedBlackNode*& node, const T& value) {
    if (!node) {
      node = new RedBlackNode(value);
      return node;
    }

    if (comp(value, node->data)) {
      RedBlackNode* inserted = bst_insert(node->left, value);
      node->left->parent = node;
      return inserted;
    } else if (comp(node->data, value)) {
      RedBlackNode* inserted = bst_insert(node->right, value);
      node->right->parent = node;
      return inserted;
    }

    return node; // Ignore if value is duplicate
  }

  void fix_insert(RedBlackNode* node) {
    if (node == root) {
      return;
    }

    RedBlackNode* parent = node->parent;

    if (is_black(parent)) {
      return;
    }

    RedBlackNode* gp = get_grandparent(node);

    if (gp == nullptr) {
      return;
    }

    RedBlackNode* uncle = get_uncle(node);

    if (is_red(uncle)) {
      parent->color = BLACK;
      uncle->color = BLACK;
      gp->color = RED;

      fix_insert(gp);
      return;
    }

    // LL Rotation
    if (parent == gp->left && node == parent->left) {
      parent->color = BLACK;
      gp->color = RED;

      rotate_right(gp);
    } else if (parent == gp->left && node == parent->right) {
      // LR Rotation
      rotate_left(parent);
      fix_insert(parent);
    } else if (parent == gp->right && node == parent->right) {
      // RR Rotation
      parent->color = BLACK;
      gp->color = RED;

      rotate_left(gp);
    } else if (parent == gp->right && node == parent->left) {
      rotate_right(parent);
      fix_insert(parent);
    }
  }

  /**
   * Utility Methods
   */
  void inorder(RedBlackNode* node) const {
    if (!node)
      return;

    inorder(node->left);
    std::cout << node->data << " ";
    inorder(node->right);
  }

  bool search(RedBlackNode* node, const T& value) const {
    if (!node) {
      return false;
    }

    if (this->comp(value, node->data)) {
      return search(node->left, value);
    }

    if (this->comp(node->data, value)) {
      return search(node->right, value);
    }

    return true; // Equal
  }

  void cleanup(RedBlackNode* node) {
    if (!node) {
      return;

      cleanup(node->left);
      cleanup(node->right);

      delete node;
    }
  }

public:
  ~RedBlackTree() { cleanup(root); }

  void insert(const T& value) {
    RedBlackNode* inserted_node = bst_insert(root, value);
    fix_insert(inserted_node);
    root->color = BLACK;
  }

  void print_inorder() { inorder(root); }

  bool search(const T& value) { return search(root, value); }
};

#endif