#ifndef GRAPHIC_AKINATOR_H
#define GRAPHIC_AKINATOR_H

#include <stdio.h>
#include <string.h>
#include <raylib.h>

const int SCREEN_WIDTH  = 1000;
const int SCREEN_HEIGHT = 1000;
const int MAX_CHARS     = 256;

enum menuButtonsLocation
{
    BUTTON_GAME_TOP_X    = 300,
    BUTTON_GAME_TOP_Y    = SCREEN_HEIGHT / 2,
    BUTTON_GAME_BOTTOM_X = 700,
    BUTTON_GAME_BOTTOM_Y = SCREEN_HEIGHT / 2 + 80,
    BUTTON_SAVE_TOP_X    = 300,
    BUTTON_SAVE_TOP_Y    = SCREEN_HEIGHT / 2 + 100,
    BUTTON_SAVE_BOTTOM_X = 700,
    BUTTON_SAVE_BOTTOM_Y = SCREEN_HEIGHT / 2 + 180,
    BUTTON_LOAD_TOP_X    = 300,
    BUTTON_LOAD_TOP_Y    = SCREEN_HEIGHT / 2 + 200,
    BUTTON_LOAD_BOTTOM_X = 700,
    BUTTON_LOAD_BOTTOM_Y = SCREEN_HEIGHT / 2 + 280,
    BUTTON_QUIT_TOP_X    = 300,
    BUTTON_QUIT_TOP_Y    = SCREEN_HEIGHT / 2 + 300,
    BUTTON_QUIT_BOTTOM_X = 700,
    BUTTON_QUIT_BOTTOM_Y = SCREEN_HEIGHT / 2 + 380
};

enum state_t
{
    MENU_STATE         = 0,
    ASKING_STATE       = 1,
    GUESSING_STATE     = 2,
    INPUT_WHO_STATE    = 3,
    INPUT_DIFF_STATE   = 4,
    SAVE_STATE         = 5,
    LOAD_STATE         = 6,
    QUIT_STATE         = 7
};

struct button_t
{
    Vector2 top;
    Vector2 bottom;
};

struct menuButtonsCoordinates_t
{
    button_t game;
    button_t save;
    button_t load;
    button_t quit;
};

void yesNoButtonsDraw        (void);
void menuButtonsDraw         (void);
bool pressDetection          (button_t button);
state_t checkMenuButtonPress (menuButtonsCoordinates_t menuButtons);
int inputBox                 (char inputData[MAX_CHARS], int *letterCount);
void cleanData               (char *string, int *number);

#endif
