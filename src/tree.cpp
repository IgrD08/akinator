#include "../include/tree.h"
//MENTOR - add asserts
static void nodePrint           (treeNode_t *root, FILE *filePointer);
static void singleNodeDump(treeNode_t *root, int depth, FILE *filePointer);

treeNode_t *createNode(treeNode_t *parent, treeElem_t value)
{
    treeNode_t *newNode = (treeNode_t *)calloc(1, sizeof(treeNode_t));

    if (newNode == NULL)
    {
        return NULL;
    }

    char *copy = strdup(value);

    newNode->data = copy;

    newNode->parent = parent;

    // fprintf(logFile, "Tree after adding " SPEC " after %p:\n", newNode->data, newNode->parent);

    return newNode;
}

treeNode_t *addToLeft(treeNode_t *parent, treeElem_t value)
{
    if (parent == NULL || parent->left != NULL)
    {
        return NULL;
    }

    parent->left = createNode(parent, value);

    return parent->left;
}

treeNode_t *addToRight(treeNode_t *parent, treeElem_t value)
{
    if (parent == NULL || parent->right != NULL)
    {
        return NULL;
    }

    parent->right = createNode(parent, value);

    return parent->right;
}

treeNode_t *nodeGoLeft(treeNode_t *node)
{
    return (node != NULL) ? node->left : NULL;
}

treeNode_t *nodeGoRight(treeNode_t *node)
{
    return (node != NULL) ? node->right : NULL;
}

treeNode_t *nodeGoUp(treeNode_t *node)
{
   return (node != NULL) ? node->parent : NULL;
}

void deleteNode(treeNode_t *node)
{
    if (node)
    {
        if (node->left)
        {
            deleteNode(node->left);
        }

        if (node->right)
        {
            deleteNode(node->right);
        }

        free(node->data);

        free(node);
    }

    return;
}

void destroyTree(treeNode_t *root)
{
    deleteNode(root);

    return;
}

treeNode_t *treePrint(treeNode_t *root, const char *fileName)
{
    FILE *filePointerWrite = NULL;

    if (fileOpening(&filePointerWrite, fileName, "w") == 1)
    {
        return NULL;
    }

    nodePrint(root, filePointerWrite);

    fprintf(filePointerWrite, "\n");

    closeFile(&filePointerWrite);

    return root;
}

void nodePrint(treeNode_t *root, FILE *filePointer)
{
    fprintf(filePointer, "(");

    fprintf(filePointer, SPEC, root->data);

    if (root->left)
    {
        nodePrint(root->left, filePointer);
    }
    else
    {
        fprintf(filePointer, "(nil)");
    }

    if (root->right)
    {
        nodePrint(root->right, filePointer);
    }
    else
    {
        fprintf(filePointer, "(nil)");
    }

    fprintf(filePointer, ")");

    return;
}

void treeDump(treeNode_t *node)
{
    time_t timeInSeconds = time(NULL);

    tm *parsedTime = localtime(&timeInSeconds);

    char time[32] = {};

    strftime(time, 32, "%Y%m%d%H%M%S", parsedTime);

    timespec ts = {};

    clock_gettime(CLOCK_REALTIME, &ts);

    long millis = ts.tv_nsec / 1000000;

    char fileName[256] = {};

    snprintf(fileName, sizeof(fileName), "logs/img/%s%ld.dot", time, millis);

    FILE *filePointer = fopen(fileName, "w");

    fprintf(filePointer, "digraph\n{\n"
                         "\tnode[shape = Mrecord];\n");

    singleNodeDump(node, 0, filePointer);

    fprintf(filePointer, "}\n");

    fclose(filePointer);

    char command[256] = {};

    snprintf(command, sizeof(command), "dot -Tsvg logs/img/%s%ld.dot -o logs/img/%s%ld.svg", time, millis, time, millis);

    system(command);

    fprintf(logFile, "<img src= img/%s%ld.svg style = \"zoom: 65%%;\">\n", time, millis);

    return;
}

void singleNodeDump(treeNode_t *node, int depth, FILE *filePointer)
{
    if (node == NULL)
    {
        fprintf(stderr, "ERROR: can't draw node\n");

        return;
    }

    fprintf(filePointer, "\tnode%p[style = filled, label = \"{value = " SPEC " | address = %p |  parent = %p | { left = %p | right = %p }}\", fillcolor = \"#95ff72\", color = \"#259200\"];\n",
            node, node->data, node, node->parent, node->left, node->right);

    fprintf(filePointer, "\t rank%d[shape = point, width = 0, style = invis];\n", depth);

    fprintf(filePointer, "\t{ rank = same; node%p; rank%d }\n", node, depth);

    if (depth > 0)
    {
        fprintf(filePointer, "\trank%d -> rank%d [shape = point, style = invis];\n", depth - 1, depth);
    }

    if (node->left)
    {
        fprintf(filePointer, "\tnode%p -> node%p [label = \"Да\", color = \"#00fbda\"];\n", node, node->left);

        singleNodeDump(node->left, depth + 1, filePointer);
    }

    if (node->right)
    {
        fprintf(filePointer, "\tnode%p -> node%p [label = \"Нет\", color = \"#ff00e6\"];\n", node, node->right);

        singleNodeDump(node->right, depth + 1, filePointer);
    }

    return;
}

