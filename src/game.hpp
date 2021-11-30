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
    int mTilePos;
    int mWidthTile;

public:
    Vector2 mPos;
    char value;
    bool active;
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

public:
    Tile *tile;
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
    bool quit = false;
    bool start = false;
    int money = 100;
    int timer;
    bool showTurretRange = false;
    TextureObject classicTurret;
    TextureObject slowingTurret;
    TextureObject explosiveTurret;
    TextureObject jackhammer;
    Tilemap map;
    std::vector<Turret *> turret;
    std::vector<Enemy *> enemy;
    Game();
    void Menu();
    void UpdateAndDraw();
    void UpdateAndDrawUI();
    void UpdateAndDrawTurret();
    void UpdateAndDrawEnemy();
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, Color color);

