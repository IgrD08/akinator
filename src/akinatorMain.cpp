#include "../include/tree.h"
#include "../include/akinator.h"

void printMenu(treeNode_t *root);
treeNode_t *searchElement(treeNode_t *node);

int main(int argc, char *argv[])
{
    logFile = fopen("logs/graphDumpHtml.htm", "w");

    treeNode_t *root = NULL;

    root = loadTree("sixseven.txt", root);

    printMenu(root);

    treeDump(root);

    destroyTree(root);

    fclose(logFile);

    return 0;
}

void printMenu(treeNode_t *root)
{
    bool flag = 1;
    char callNumber = 0;
    treeNode_t *currentNode = NULL;

    do
    {
        printf("\033[34mAkinator\n"
               "0 - start searching\n"
               "1 - add new item\n"
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
                currentNode = searchElement(root);

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
                        scanf("%255s", newItem);

                        printf("\033[34mWhat is the difference between %s and %s? (Yes for %s)\033[0m\n", currentNode->data, newItem, currentNode->data);
                        scanf("%255s", question);

                        addToLeft(currentNode, newItem);
                        addToRight(currentNode, currentNode->data);

                        free(currentNode->data);
                        currentNode->data = strdup(question);
                    }
                    else if (answer == 'n')
                    {
                        break;
                    }
                }
            }

                break;

            case '1':
            {

            }

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

            return node->left? searchElement(node->left) : searchElement(node);
        }
        else if (answer == 'n')
        {
            while (getchar() != '\n');

            return node->right? searchElement(node->right) : searchElement(node);
        }
        else
        {
            while (getchar() != '\n');

            return searchElement(node);
        }
    }

    return node;
}
