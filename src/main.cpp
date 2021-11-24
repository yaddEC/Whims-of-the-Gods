#include <raylib.h>
#include "game.hpp"

int main(void)
{
    const int screenWidth  = 1280;
    const int screenHeight = 768;

    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    InitAudioDevice();
    Tiles map[12][16];
    TileInit(map);
    // Main game loop
    while (!WindowShouldClose())
    {
        BeginDrawing();
        TileDraw(map);
        

        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        DrawRectangle(1024,0,256,768,GREEN);
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}
