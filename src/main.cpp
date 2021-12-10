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
        ClearBackground(BEIGE);

        if (game.music)  // activate/desactivate music
        {
            SetMusicVolume(game.gameSounds.mainTheme, 0.5f);
            SetMusicVolume(game.gameSounds.secondTheme, 0.5f);
        }
        else
        {
            SetMusicVolume(game.gameSounds.mainTheme, 0);
            SetMusicVolume(game.gameSounds.secondTheme, 0);
        }

        if (game.start) // if button start is pressed
        {
            if (!IsMusicStreamPlaying(game.gameSounds.secondTheme) && game.hp > 0)
            {
                PlayMusicStream(game.gameSounds.secondTheme);
            }
            DrawRectangle(1024, 0, 256, 768, BROWN);
            DrawRectangle(1030, 530, 245, 170, ColorAlpha(DARKBROWN, 0.5));
            game.UpdateAndDraw();
        }
        else // print menu
        {
            if (!IsMusicStreamPlaying(game.gameSounds.mainTheme))
            {
                PlayMusicStream(game.gameSounds.mainTheme);
            }
            game.Menu();
        }

        UpdateMusicStream(game.gameSounds.mainTheme);
        UpdateMusicStream(game.gameSounds.secondTheme);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
