#include <raylib.h>
#include "game.hpp"
#include <vector>

int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 768;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "BLINDER");
    InitAudioDevice();
    Game game = {};
    
    // Main game loop
    while (!WindowShouldClose() && !game.quit)
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if(game.start)
        {
            DrawRectangle(1024,0,256,768,BROWN);
            game.UpdateAndDraw();
        }
        else
        {
            game.Menu();
        }
        
        DrawFPS(10, 10);

        EndDrawing();
    }

   
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
