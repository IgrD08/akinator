#include "../include/tree.h"

int main()
{
    logFile = fopen("logs/graphDumpHtml.htm", "w");

    fprintf(logFile, "<pre>\n");

    treeNode_t *root = NULL;

    root = createNode(root, (const char *)"10");
    treeNode_t *sex = addToLeft(root, (const char *)"5");
    addToLeft(sex, (const char *)"20");

    sex = nodeGoUp(sex);
    addToRight(sex, (const char *)"sixseven");

    treeDump(root);
    treePrint(root, (const char *)"sixseven.txt");

    destroyTree(root);

    fclose(logFile);

    return 0;
}
