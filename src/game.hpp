#pragma once
#include <mathematics.hpp>
#include <iostream>
#include <raylib.h>
#include "entities/turret.hpp"
#include "entities/enemy.hpp"
#include "entities/tower.hpp"



class Tile
{
private:
    Vector2 mPos;
    int mTilePos;
    int mWidthTile;

public:
    char value;
    Tile()
    {
        mWidthTile = SIZE;
    }
    ~Tile()
    {
    }

    void Init(int i, int mapWidth, char val)
    {

        mTilePos = i;
        value = val;
        mPos.x = (i % mapWidth) * mWidthTile;
        mPos.y = static_cast<int>(i / mapWidth) * mWidthTile;
    }

    void Draw(Texture2D tilesheet, Tile frame)
    {

        Rectangle source = {frame.mPos.x, frame.mPos.y, SIZE, SIZE};
        Rectangle dest = {mPos.x, mPos.y, SIZE, SIZE};
        Vector2 origin = {0, 0};
        DrawTexturePro(tilesheet, source, dest, origin, 0, WHITE);

        if (GetTile(GetMousePosition()) == mTilePos && GetMousePosition().x < 1024)
        {
            DrawRectangleLines(mPos.x, mPos.y, SIZE, SIZE, ColorAlpha(WHITE, 0.5));
        }
    }
};

class Tilemap
{

private:
    const char *plan;
    int mHeight;
    int mWidth;
    int total;
    Tile *tile;
    Tile texture[368];
    Texture2D tilesheet;

public:
    Tilemap()
    {
        mHeight = 12;
        mWidth = 16;
        total = mHeight * mWidth;
        tile = new Tile[total];
        tilesheet = LoadTexture("assets/towerDefense_tilesheet.png");

        plan =
            {
                "-------T|OOOOOOO"
                "OOOOOOOl|OOOOOOO"
                "OOOOOOOl|OOOOOOO"
                "OOOOOOOl|OOOOOOO"
                "OOOOOOOl|OOOOOOO"
                "OO[____JL____]OO"
                "OOlb--------d|OO"
                "OOl|OOOOOOOOl|OO"
                "OOlL________J|OO"
                "OO{---------d|OO"
                "OOOOOOOOOOOOl|OO"
                "OOOOOOOOOOOOlL__"};
    }

    void Init()
    {
        for (int i = 0; i < total; i++)
        {
            tile[i].Init(i, mWidth, plan[i]);
        }

        for (int i = 0; i < 368; i++)
        {
            texture[i].Init(i, 23, 'a');
        }
    }

    void Draw()
    {
        for (int i = 0; i < total; i++)
        {
            switch (tile[i].value)
            {
            case 'I':
                tile[i].Draw(tilesheet, texture[50]);
                break;
            case '-':
                tile[i].Draw(tilesheet, texture[1]);
                break;
            case 'T':
                tile[i].Draw(tilesheet, texture[2]);
                break;
            case 'l':
                tile[i].Draw(tilesheet, texture[25]);
                break;
            case '|':
                tile[i].Draw(tilesheet, texture[23]);
                break;
            case 'L':
                tile[i].Draw(tilesheet, texture[46]);
                break;
            case 'J':
                tile[i].Draw(tilesheet, texture[48]);
                break;
            case '_':
                tile[i].Draw(tilesheet, texture[47]);
                break;
            case 'O':
                tile[i].Draw(tilesheet, texture[24]);
                break;
            case '[':
                tile[i].Draw(tilesheet, texture[3]);
                break;
            case ']':
                tile[i].Draw(tilesheet, texture[4]);
                break;
            case '{':
                tile[i].Draw(tilesheet, texture[26]);
                break;
            case '}':
                tile[i].Draw(tilesheet, texture[27]);
                break;

                case 'd':
                tile[i].Draw(tilesheet, texture[2]);
                break;

                case 'b':
                tile[i].Draw(tilesheet, texture[0]);
                break;
            }
        }
    }

    ~Tilemap()
    {
    }
};

class Game
{
public:
    int money;
    int timer;
    bool showTurretRange = false;
    TextureObject classicTurret;
    TextureObject slowingTurret;
    TextureObject explosiveTurret;
    Tilemap map;
    std::vector<Enemy> enemies;

    Game();
    void UpdateAndDraw();
    void Delete();
};


bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, Color color);