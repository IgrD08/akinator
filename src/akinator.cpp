#include "../include/akinator.h"

static treeNode_t *loadNode(char *treeBuffer, treeNode_t *currentNode, treeNode_t *parent, size_t *index, char *string);

treeNode_t *loadTree(const char *fileName, treeNode_t *currentNode)
{
    FILE *filePointer = NULL;

    if (fileOpening(&filePointer, fileName, "r") == 1)
    {
        return NULL;
    }

    struct stat fileInfo;
    if (stat(fileName, &fileInfo) == -1)
        return NULL;

    char *treeBuffer = NULL;
    if ((treeBuffer = (char *)(calloc((size_t)fileInfo.st_size + 1, sizeof(char)))) == NULL)
    {
        fprintf(stderr, "ERROR: allocation error\n");

        return NULL;
    }

    if (fread(treeBuffer, sizeof(char), (size_t)fileInfo.st_size, filePointer) < (size_t)fileInfo.st_size)
    {
        fprintf(stderr, "ERROR: incorrect reading from file\n");

        return NULL;
    }

    closeFile(&filePointer);

    char *string = NULL;
    if ((string = (char *)calloc(256 + 1, sizeof(char))) == NULL) //NOTE - 1 for \0
    {
        fprintf(stderr, "ERROR: allocation error\n");

        return NULL;
    }

    size_t index = 1;
    treeNode_t *root = NULL;
    if ((root = loadNode(treeBuffer, currentNode, NULL, &index, string)) == NULL)
    {
        fprintf(stderr, "ERROR: can't load node: %p\n", currentNode);

        return NULL;
    }

    free(treeBuffer);
    free(string);

    return root;
}

treeNode_t *loadNode(char *treeBuffer, treeNode_t *currentNode, treeNode_t *parent, size_t *index, char *string)
{
    if (sscanf(&treeBuffer[*index], "%256[^()]", string) == -1)
    {
        fprintf(stderr, "ERROR: incorrect reading from buffer\n");

        return NULL;
    }

    *index += strlen(string);

    if (strcmp(string, "nil") == 0)
    {
        (*index)++;

        return NULL;
    }

    currentNode = createNode(parent, string);

    if (treeBuffer[*index] == '(')
    {
        (*index)++;

        currentNode->left = loadNode(treeBuffer, currentNode->left, currentNode, index, string);
    }

    if (treeBuffer[*index] == '(')
    {
        (*index)++;

        currentNode->right = loadNode(treeBuffer, currentNode->right, currentNode, index, string);
    }

    if (treeBuffer[*index] == ')')
    {
        (*index)++;
    }

    return currentNode;
}

