#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <cstdlib>
#include <cinttypes>

#define SPECIFIER_ELEM_T " %s "

typedef const char* elem_t;
// typedef int elem_t;

// const elem_t POISON_VALUE = -666;

// TODO bigArray

struct node {
  elem_t data   =   {};
  node  *left   = NULL;
  node  *right  = NULL;
  node  *parent = NULL;
  // TODO связать ноды в список
};

struct binaryTree {
  node    *root      = NULL;
  uint64_t errorCode =   {};
};

enum binaryTreeError {
  NO_ERRORS        = 0,
  TREE_BAD_POINTER = 1,
  NODE_BAD_POINTER = 2,
  NODE_VALUE_EXIST = 3
};

// FUNCTION PROTOTYPES //
binaryTreeError binaryTreeInitialize(binaryTree *tree, elem_t rootData);
binaryTreeError binaryTreeDestruct  (node *currentNode                );
binaryTreeError binaryTreeNodeCreate(binaryTree *tree, elem_t data    );
binaryTreeError binaryTreeNodeLink  (node *parentNode, node  *node    );
binaryTreeError printBinaryTree     (node *node                       );
// FUNCTION PROTOTYPES //

#endif // BINARY_TREE_H_