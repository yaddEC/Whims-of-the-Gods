#pragma once
#include "entity.hpp"


void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b, Tile *c, Tile *d, int PrevTile,float &rotation);

class Enemy : public Entity
{
public:
    Enemy();

    int radius;
    int damage;
    int hp;
    int maxHp;
    int prevTile;
    int timer;
    int healTimer;
    float speed;
    int slowingTimer;
    float slowingCoef;
    Vector2 direction;
    int looking;
    int reward;
    Color color;

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
