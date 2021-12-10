#pragma once
#include "entity.hpp"

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
