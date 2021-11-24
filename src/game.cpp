#include "game.hpp"

void TileInit(Tiles (&map)[12][16])
{
   

    for (int j = 0; j < 12; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            map[j][i].Init(i, j);
        }
    }
}

void TileDraw(Tiles (&map)[12][16])
{
   

    for (int j = 0; j < 12; j++)
    {
        for (int i = 0; i < 16; i++)
        {
            map[j][i].Draw();
        }
    }
}
