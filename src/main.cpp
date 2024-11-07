#include "binaryTree.h"

int main() {
  binaryTree tree = {};

  binaryTreeInitialize(&tree, "ДЕД");

  binaryTreeNodeCreate(&tree, "ЛОХ");

  printBinaryTree     (tree.root);
}