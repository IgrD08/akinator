#include "../include/tree.h"
#include "../include/akinator.h"

static void printMenu(treeNode_t **root);
static treeNode_t *searchElement(treeNode_t *node);
static void saveDataToFile(treeNode_t **root);
static void loadDataFromFile(treeNode_t **root);

int main()
{
    if (fileOpening(&logFile, "logs/graphDumpHtml.htm", "w") == 1)
    {
        return 1;
    }

    treeNode_t *root = NULL;

    printMenu(&root);

    treeDump(root);

    destroyTree(root);

    closeFile(&logFile);

    return 0;
}

void printMenu(treeNode_t **root)
{
    bool flag = 1;
    char callNumber = 0;
    treeNode_t *currentNode = NULL;

    do
    {
        printf("\033[34mAkinator\n"
               "0 - start searching\n"
               "1 - save database\n"
               "2 - open database\n"
               "q - exit\033[0m\n"
              );

        if (scanf("%c", &callNumber) != 1)
        {
            while (getchar() != '\n');
            continue;
        }

        switch (callNumber)
        {
            case '0':
            {
                while (getchar() != '\n');
                if ((currentNode = searchElement(*root)) == NULL)
                {
                    return;
                }

                printf("\033[34mDid you search %s? (y/n)\033[0m\n", currentNode->data);

                int answer = getchar();

                if (answer == 'y')
                {
                    printf("\033[34mThanks for playing\033[0m\n");
                }
                else if (answer == 'n')
                {
                    while (getchar() != '\n');

                    printf("\033[34mWould you like to add new element?\033[0m\n");
                    answer = getchar();

                    while (getchar() != '\n');

                    if (answer == 'y')
                    {
                        char newItem[256] = {};
                        char question[256] = {};

                        printf("\033[34mWhat was it?\033[0m\n");
                        scanf("%255[^\n]", newItem);

                        while (getchar() != '\n');

                        printf("\033[34mWhat is the difference between %s and %s? (Yes for %s)\033[0m\n",
                               currentNode->data, newItem, newItem);
                        scanf("%255[^\n]", question);

                        if (addToLeft(currentNode, newItem) == NULL)
                        {
                            fprintf(stderr, "ERROR: can't add element to left\n");

                            return;
                        }

                        if (addToRight(currentNode, currentNode->data) == NULL)
                        {
                            fprintf(stderr, "ERROR: can't add element to right\n");

                            return;
                        }

                        free(currentNode->data);
                        currentNode->data = strdup(question);
                    }
                    else if (answer == 'n')
                    {
                        continue;
                    }
                }
            }

                break;

            case '1':

                saveDataToFile(root);

                break;

            case '2':

                loadDataFromFile(root);

                break;

            case 'q':
            {
                flag = 0;
            }

            default:

                break;
        }

        while (getchar() != '\n');

    }while(flag);

    return;
}

treeNode_t *searchElement(treeNode_t *node)
{
    if (node == NULL)
    {
        return node;
    }

    if (node->left != NULL || node->right != NULL)
    {
        printf("\033[34mThe object you have in mind is %s? (y/n)\033[0m\n", node->data);

        int answer = getchar();

        if (answer == 'y')
        {
            while (getchar() != '\n');

            return node->left ? searchElement(node->left) : searchElement(node);
        }
        else if (answer == 'n')
        {
            while (getchar() != '\n');

            return node->right ? searchElement(node->right) : searchElement(node);
        }
        else
        {
            while (getchar() != '\n');

            return searchElement(node);
        }
    }

    return node;
}

void saveDataToFile(treeNode_t **root)
{
    printf("\033[34mFile name to open:\033[0m\n");

    char fileName[MAX_FILE_LEN] = {};
    scanf("%s", fileName);

    treePrint(*root, fileName);

    return;
}

void loadDataFromFile(treeNode_t **root)
{
    printf("\033[34mFile name to open:\033[0m\n");

    char fileName[MAX_FILE_LEN] = {};
    scanf("%s", fileName);

    if ((*root = loadTree(fileName, *root)) == NULL)
    {
        fprintf(stderr, "ERROR: can't load tree\n");

        return;
    }

    return;
}
