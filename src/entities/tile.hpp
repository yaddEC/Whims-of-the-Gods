#pragma once
#include "entity.hpp"


class Tile
{
private:
    int mWidthTile;

public:
    int tilePos; // draw tile id
    Vector2 pos; // pos on the map
    char value;
    bool active;
    bool road;
    int environment;
    Tile();
    ~Tile();

    Tile(int i, int mapWidth, char val);

    void Draw(Vector2 frame);

    static int GetTile(Vector2 vec)
    {
        return static_cast<int>(vec.x / 64) + 16 * static_cast<int>(vec.y / 64);
    }
};

class Tilemap
{
private:
    const char *plan;
    int height;
    int total;

public:
    int width;
    std::vector<Tile> tile; 
    Vector2 texture[368];
    Tile Spawn;
    Tile Despawn;
    Tilemap();
    void Init();
    void Draw(int round);
    ~Tilemap();

};
