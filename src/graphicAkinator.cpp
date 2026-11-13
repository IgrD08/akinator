#include "../include/graphicAkinator.h"

static void menuButtonsDraw(void);
static void yesNoButtonsDraw(void);

void drawWindow(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Akinator");

    SetTargetFPS(60);

    while(!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        yesNoButtonsDraw();

        EndDrawing();
    }

    CloseWindow();

    return;
}

void menuButtonsDraw(void)
{
    DrawRectangle(300, SCREEN_HEIGHT / 2      , 400, 80, GRAY);
    DrawRectangle(300, SCREEN_HEIGHT / 2 + 100, 400, 80, GRAY);
    DrawRectangle(300, SCREEN_HEIGHT / 2 + 200, 400, 80, GRAY);
    DrawRectangle(300, SCREEN_HEIGHT / 2 + 300, 400, 80, GRAY);

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

