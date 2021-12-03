#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include <mathematics.hpp>

class Tile
{
private:
    int mWidthTile;

public:
    int mTilePos;
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
    Tile Spawn;
    Tile Despawn;
    Tilemap();
    void Init();
    void Draw();
    ~Tilemap();
};

class Entity
{
    public:
    Entity();
    float rotation;
    Rectangle sourceTexture;
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




