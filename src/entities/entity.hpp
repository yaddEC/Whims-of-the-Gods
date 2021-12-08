#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include <mathematics.hpp>
#include "../sounds.hpp"

class Tile
{
private:
    int mWidthTile;

public:
    int mTilePos;
    Vector2 mPos;
    char value;
    bool active;
    bool road;
    Tile();
    ~Tile();

    void Init(int i, int mapWidth, char val);

    void Draw(Texture2D tilesheet, Tile frame);
};

class Tilemap
{
private:
    const char *plan;
    int height;
   
    int total;

public:
    int width;
    Tile *tile;
    Texture2D tilesheet;
    Tile texture[368];
    Tile Spawn;
    Tile Despawn;
    Tilemap();
    void Init();
    void Draw(int round);
    ~Tilemap();
};

class Entity
{
    public:
    Entity();
    float rotation;
    Rectangle sourceTexture;
    int damage;
    int timer;
    bool active;
    int hp;
    Vector2 pos;
    int posTile;

    virtual void UpdateAndDraw()
    {
    }
};


void FrameTimer(int &timer);
void DefSpawn(Vector2 pos);




