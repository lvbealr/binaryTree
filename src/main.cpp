#include "binaryTree.h"

#include "getopt.h"

#include "consoleParser.h"

#define INIT_BINARY_TREE(treePtr, rootValue) {                                         \
  binaryTreeInitialize(treePtr, rootValue);                                            \
  binaryTreeInfoInitialize(treePtr, __FILE__, __PRETTY_FUNCTION__, __LINE__);          \
  parseConsole(argc, argv, treePtr);                                                   \
  binaryTreeSetInfo(treePtr);                                                          \
  DUMP_(treePtr);                                                                      \
}

int main(int argc, char *argv[]) {
  binaryTree<int> intTree = {};
  INIT_BINARY_TREE(&intTree, 100);

  binaryTreeNodeCreate(&intTree, 200);
  binaryTreeNodeCreate(&intTree, 12);
  binaryTreeNodeCreate(&intTree, 1488);
  binaryTreeNodeCreate(&intTree, 228);
  binaryTreeNodeCreate(&intTree, 50);
  binaryTreeNodeCreate(&intTree, 37);
  binaryTreeNodeCreate(&intTree, 98);
  binaryTreeNodeCreate(&intTree, 1002);
  binaryTreeNodeCreate(&intTree, 1323);
  binaryTreeNodeCreate(&intTree, 11);
  binaryTreeNodeCreate(&intTree, 2);

  binaryTreeDestruct(&intTree);
}