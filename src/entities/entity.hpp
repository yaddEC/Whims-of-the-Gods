#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include <mathematics.hpp>


class Entity
{
    public:
    Entity();
    float rotation;
    Rectangle sourceTexture;
    int damage;
    int timer;
    bool active;
    int hp;
    Vector2 pos;
    int posTile;

    virtual void UpdateAndDraw()
    {
    }
};


void FrameTimer(int &timer);
void DefSpawn(Vector2 pos);




