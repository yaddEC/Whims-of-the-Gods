#pragma once 
#include "entity.hpp"


class Enemy : public Entity
{
public:
    Enemy();
    int radius = 5.0f;
    int damage;
    float speed;
    Vector2 direction;

     void UpdateAndDraw() override
    {

    }
    virtual ~Enemy()
    {
    }
};

class Warrior: public Enemy
{
public:
    Warrior()
    {
        damage = 2;
        speed = 4;
        hp = 10;
    }
     void UpdateAndDraw() override
    {

    }
};


class Healer : public Enemy
{
private:
    int heal;
    int timer;
public:
    Healer()
    {
        damage = 1;
        
    }

     void UpdateAndDraw() override
    {

    }

};

class Berserker : public Enemy
{
public:
    

     void UpdateAndDraw() override
    {

    }
};





