#pragma once 
#include <cmath>
#include <vector>
#include <raylib.h>

#define SIZE 64.0f

struct TextureObject
{
    Texture2D model;
    Rectangle sourceRec = (Rectangle){0.0f, 0.0f, SIZE, SIZE};
    Vector2 origin = (Vector2){SIZE / 2.0f, SIZE / 2.0f};
    Rectangle destRec;
};

template<typename A>
inline float norm(A Vec)
{
return sqrt((Vec.x*Vec.x)+(Vec.y*Vec.y));
}

template<typename A, typename B>
bool collCirclex2(A posCircle1, int radiusCircle1, B posCircle2,int radiusCircle2)
{
    A centerCenterVector = {posCircle1.x - posCircle2.x, posCircle1.y - posCircle2.y};
    float normCenterCenterVector = norm(centerCenterVector);
    if (normCenterCenterVector <= radiusCircle1 + radiusCircle2)
    {
        return true;
    }
    return false;
}

template<typename A>
A vector(A a, A b)
{
    A res;
    res.x=b.x-a.x;
    res.y=b.y-a.y;
    return res;
}

template<typename A>
int GetTile(A vec)
{

    return static_cast<int>(vec.x/64)+16*static_cast<int>(vec.y/64);
}



