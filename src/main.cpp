#include <vector>
#include <raylib.h>
#include "resources.hpp"
#include "game.hpp"

int main(void)
{
    const int screenWidth = 1280;
    const int screenHeight = 768;
    SetTargetFPS(60);
    
    InitWindow(screenWidth, screenHeight, "Whim Of The Gods");
    InitAudioDevice();

    Resources resources;
    gRes = &resources;

    Game game = {};

    while (!WindowShouldClose() && !game.quit) // Main game loop
    {
        BeginDrawing();
        ClearBackground(GetColor(0x8db3c6ff));

        if (game.music) // activate/desactivate music
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

        if (game.start) // if start button is pressed
        {
            if (game.hp > 0)
            {
                game.currentMusic = &(gRes->sounds.secondTheme);
                PlayMusicStream(gRes->sounds.secondTheme); //  Play game music
            }

            game.UpdateAndDraw();
        }

        else if (game.credit) // if credit button is pressed
        {

            game.currentMusic = &(gRes->sounds.creditsTheme);
            PlayMusicStream(gRes->sounds.creditsTheme); //  Play credits music

            game.Credit();
        }

        else // print menu
        {

            game.currentMusic = &(gRes->sounds.mainTheme);
            PlayMusicStream(gRes->sounds.mainTheme); //  Play menu music

            game.Menu();
        }

        if (game.currentMusic) // update current music
            UpdateMusicStream(*(game.currentMusic));

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
