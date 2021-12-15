#include <vector>
#include <raylib.h>
#include "resources.hpp"
#include "game.hpp"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 768;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "Whim Of The Gods");
    InitAudioDevice();

    Resources resources;
    gRes = &resources;

    Game game = {};

    // Main game loop
    while (!WindowShouldClose() && !game.quit)
    {
        BeginDrawing();
        ClearBackground(GetColor(0x8db3c6ff));

        if (game.music)  // activate/desactivate music
        {
            SetMusicVolume(gRes->sounds.mainTheme, 0.5f);
            SetMusicVolume(gRes->sounds.secondTheme, 0.5f);
            SetMusicVolume(gRes->sounds.gameOver, 0.5f);
            SetMusicVolume(gRes->sounds.creditsTheme, 0.5f);
        }
        else
        {
            SetMusicVolume(gRes->sounds.mainTheme, 0);
            SetMusicVolume(gRes->sounds.secondTheme, 0);
            SetMusicVolume(gRes->sounds.gameOver, 0);
            SetMusicVolume(gRes->sounds.creditsTheme, 0);
        }

        if (game.start) // if button start is pressed
        {
            if (game.hp > 0)
            {
                game.currentMusic = &(gRes->sounds.secondTheme);
                PlayMusicStream(gRes->sounds.secondTheme);
            }
            DrawRectangle(1024, 0, 256, 768, BROWN);
            DrawRectangle(1030, 530, 245, 170, ColorAlpha(DARKBROWN, 0.5));
            game.UpdateAndDraw();
        }
        else if(game.credit)
        {
            if (!IsMusicStreamPlaying(gRes->sounds.creditsTheme))
            {
                game.currentMusic = &(gRes->sounds.creditsTheme);
                PlayMusicStream(gRes->sounds.creditsTheme);
            }
            game.Credit();
        }
        else // print menu
        {
            /* if (!IsMusicStreamPlaying(gRes->sounds.mainTheme))
            { */
                game.currentMusic = &(gRes->sounds.mainTheme);
                PlayMusicStream(gRes->sounds.mainTheme);
            /* } */
            game.Menu();
        }

        if (game.currentMusic)
            UpdateMusicStream(*(game.currentMusic));

        DrawFPS(10, 10);

        
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
