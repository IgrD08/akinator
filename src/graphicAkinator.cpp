#include "../include/graphicAkinator.h"

void menuButtonsDraw(void)
{
    DrawRectangle(BUTTON_GAME_TOP_X, BUTTON_GAME_TOP_Y, BUTTON_GAME_BOTTOM_X - BUTTON_GAME_TOP_X, BUTTON_GAME_BOTTOM_Y - BUTTON_GAME_TOP_Y, GRAY);
    DrawRectangle(BUTTON_SAVE_TOP_X, BUTTON_SAVE_TOP_Y, BUTTON_SAVE_BOTTOM_X - BUTTON_SAVE_TOP_X, BUTTON_SAVE_BOTTOM_Y - BUTTON_SAVE_TOP_Y, GRAY);
    DrawRectangle(BUTTON_LOAD_TOP_X, BUTTON_LOAD_TOP_Y, BUTTON_LOAD_BOTTOM_X - BUTTON_LOAD_TOP_X, BUTTON_LOAD_BOTTOM_Y - BUTTON_LOAD_TOP_Y, GRAY);
    DrawRectangle(BUTTON_QUIT_TOP_X, BUTTON_QUIT_TOP_Y, BUTTON_QUIT_BOTTOM_X - BUTTON_QUIT_TOP_X, BUTTON_QUIT_BOTTOM_Y - BUTTON_QUIT_TOP_Y, GRAY);

    DrawText("Start game"   , 320, SCREEN_HEIGHT / 2 + 20 , 40, RAYWHITE);
    DrawText("Save database", 320, SCREEN_HEIGHT / 2 + 120, 40, RAYWHITE);
    DrawText("Open database", 320, SCREEN_HEIGHT / 2 + 220, 40, RAYWHITE);
    DrawText("Press to quit", 320, SCREEN_HEIGHT / 2 + 320, 40, RAYWHITE);

    return;
}

void yesNoButtonsDraw(void)
{
    DrawRectangle(50, SCREEN_HEIGHT / 2, 400, 80, GRAY);
    DrawRectangle(550, SCREEN_HEIGHT / 2, 400, 80, GRAY);

    DrawText("YES", 70 , SCREEN_HEIGHT / 2, 40, RAYWHITE);
    DrawText("NO" , 570, SCREEN_HEIGHT / 2, 40, RAYWHITE);

    return;
}

bool pressDetection(button_t button)
{
    Vector2 pos = GetMousePosition();

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && pos.x >= button.top.x && pos.x <= button.bottom.x && pos.y >= button.top.y && pos.y <= button.bottom.y)
        return 1;

    return 0;
}

state_t checkMenuButtonPress(menuButtonsCoordinates_t menuButtons)
{
    if (pressDetection(menuButtons.game)) return GAME_STATE;
    if (pressDetection(menuButtons.save)) return SAVE_STATE;
    if (pressDetection(menuButtons.load)) return LOAD_STATE;
    if (pressDetection(menuButtons.quit)) return QUIT_STATE;

    return MENU_STATE;
}

int inputBox(char inputData[MAX_CHARS], int *letterCount) //TODO - delete inputData[MAX_CHARS]
{
    Rectangle textBox = {.x = SCREEN_WIDTH / 2 - 400, .y = SCREEN_HEIGHT / 2 - 150, .width = 800, .height = 50};

    if (CheckCollisionPointRec(GetMousePosition() , textBox))
    {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);

        int key = GetCharPressed();

        while (key > 0)
        {
            if (key >= 32 && key <= 125 && *letterCount < MAX_CHARS)
            {
                inputData[*letterCount]     = (char)key;
                inputData[*letterCount + 1] = '\0';
                (*letterCount)++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressedRepeat(KEY_BACKSPACE) || IsKeyPressed(KEY_BACKSPACE))
        {
            (*letterCount)--;
            if (*letterCount < 0) *letterCount = 0;
            inputData[*letterCount] = '\0';
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            return 1;
        }
    }
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    DrawRectangleRec(textBox, GRAY);

    DrawText(inputData, (int)textBox.x + 5, (int)textBox.y + 5, 40, RAYWHITE);

    return 0;
}
