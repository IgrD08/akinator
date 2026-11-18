#include "../include/tree.h"
#include "../include/akinator.h"
#include "../include/graphicAkinator.h"

static void windowSettings(void);
static void stateHandling(state_t *state, bool *needQuit, char inputData[MAX_CHARS], int *letterCount, treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount, treeNode_t **currentNode);
static state_t loadDataFromFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount);
static state_t saveDataToFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount);
static state_t searchingProcessing(treeNode_t **root, treeNode_t **currentNode);
static state_t askingProcessing(treeNode_t **currentNode);
static state_t inputWhoProcessing(char inputData[MAX_CHARS], int *letterCount);
static state_t inputDiffProcessing(treeNode_t **currentNode, char inputData[MAX_CHARS], int *letterCount, char fileName[MAX_FILE_LEN], int *fileLetterCount);

const button_t yes = {.top = {.x = 50,  .y = SCREEN_HEIGHT / 2}, .bottom = {.x = 450, .y = SCREEN_HEIGHT / 2 + 80}};
const button_t no  = {.top = {.x = 550, .y = SCREEN_HEIGHT / 2}, .bottom = {.x = 950, .y = SCREEN_HEIGHT / 2 + 80}};

int main()
{
    if (fileOpening(&logFile, "logs/logger.htm", "w") == 1)
    {
        return 1;
    }

    fprintf(logFile, "<pre>\n");

    windowSettings();

    menuButtonsCoordinates_t menuButtons = {
                                            .game = {.top = {.x = BUTTON_GAME_TOP_X, .y = BUTTON_GAME_TOP_Y}, .bottom = {.x = BUTTON_GAME_BOTTOM_X, .y = BUTTON_GAME_BOTTOM_Y}},
                                            .save = {.top = {.x = BUTTON_SAVE_TOP_X, .y = BUTTON_SAVE_TOP_Y}, .bottom = {.x = BUTTON_SAVE_BOTTOM_X, .y = BUTTON_SAVE_BOTTOM_Y}},
                                            .load = {.top = {.x = BUTTON_LOAD_TOP_X, .y = BUTTON_LOAD_TOP_Y}, .bottom = {.x = BUTTON_LOAD_BOTTOM_X, .y = BUTTON_LOAD_BOTTOM_Y}},
                                            .quit = {.top = {.x = BUTTON_QUIT_TOP_X, .y = BUTTON_QUIT_TOP_Y}, .bottom = {.x = BUTTON_QUIT_BOTTOM_X, .y = BUTTON_QUIT_BOTTOM_Y}}
                                           };

    state_t state = MENU_STATE;
    bool needQuit = false;

    char inputData[MAX_CHARS]   = {};
    char fileName[MAX_FILE_LEN] = {};
    int letterCount             = 0;
    int FileLetterCount         = 0;

    treeNode_t *root        = NULL;
    treeNode_t *currentNode = NULL;

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (state == MENU_STATE)
        {
            menuButtonsDraw();
            state = checkMenuButtonPress(menuButtons);
            if (state == ASKING_STATE) currentNode = root;
        }

        if (state == ASKING_STATE || state == GUESSING_STATE)
        {
            yesNoButtonsDraw();
        }

        stateHandling(&state, &needQuit, inputData, &letterCount, &root, fileName, &FileLetterCount, &currentNode);

        if (needQuit)
        {
            treeDump(root);
            destroyTree(root);

            return 0;
        }

        EndDrawing();
    }

    treeDump(root);
    destroyTree(root);

    CloseWindow();

    closeFile(&logFile);

    return 0;
}

static void windowSettings(void)
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Akinator");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    return;
}

void stateHandling(state_t *state, bool *needQuit, char inputData[MAX_CHARS], int *letterCount,
                   treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount, treeNode_t **currentNode)
{
    switch (*state)
    {
        case MENU_STATE:

            break;

        case ASKING_STATE:

            *state = searchingProcessing(root, currentNode);

            break;

        case GUESSING_STATE:

            *state = askingProcessing(currentNode);

            break;

        case INPUT_WHO_STATE:

            *state = inputWhoProcessing(inputData, letterCount);

            break;

        case INPUT_DIFF_STATE:

            *state = inputDiffProcessing(currentNode, inputData, letterCount, fileName, fileLetterCount);

            break;

        case SAVE_STATE:

            *state = saveDataToFile(root, fileName, fileLetterCount);

            break;

        case LOAD_STATE:

            *state = loadDataFromFile(root, fileName, fileLetterCount);

            break;

        case QUIT_STATE:

            *needQuit = true;

            break;

        default:

            break;
    }

    return;
}

state_t saveDataToFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount)
{
    DrawText("File name to open:\n", (SCREEN_WIDTH - MeasureText("File name to open:\n", 40)) / 2, SCREEN_HEIGHT / 4, 40, GRAY);

    if (inputBox(fileName, fileLetterCount) == 1)
    {
        treePrint(*root, fileName);

        cleanData(fileName, fileLetterCount);

        return MENU_STATE;
    }

    return SAVE_STATE;
}

state_t loadDataFromFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount)
{
    DrawText("File name to open:\n", (SCREEN_WIDTH - MeasureText("File name to open:\n", 40)) / 2, SCREEN_HEIGHT / 4, 40, GRAY);

    if (inputBox(fileName, fileLetterCount) == 1)
    {
        destroyTree(*root);
        *root = NULL;
        if ((*root = loadTree(fileName, *root)) == NULL)
        {
            DrawText("ERROR: can't load tree\n", (SCREEN_WIDTH - MeasureText("ERROR: can't load tree\n", 40)) / 2, 3 * SCREEN_HEIGHT / 4, 40, GRAY);
        }

        cleanData(fileName, fileLetterCount);

        return MENU_STATE;
    }

    return LOAD_STATE;
}

state_t searchingProcessing(treeNode_t **root, treeNode_t **currentNode)
{
    if (*root == NULL) return MENU_STATE;
    if (*currentNode == NULL) *currentNode = *root;

    if ((*currentNode)->left == NULL && (*currentNode)->right == NULL) return GUESSING_STATE;

    char buffer[256 + sizeof("The object you have in mind is ?")] = {};
    snprintf(buffer, sizeof(buffer), "The object you have in mind is %s?", (*currentNode)->data);

    DrawText(buffer, (SCREEN_WIDTH - MeasureText(buffer, 40)) / 2, SCREEN_HEIGHT / 8, 40, GRAY);

    if (pressDetection(yes)) *currentNode = (*currentNode)->left;
    if (pressDetection(no))  *currentNode = (*currentNode)->right;

    return ASKING_STATE;
}

state_t askingProcessing(treeNode_t **currentNode)
{
    char buffer[256 + sizeof("Did you search ?")] = {};
    snprintf(buffer, sizeof(buffer), "Did you search %s?", (*currentNode)->data);
    DrawText(buffer, (SCREEN_WIDTH - MeasureText(buffer, 40)) / 2, SCREEN_HEIGHT / 8, 40, GRAY);

    if (pressDetection(yes))
    {
        return MENU_STATE;
    }

    if (pressDetection(no))
    {
        return INPUT_WHO_STATE;
    }

    return GUESSING_STATE;
}

state_t inputWhoProcessing(char inputData[MAX_CHARS], int *letterCount)
{
    DrawText("What was it?", (SCREEN_WIDTH - MeasureText("What was it?", 40)) / 2, SCREEN_HEIGHT / 8, 40, GRAY);

    if (inputBox(inputData, letterCount) == 1)
    {
        return INPUT_DIFF_STATE;
    }

    return INPUT_WHO_STATE;
}

state_t inputDiffProcessing(treeNode_t **currentNode, char inputData[MAX_CHARS], int *letterCount, char fileName[MAX_FILE_LEN], int *fileLetterCount)
{
    char buffer[256 + sizeof("What is the difference between and ? (Yes for )")] = {};
    snprintf(buffer, sizeof(buffer), "What is the difference between %s and %s? (Yes for %s)", (*currentNode)->data, inputData, inputData);
    DrawText(buffer, (SCREEN_WIDTH - MeasureText(buffer, 40)) / 2, SCREEN_HEIGHT / 8, 40, GRAY);

    if (inputBox(fileName, fileLetterCount) == 1)
    {
        if (addToLeft(*currentNode, fileName) == NULL)
        {
            DrawText("ERROR: can't add element to left", (SCREEN_WIDTH - MeasureText("ERROR: can't add element to left", 40)) / 2, SCREEN_HEIGHT / 8, 40, GRAY);

            return MENU_STATE;
        }

        if (addToRight(*currentNode, (*currentNode)->data) == NULL)
        {
            DrawText("ERROR: can't add element to right", (SCREEN_WIDTH - MeasureText("ERROR: can't add element to right", 40)) / 2, SCREEN_HEIGHT / 8, 40, GRAY);

            return MENU_STATE;
        }

        free((*currentNode)->data);
        (*currentNode)->data = strdup(fileName);

        cleanData(fileName, fileLetterCount);
        cleanData(inputData, letterCount);

        return MENU_STATE;
    }

    return INPUT_DIFF_STATE;
}
