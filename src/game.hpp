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
    Tile();
    ~Tile();

    void Init(int i, int mapWidth, char val);

    void Draw(Texture2D tilesheet, Tile frame);
};

class Tilemap
{
private:
    const char *plan;
    int mHeight;
    int mWidth;
    int total;
    Tile *tile;
public:
    Texture2D tilesheet;
    Tile texture[368];
    Tilemap();
    void Init();
    void Draw();
    ~Tilemap(); 
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
    void UpdateAndDrawUI();
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, Color color);