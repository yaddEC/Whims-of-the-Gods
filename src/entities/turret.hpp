#pragma once 
#include "entity.hpp"

class Turret : public Entity
{
public:
    int target = -1;
    float rotation = 0.0f;
    int damage;
    float range = 100.0f;
    int price;
    float attackSpeed;
    int timer;


    void UpdateAndDraw() override
    {

    }
    virtual ~Turret()
    {
    }
};


class ClassicTurret : public Turret
{
public:

 void UpdateAndDraw() override
    {

    }
    
};

class SlowingTurret : public Turret
{
public:
    float slowEffect; // slow effect coef (between 1 and 0)

     void UpdateAndDraw() override
    {

    }
};

class ExplosiveTurret : public Turret
{
public:
    float damageRange; // radius of the damage zone

     void UpdateAndDraw() override
    {

    }
};
