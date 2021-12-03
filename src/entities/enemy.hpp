#pragma once
#include "entity.hpp"
bool checkTile(int tile, std::vector<int *> PrevTiles);

void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b = nullptr, int PrevTile = 999, Tile *c = nullptr, std::vector<int *> PrevTiles = {}, Tile *d = nullptr);

class Enemy : public Entity
{
public:
    Enemy();

    int radius;
    int damage;
    std::vector<int *> PrevTiles;
    int hp;
    int maxHp;
    int prevTile;
    int timer;
    float speed;
    int slowingTimer;
    float slowingCoef;
    Vector2 direction;
    int reward;
    Color color; // TEMPORAIRE

    void UpdateAndDraw(Tilemap &map, int round,std::vector<Enemy *> &enemy);
    
    virtual ~Enemy();

};

class Warrior : public Enemy
{
public:
    Warrior();
};

class Healer : public Enemy
{

public:
    Healer();
};

class Berserker : public Enemy
{
public:
    Berserker();
};
