#include "binaryTree.h"
#include "customWarning.h"

#define FREE_(field) { \
  free(field);         \
  field = NULL;        \
}

binaryTreeError binaryTreeInitialize(binaryTree *tree, elem_t rootData) {
  customWarning(tree     != NULL, TREE_BAD_POINTER);

  node *treeRoot = (node *)calloc(1, sizeof(node));
  customWarning(treeRoot != NULL, NODE_BAD_POINTER);

  tree->root        = treeRoot;
  tree->root->data  = rootData;
  tree->root->left  =     NULL;
  tree->root->right =     NULL;
  tree->root->left  =     NULL;

  return NO_ERRORS;
}

binaryTreeError binaryTreeDestruct(node *currentNode) {
  customWarning(currentNode != NULL, NODE_BAD_POINTER);

  // идея: опускаемся сначала в самый левый низ, оттуда начинаем подниматься по родителю рекурсией пока parent не NULL (это root),
  // зачищаем каждую ноду

  // затем также идем в самый правый низ, рекурсией поднимаемся по родителю пока parent не NULL (это root)
  // зачищаем каждую ноду

  // зачищаем root

  // нет хуйня какая

  return NO_ERRORS;
}

binaryTreeError binaryTreeNodeCreate(binaryTree *tree, elem_t data) {
  customWarning(tree     != NULL, TREE_BAD_POINTER);

  node *treeNode = (node *)calloc(1, sizeof(node));
  customWarning(treeNode != NULL, TREE_BAD_POINTER);

  treeNode->data   = data;
  treeNode->left   = NULL;
  treeNode->right  = NULL;
  treeNode->parent = NULL;

  if (binaryTreeNodeLink(tree->root, treeNode) == NODE_VALUE_EXIST) {
    FREE_(treeNode);
  };

  return NO_ERRORS;
}

binaryTreeError binaryTreeNodeLink(node *parentNode, node *node) {
  customWarning(parentNode != NULL, TREE_BAD_POINTER);
  customWarning(node       != NULL, NODE_BAD_POINTER);

  elem_t parentValue = parentNode->data;
  elem_t nodeValue   = node->data;

  // ! SAME VALUE
  if (nodeValue == parentValue) {
    return NODE_VALUE_EXIST;
  }
  // ! SAME VALUE

  // ! ON RIGHT
  if (nodeValue > parentValue) {
    if (parentNode->right == NULL) {
      parentNode->right = node;
      node->parent      = parentNode;
    }

    else {
      parentNode = parentNode->right;
      binaryTreeNodeLink(parentNode, node);
    }
  }
  // ! ON RIGHT

  // ! ON LEFT
  if (nodeValue < parentValue) {
    if (parentNode->left == NULL) {
      parentNode->left = node;
      node->parent     = parentNode;
    }

    else {
      parentNode = parentNode->left;
      binaryTreeNodeLink(parentNode, node);
    }
  }
  // ! ON LEFT

  return NO_ERRORS;
}

binaryTreeError printBinaryTree(node *node) {
  customWarning(node != NULL, NODE_BAD_POINTER);

  printf("(");

  if (node->left) {
    printBinaryTree(node->left);
  }

  printf(SPECIFIER_ELEM_T, node->data);

  if (node->right) {
    printBinaryTree(node->right);
  }

  printf(")");

  return NO_ERRORS;
}