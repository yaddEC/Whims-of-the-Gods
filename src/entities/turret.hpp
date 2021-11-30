#pragma once
#include "entity.hpp"
#include "enemy.hpp"

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);


class Turret : public Entity
{
public:
    int id;
    float range = 100.0f;
    float rotation = 0.0f;
    int target = -1;
    int damage;
    int price;
    float attackSpeed;
    Vector2 explosionPos;
    float slowEffect = 1;
    int timer=0;

    void UpdateAndDraw(std::vector<Enemy *> &enemy, Texture2D tilesheet, Vector2 sourcePos);
    
    virtual ~Turret()
    {
    }
};

class ClassicTurret : public Turret
{

public:
    ClassicTurret()
    {
        damage = 10;
        price = 100;
        attackSpeed = 2;
    }
};

class SlowingTurret : public Turret
{
public:
    SlowingTurret()
    {

        damage = 5;
        price = 150;
        attackSpeed = 6;
        slowEffect = 0.5f;
    }
};

class ExplosiveTurret : public Turret
{
public:
    ExplosiveTurret()
    {

        damage = 20;
        price = 200;
        attackSpeed = 1;
    }
};
