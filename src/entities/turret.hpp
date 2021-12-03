#pragma once
#include "entity.hpp"
#include "enemy.hpp"

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

class Turret : public Entity
{
public:
    int id;
    float range;
    int target;
    int damage;
    int price;
    float attackSpeed;
    Vector2 explosionPos;
    float slowEffect;
    int timer;
    Color colorZone;

    void UpdateAndDraw(std::vector<Enemy *> &enemy, Texture2D tilesheet, Vector2 sourcePos);

    Turret();

    virtual ~Turret()
    {
    }
};

class ClassicTurret : public Turret
{

public:
    ClassicTurret();
};

class SlowingTurret : public Turret
{
public:
    SlowingTurret();
};

class ExplosiveTurret : public Turret
{
public:
    ExplosiveTurret();
};