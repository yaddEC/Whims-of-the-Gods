#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>
#include <mathematics.hpp>



class Entity
{

    public:
    
    TextureObject texture;
    bool active = false;
    int hp;
    Vector2 pos;
    Vector2 posTile;

    virtual void UpdateAndDraw()
    {

    }
};




