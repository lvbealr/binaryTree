#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

#include <cstdlib>
#include <ctime>
#include <cinttypes>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

#include "binaryTreeDef.h"
#include "customWarning.h"
#include "binaryTreeDump.h"
#include "consoleParser.h"

#define DUMP_(treePtr) { \
  strncpy((treePtr)->infoData->lastUsedFileName,     __FILE__,            MAX_FILE_NAME_SIZE); \
  strncpy((treePtr)->infoData->lastUsedFunctionName, __PRETTY_FUNCTION__, MAX_FILE_NAME_SIZE); \
  (treePtr)->infoData->lastUsedLine  =               __LINE__                                ; \
  binaryTreeDump(treePtr);                                                                     \
}

#define SAVE_DUMP_IMAGE(treePtr) {                                      \
  DUMP_(tree);                                                          \
                                                                        \
  char *buffer = (char *)calloc(MAX_CMD_BUFFER_SIZE, sizeof(char));     \
  customWarning(buffer != NULL, BAD_BUFFER_POINTER);                    \
                                                                        \
  char *newFileName = (char *)calloc(MAX_FILE_NAME_SIZE, sizeof(char)); \
  customWarning(newFileName != NULL, BAD_FILE_NAME_POINTER);            \
                                                                        \
  strncpy(newFileName, (treePtr)->infoData->htmlDumpPath,               \
  strlen((treePtr)->infoData->htmlDumpPath) - strlen(".html"));         \
                                                                        \
  snprintf(buffer, MAX_CMD_BUFFER_SIZE, "dot -Tsvg %s -o %s.svg",       \
          (treePtr)->infoData->dumpFileName, newFileName);              \
  system(buffer);                                                       \
                                                                        \
  FREE_(buffer);                                                        \
  FREE_(newFileName);                                                   \
}

#define BINARY_TREE_INITIALIZE(pointer) {                               \
  treeInitialize    (pointer);                                          \
  treeInfoInitialize(pointer, __FILE__, __PRETTY_FUNCTION__, __LINE__); \
  parseConsole      (argc, argv, pointer);                              \
  binaryTreeSetInfo (pointer);                                          \
}

template<typename DT>
inline binaryTreeError treeInitialize  (binaryTree<DT> *tree) {
  customWarning(tree != NULL, TREE_NULL_POINTER);

  if (nodeInitialize(tree, &tree->root) != NO_ERRORS) {
    return ROOT_NULL_POINTER;
  }

  tree->root->left  = NULL;
  tree->root->right = NULL;

  // TODO VERIFY

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError treeDestruct(binaryTree<DT> *tree) {
  customWarning(tree != NULL, TREE_NULL_POINTER);

  SAVE_DUMP_IMAGE(tree);

  if (tree->root) {
    nodeDestruct(tree, &(tree->root));
  }

  DUMP_(tree);

  binaryTreeInfoDestruct(tree);

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError nodeInitialize  (binaryTree<DT> *tree, node<DT>      **currentNode) {
  *currentNode = (node<DT> *)calloc(1, sizeof(node<DT>));

  customWarning(*currentNode != NULL, NODE_NULL_POINTER);

  if (tree->infoData) {
    DUMP_(tree);
  }

  return NO_ERRORS;
}


template<typename DT>
inline binaryTreeError nodeLink        (binaryTree<DT> *tree, node<DT> *currentNode, linkDirection direction) {
  customWarning(tree        != NULL, TREE_NULL_POINTER);
  customWarning(currentNode != NULL, NODE_NULL_POINTER);

  node<DT> **childNode = NULL;

  switch (direction) {
    case LEFT:
      {
        childNode = &(currentNode->left);
        break;
      }

    case RIGHT:
      {
        childNode = &(currentNode->right);
        break;
      }

    case PARENT:
    default:
      {
        return NO_ERRORS;
        break;
      }
  }

  if (*childNode) {
    return NODE_USED;
  }

  node<DT> *newNode = {};
  nodeInitialize(tree, &newNode);

  newNode->parent = currentNode;
  newNode->left   =        NULL;
  newNode->right  =        NULL;
  *childNode      =     newNode;

  DUMP_(tree);

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError nodeDestruct(binaryTree<DT> *tree, node<DT> **currentNode) {
  customWarning(tree         != NULL, TREE_NULL_POINTER);
  customWarning(*currentNode != NULL, NODE_NULL_POINTER);

  if ((*currentNode)->left) {
    nodeDestruct(tree, &((*currentNode)->left));
  }

  if ((*currentNode)->right) {
    nodeDestruct(tree, &((*currentNode)->right));
  }

  DUMP_(tree);

  FREE_(*currentNode);

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError callPrintBinaryTree (binaryTree<DT> *tree, printType type, FILE *stream) {
  customWarning(tree   != NULL, TREE_NULL_POINTER);
  customWarning(stream != NULL, BAD_STREAM_POINTER);

  printBinaryTree(tree->root, type, stream);
}

template<typename DT>
inline binaryTreeError printBinaryTree     (node<DT>       *currentNode, printType type, FILE *stream) {
  customWarning(currentNode   != NULL, NODE_NULL_POINTER);
  customWarning(stream        != NULL, BAD_STREAM_POINTER);

  fprintf(stream, "( )");

  if (type == PREFIX) {
    printNode(currentNode);
  }

  if (currentNode->left) {
    printBinaryTree(currentNode, type, stream);
  }

  if (type == INFIX) {
    printNode(currentNode);
  }

  if (currentNode->right) {
    printBinaryTree(currentNode, type, stream);
  }

  if (type == POSTFIX) {
    printNode(currentNode);
  }

  fprintf(stream, " )");

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError printNode       (node<DT>       *currentNode, FILE *stream) {
  customWarning(currentNode != NULL, NODE_NULL_POINTER);

  if (currentNode->data) {
    fprintf(stream, "%d", currentNode->data);
  }

  else {
    fprintf(stream, "nul");
  }

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError treeInfoInitialize(binaryTree<DT> *tree, const char *fileName,
                                                                const char *funcName,
                                                                int         line) {
  customWarning(tree     != NULL, TREE_NULL_POINTER);
  customWarning(fileName != NULL, BAD_FILE_NAME_POINTER);
  customWarning(funcName != NULL, BAD_FUNC_NAME_POINTER);
  customWarning(line      > 0,    BAD_BORN_LINE_VALUE);

  tree->infoData                       = (binaryTreeInfo *)calloc(1, sizeof(binaryTreeInfo));

  customWarning(tree->infoData != NULL, BAD_INFO_POINTER);

  tree->infoData->bornFileName         = (char *)calloc(MAX_FILE_NAME_SIZE,   sizeof(char));
  tree->infoData->bornFunctionName     = (char *)calloc(MAX_BORN_FUNC_NAME,   sizeof(char));
  tree->infoData->bornLine             = line;
  tree->infoData->dumpFolderName       = (char *)calloc(MAX_DUMP_FOLDER_NAME, sizeof(char));
  tree->infoData->lastUsedFileName     = (char *)calloc(MAX_FILE_NAME_SIZE,   sizeof(char));
  tree->infoData->lastUsedFunctionName = (char *)calloc(MAX_BORN_FUNC_NAME,   sizeof(char));
  tree->infoData->lastUsedLine         = line;
  tree->infoData->htmlDumpPath         = (char *)calloc(MAX_DUMP_FILE_NAME,   sizeof(char));

  customWarning(tree->infoData->bornFileName         != NULL, INFO_NULL_POINTER);
  customWarning(tree->infoData->bornFunctionName     != NULL, INFO_NULL_POINTER);
  customWarning(tree->infoData->dumpFolderName       != NULL, INFO_NULL_POINTER);
  customWarning(tree->infoData->lastUsedFileName     != NULL, INFO_NULL_POINTER);
  customWarning(tree->infoData->lastUsedFunctionName != NULL, INFO_NULL_POINTER);
  customWarning(tree->infoData->htmlDumpPath         != NULL, INFO_NULL_POINTER);

  strncpy(tree->infoData->bornFileName,     fileName, MAX_FILE_NAME_SIZE);
  strncpy(tree->infoData->bornFunctionName, funcName, MAX_BORN_FUNC_NAME);

  return NO_ERRORS;
}

template<typename DT>
inline binaryTreeError binaryTreeInfoDestruct(binaryTree<DT> *tree) {
  customWarning(tree != NULL, TREE_NULL_POINTER);

  FREE_(tree->infoData->bornFileName        );
  FREE_(tree->infoData->bornFunctionName    );
  FREE_(tree->infoData->dumpFolderName      );
  tree->infoData->lastUsedFileName       = {}; // TODO
  FREE_(tree->infoData->lastUsedFileName    );
  tree->infoData->lastUsedFunctionName   = {}; // TODO
  FREE_(tree->infoData->lastUsedFunctionName);
  FREE_(tree->infoData->htmlDumpPath        );

  tree->infoData->dumpFileName = {};
  tree->infoData->bornLine     = 0;

  FREE_(tree->infoData);

  return NO_ERRORS;
}

template<typename DT>
static char *setDumpFileName(binaryTree<DT> *tree) {
  const time_t currentTime = time(NULL);
  tm localTime             = *localtime(&currentTime);

  char *fileName = (char *)calloc(MAX_FILE_NAME_SIZE, sizeof(char));

  customWarning(fileName != NULL, NULL);

  snprintf(fileName, FILENAME_MAX, "%s/%.2d.%.2d.%.4d-%.2d:%.2d:%.2d.html",
                                    tree->infoData->dumpFolderName, localTime.tm_mday, localTime.tm_mon,
                                    localTime.tm_year + 1900,       localTime.tm_hour, localTime.tm_min, localTime.tm_sec);

  return fileName;
}

#endif // BINARY_TREE_H_