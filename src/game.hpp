#pragma once
#include <mathematics.hpp>
#include <iostream>
#include <raylib.h>



const char Plan[12][17] = {
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIOOOOOOOOIO",
    "OOOOOIIIIIIIIIIO",
    "OOOOOOOOOIOOOOIO",
    "OOOOOOOOOIOOOOIO",
    "OOOOOOOOOIOOOOIO"
};

class Tiles
{
private:
    Vector2 mPos;
    Vector2 mTilePos;
    float mWidth;
    char value;

public:
    Tiles()
    {
        mWidth = 64;
    }
    ~Tiles()
    {
    }

    void Init(int i, int j)
    {
        mTilePos.x = i;
        mTilePos.y = j;
        mPos.x = mWidth*mTilePos.x;
        mPos.y = mWidth*mTilePos.y;


    }

    void Draw()
    {
       if(Plan[static_cast<int>( mTilePos.y)][static_cast<int>( mTilePos.x)]=='O')
       {
           DrawRectangle(mPos.x,mPos.y,mWidth,mWidth,BLUE);
       }
       
       if(Plan[static_cast<int>( mTilePos.y)][static_cast<int>( mTilePos.x)]=='I')
       {
           DrawRectangle(mPos.x,mPos.y,mWidth,mWidth,RED);
       }


    }


   
};

void TileInit(Tiles (&map)[12][16]);
void TileDraw(Tiles (&map)[12][16]);