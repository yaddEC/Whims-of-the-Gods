#pragma once

#include <raylib.h>
#include <vector>
#include <cmath>

bool pointSelected =false;
Vector2 mousePos;

struct TextureObject
{
    float width;
    float height;
    Texture2D model;
    Rectangle sourceRec;
    Vector2 origin;
    Rectangle destRec;
};

class Game
{
public:
    int money;
    TextureObject turret;
};

class Entity
{
public:
    bool active;
    Vector2 pos;
    int damage;
};

class Turret : public Entity
{
public:
    float rotation = 0.0f;
    int damage;
    float range = 100.0f;
    int price;
    float attackSpeed;
};

class ClassicTurret : public Turret
{
public:
    
};

class SlowingTurret : public Turret
{
public:
    float slowEffect; // slow effect coef (between 1 and 0)
};

class ExplosiveTurret : public Turret
{
public:
    float damageRange; // radius of the damage zone
};




class Enemy : public Entity
{
public:
    int damage;
    int hp;
    float speed;
    Vector2 direction;
};

class EnemyHealer : public Enemy
{
public:
    int heal;
};




Vector2 vector(Vector2 a, Vector2 b)
{
    Vector2 res;
    res.x=b.x-a.x;
    res.y=b.y-a.y;
    return res;
}

float normeVector(Vector2 vector)
{
    float res = sqrt(pow(vector.x,2)+pow(vector.y,2));
    return res;
}
