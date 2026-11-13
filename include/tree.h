#ifndef TREE_H
#define TREE_H

typedef char * treeElem_t;
#define SPEC "%s"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "logger.h"
#include "treeVerify.h"
#include "graphicAkinator.h"

const int MAX_FILE_LEN = 100;

struct treeNode_t
{
    treeElem_t data;
    treeNode_t *left;
    treeNode_t *right;
    treeNode_t *parent;
};

treeNode_t * createNode  (treeNode_t *parent, treeElem_t value);
treeNode_t * addToLeft   (treeNode_t *parent, treeElem_t value);
treeNode_t * addToRight  (treeNode_t *parent, treeElem_t value);
void deleteNode          (treeNode_t *node);
void destroyTree         (treeNode_t *root);
treeNode_t * nodeGoLeft  (treeNode_t *node);
treeNode_t * nodeGoRight (treeNode_t *node);
treeNode_t * nodeGoUp    (treeNode_t *node);
void treePrint           (treeNode_t *root, FILE *filePointer);
void nodePrint           (treeNode_t *root, FILE *filePointer);
void singleNodeDump      (treeNode_t *root, int depth, FILE *filePointer); //TODO - сделать закрытие реализации, то есть перенести объявление в cpp и сделать static
void treeDump            (treeNode_t *node);

#endif
