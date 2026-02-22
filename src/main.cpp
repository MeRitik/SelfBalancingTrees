#include "AVLTree.hpp"
#include <iostream>
using namespace std;

int main() {

  AVLTree<int, less<int>> tree; // greater<int>, less<int>, greater_equal<int>,
                                // less_equal<int>, etc.

  int values[] = {10, 20, 30, 40, 50, 25};

  for (int v : values) {
    cout << "Inserting: " << v << endl;
    tree.insert(v);

    cout << "Inorder: ";
    tree.print_inorder();
    cout << endl;
  }

  return 0;
}