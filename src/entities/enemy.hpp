#pragma once
#include "entity.hpp"
#include "tile.hpp"


void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b, Tile *c, Tile *d, int PrevTile,float &rotation);

enum EnemyType
{
    WARRIOR = 1,
    HEALER,
    BERSERKER
};

class Enemy : public Entity
{
public:
    Enemy();
    EnemyType id;
    int radius;
    int hp;
    int maxHp;
    int prevTile;
    int healTimer;
    float speed;
    int slowingTimer;
    float slowingCoef;
    Vector2 direction;
    int looking;
    int reward;
    Color color;

    void UpdateAndDraw(Tilemap &map, int round,std::vector<Enemy *> &enemies);
    void GetEnemyDirection(Tilemap &map, int round);
    void ActivateHealingZone(std::vector<Enemy *> &enemies);
    
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