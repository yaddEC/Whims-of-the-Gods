#include <raylib.h>
#include "game.hpp"
#include <vector>

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 768;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Whim Of The Gods");
    InitAudioDevice();
    Game game = {};

    // Main game loop
    while (!WindowShouldClose() && !game.quit)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (game.start) // if button start is pressed
        {
            if (!IsSoundPlaying(game.gameSounds.secondTheme) && game.hp>0)
            {
                PlaySound(game.gameSounds.secondTheme);
            }
            DrawRectangle(1024, 0, 256, 768, BROWN);
            DrawRectangle(1030, 530, 245, 170, ColorAlpha(DARKBROWN, 0.5));
            game.UpdateAndDraw();
        }
        else // print menu
        {
            if (!IsSoundPlaying(game.gameSounds.mainTheme))
            {
                PlaySound(game.gameSounds.mainTheme);
            }
            game.Menu();
        }

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
