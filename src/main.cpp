#include "binaryTreeDef.h"
#include "binaryTree.h"

int main(int argc, char *argv[]) {
  binaryTree<int> tree = {};
  BINARY_TREE_INITIALIZE(&tree);

  nodeLink(&tree, tree.root, LEFT);

  nodeLink(&tree, tree.root->left, LEFT);

  treeDestruct(&tree);

  return 0;
}