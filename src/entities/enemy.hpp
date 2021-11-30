#pragma once
#include "entity.hpp"

class Enemy : public Entity
{
public:
    Enemy();
    int radius = 5.0f;
    int damage;
    int hp = 60;
    int maxHp = 60;
    float speed = 1;
    int slowingTimer = 0;
    float slowingCoef = 1;
    Vector2 direction;
    int reward = 5;
    Color color; // TEMPORAIRE

    void UpdateAndDraw() override
    {
        FrameTimer(slowingTimer);

        if (pos.x - radius < 0 || pos.x + radius > 1024) // TEST ENEMY
            direction.x *= -1;
        if (pos.y - radius < 0 || pos.y + radius > 768)
            direction.y *= -1;
        if(slowingTimer==0 && slowingCoef != 1)
        {
            slowingCoef = 1;
        }
        pos.x += direction.x*slowingCoef*speed;
        pos.y += direction.y*slowingCoef*speed;

        DrawCircle(pos.x, pos.y, radius, color);
        DrawRectangle(pos.x-20, pos.y+20, 40,10, ColorAlpha(BLACK, 0.5));
        DrawRectangle(pos.x-20, pos.y+20, hp*40/maxHp,10, GREEN);
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
        color = RED;
        damage = 2;
        speed = 0.8;
        hp = 60;
        maxHp = 60;
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
        color = VIOLET;
        damage = 1;
        speed = 1;
        hp = 30;
        maxHp = 30;
    }

};

class Berserker : public Enemy
{
public:
    Berserker()
    {
        color = MAROON;
        radius = 7.0f;
        damage = 5;
        speed = 0.6;
        hp = 120;
        maxHp = 120;
    }
};
