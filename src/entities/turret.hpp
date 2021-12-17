#pragma once
#include "entity.hpp"

bool InRec(int x, int y, float width, float height);
bool InRec(Rectangle rec);

// Forward declaration
class Enemy;
struct Sounds;
class Game;

enum TurretType
{
    CLASSIC = 1,
    SLOWING,
    EXPLOSIVE
};

class Turret : public Entity
{
public:
    TurretType id;
    float range;
    int target;
    int price;
    int updatePrice;
    float attackSpeed;
    Vector2 explosionPos;
    float slowEffect;
    bool showTurretUpgrade;
    Color colorZone;

    void UpdateAndDraw(Texture2D tilesheet, Vector2 sourcePos, Game& game);

    Turret();

    virtual ~Turret()
    {
    }

    void DrawExplosionAnimation();
    virtual void DoSpecificEffect(Game& game){};
};

class ClassicTurret : public Turret
{

public:
    ClassicTurret();
    void DoSpecificEffect(Game& game) override;
};

class SlowingTurret : public Turret
{
public:
    SlowingTurret();
    void DoSpecificEffect(Game& game) override;
};

class ExplosiveTurret : public Turret
{
public:
    ExplosiveTurret();
    void DoSpecificEffect(Game& game) override;
};