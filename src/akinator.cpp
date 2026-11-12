#include "../include/akinator.h"

treeNode_t *loadTree(const char *fileName, treeNode_t *currentNode)
{
    FILE *filePointer = NULL;

    filePointer = fopen(fileName, "r");

    char *treeBuffer = NULL;

    struct stat fileInfo;
    if (stat(fileName, &fileInfo) == -1)
        return NULL;

    if ((treeBuffer = (char *)(calloc((size_t)fileInfo.st_size + 1, sizeof(char)))) == NULL)
        return NULL;

    fread(treeBuffer, sizeof(char), (size_t)fileInfo.st_size, filePointer);

    fclose(filePointer);

    char *string = (char *)calloc(256 + 1, sizeof(char)); // 1 for \0

    size_t index = 1;

    treeNode_t *root = loadNode(treeBuffer, currentNode, NULL, &index, string);

    free(treeBuffer);
    free(string);

    return root;
}

treeNode_t *loadNode(char *treeBuffer, treeNode_t *currentNode, treeNode_t *parent, size_t *index, char *string)
{
    sscanf(&treeBuffer[*index], "%256[^()]", string);

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

