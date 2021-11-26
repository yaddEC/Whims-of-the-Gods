#pragma once
#include "entity.hpp"

class Enemy : public Entity
{
public:
    Enemy();
    int radius = 5.0f;
    int damage;
    int hp = 60;
    float speed;
    Vector2 direction;

    void UpdateAndDraw() override
    {

        if (pos.x - radius < 0 || pos.x + radius > 1024) // TEST ENEMY
            direction.x *= -1;
        if (pos.y - radius < 0 || pos.y + radius > 768)
            direction.y *= -1;
        pos.x += direction.x;
        pos.y += direction.y;
        DrawCircle(pos.x, pos.y, radius, RED);
        DrawRectangle(pos.x-20, pos.y+20, 40,10, ColorAlpha(BLACK, 0.5));
        DrawRectangle(pos.x-20, pos.y+20, hp*40/60,10, GREEN);
        DrawRectangleLines(pos.x-21, pos.y+20, 42,10, BLACK);
       
    }
    virtual ~Enemy()
    {
    }
};

class Warrior : public Enemy
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
