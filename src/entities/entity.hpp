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
    int mTilePos; // draw tile id
    Vector2 mPos; // pos on the map
    char value;
    bool active;
    bool road;
    Tile();
    ~Tile();

    Tile(int i, int mapWidth, char val);

    void Draw(Texture2D tilesheet, Vector2 frame);
};

class Tilemap
{
private:
    const char *plan;
    int height;
    
    int total;

public:
    int width;
    std::vector<Tile> tile; // use std::vector<Tile>   (texture.resize(...))
    Texture2D tilesheet;
    Vector2 texture[368];
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




