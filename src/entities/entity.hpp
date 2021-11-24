#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include "../game.hpp"


class Entity
{

    public:
    
    bool active;
    int hp;
    Vector2 pos;
    Vector2 posTile;

    virtual void UpdateAndDraw()
    {

    }
};




