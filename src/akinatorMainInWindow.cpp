#include "../include/tree.h"
#include "../include/akinator.h"
#include "../include/graphicAkinator.h"

static void stateHandling(state_t *state, bool *needQuit, char inputData[MAX_CHARS], int *letterCount, treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount);
static state_t loadDataFromFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount);
static state_t saveDataToFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount);

int main()
{
    SetTraceLogLevel(LOG_NONE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Akinator");
    SetTargetFPS(60);
    SetExitKey(KEY_NULL);

    menuButtonsCoordinates_t menuButtons = {
                                            .game = {.top = {.x = BUTTON_GAME_TOP_X, .y = BUTTON_GAME_TOP_Y}, .bottom = {.x = BUTTON_GAME_BOTTOM_X, .y = BUTTON_GAME_BOTTOM_Y}},
                                            .save = {.top = {.x = BUTTON_SAVE_TOP_X, .y = BUTTON_SAVE_TOP_Y}, .bottom = {.x = BUTTON_SAVE_BOTTOM_X, .y = BUTTON_SAVE_BOTTOM_Y}},
                                            .load = {.top = {.x = BUTTON_LOAD_TOP_X, .y = BUTTON_LOAD_TOP_Y}, .bottom = {.x = BUTTON_LOAD_BOTTOM_X, .y = BUTTON_LOAD_BOTTOM_Y}},
                                            .quit = {.top = {.x = BUTTON_QUIT_TOP_X, .y = BUTTON_QUIT_TOP_Y}, .bottom = {.x = BUTTON_QUIT_BOTTOM_X, .y = BUTTON_QUIT_BOTTOM_Y}}
                                           };

    state_t state = MENU_STATE;
    bool needQuit = false;
    char inputData[MAX_CHARS] = {};
    int letterCount = 0;
    treeNode_t *root = NULL;
    char fileName[MAX_FILE_LEN] = {};
    int FileLetterCount = 0;

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        if (state == MENU_STATE)
        {
            menuButtonsDraw();
            state = checkMenuButtonPress(menuButtons);
        }

        stateHandling(&state, &needQuit, inputData, &letterCount, &root, fileName, &FileLetterCount);

        if (needQuit)
            return 0;


        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void stateHandling(state_t *state, bool *needQuit, char inputData[MAX_CHARS], int *letterCount, treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount)
{
    switch (*state)
    {
        case MENU_STATE:
            break;

        case GAME_STATE:

            yesNoButtonsDraw();

            inputBox(inputData, letterCount);


            break;

        case SAVE_STATE:

            *state = saveDataToFile(root, fileName, fileLetterCount);

            break;

        case LOAD_STATE:

            *state = loadDataFromFile(root, fileName, fileLetterCount);

            break;

        case QUIT_STATE:

            destroyTree(*root);

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

        for (int i = 0; i < *fileLetterCount; i++)
        {
            fileName[i] = '\0';
        }

        *fileLetterCount = 0;

        return MENU_STATE;
    }

    return SAVE_STATE;
}

state_t loadDataFromFile(treeNode_t **root, char fileName[MAX_FILE_LEN], int *fileLetterCount)
{
    DrawText("File name to open:\n", (SCREEN_WIDTH - MeasureText("File name to open:\n", 40)) / 2, SCREEN_HEIGHT / 4, 40, GRAY);

    if (inputBox(fileName, fileLetterCount) == 1)
    {
        if ((*root = loadTree(fileName, *root)) == NULL)
        {
            DrawText("ERROR: can't load tree\n", (SCREEN_WIDTH - MeasureText("ERROR: can't load tree\n", 40)) / 2, 3 * SCREEN_HEIGHT / 4, 40, GRAY);
        }

        for (int i = 0; i < *fileLetterCount; i++)
        {
            fileName[i] = '\0';
        }

        *fileLetterCount = 0;

        return MENU_STATE;
    }

    return LOAD_STATE;
}

