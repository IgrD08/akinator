#ifndef AKINATOR_H
#define AKINATOR_H

#include <string.h>
#include <sys/stat.h>
#include "tree.h"

treeNode_t *loadTree        (const char *fileName, treeNode_t *node);
treeNode_t *loadNode        (char *treeBuffer, treeNode_t *currentNode, treeNode_t *parent, size_t *index, char *string);

#endif
