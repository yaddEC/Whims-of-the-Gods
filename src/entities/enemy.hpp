#pragma once
#include "entity.hpp"
#include "tile.hpp"


void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b, Tile *c, Tile *d, int PrevTile,float &rotation);

class Enemy : public Entity
{
public:
    Enemy();
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

    virtual void UpdateAndDraw(Tilemap &map, int round,std::vector<Enemy *> &enemies);
    void GetEnemyDirection(Tilemap &map, int round);
    void ActivateHealingZone(std::vector<Enemy *> &enemies);

    virtual void UpdateSpecific(std::vector<Enemy *> &enemies) {}
    
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
    void UpdateSpecific(std::vector<Enemy *> &enemies) override;
};

class Berserker : public Enemy
{
public:
    Berserker();
};