#pragma once
#include "entity.hpp"

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

class Enemy; // Forward declaration
struct Sounds; // Forward declaration

class Turret : public Entity
{
public:
    enum Type
    {
        CLASSIC=1,
        SLOWING,
        EXPLOSIVE
    };
    Type id;
    float range;
    int target;
    int price;
    int updatePrice;
    float attackSpeed;
    Vector2 explosionPos;
    float slowEffect;
    bool showTurretUpgrade;
    Color colorZone;

    void UpdateAndDraw(std::vector<Enemy *> &enemy, Texture2D tilesheet, Vector2 sourcePos, Sounds &turretSounds, bool soundEffect);

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