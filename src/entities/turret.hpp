#pragma once
#include "entity.hpp"
#include "enemy.hpp"

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

class Turret : public Entity
{
public:
    float range = 100.0f;
    float rotation = 0.0f;
    int target = -1;
    int damage;
    int price;
    float attackSpeed;
    float slowEffect;
    int timer;

    void UpdateAndDraw(std::vector<Enemy *> &enemy)
    {
        if (active) //if the turret is active
        {
            int nearestEnemyId = -1;
            int nearestEnemyDistance = -1;
            for (auto j = 0u; target == -1 && j < enemy.size(); j++) // Check every enemy if turret has no current target
            {
                if (enemy[j]->hp > 0)
                {

                    float normTurretEnemy = norm(vector(enemy[j]->pos, Vector2{pos.x, pos.y}));
                    if (normTurretEnemy <= range) // if enemy in turret range
                    {
                        if (nearestEnemyDistance == -1 || normTurretEnemy < nearestEnemyDistance) // if enemy closer than current nearest enemy
                        {
                            nearestEnemyDistance = normTurretEnemy;
                            nearestEnemyId = j;
                        }
                    }
                }
            }
            if (nearestEnemyId != -1) // targets nearest enemy if turret has no current target
            {
                target = nearestEnemyId;
            }
            if (target != -1 && enemy[target]->hp>0 && norm(vector(enemy[target]->pos, Vector2{pos.x, pos.y})) <= range) // The turret rotate to aim the target
            {
                rotation = -acos((enemy[target]->pos.x - pos.x) / norm(vector(enemy[target]->pos, Vector2{pos.x, pos.y}))) * RAD2DEG;
                if (enemy[target]->pos.y - pos.y > 0)
                {
                    rotation = -rotation;
                }
                rotation += 90;
                enemy[target]->hp -= 1;
                
                if (enemy[target]->hp <= 0) // target dead
                {
                    target = -1;
                }   
            }
            else // No more target
            {
                target = -1;
            }

      
        }

        if (InRec(pos.x - 32, pos.y - 32, SIZE, SIZE))
        {
            DrawCircleV(pos, range, ColorAlpha(DARKBLUE, 0.3)); // Draw turret range
        }
        Rectangle destRec = {pos.x, pos.y, SIZE, SIZE};
        DrawTexturePro(texture.model, texture.sourceRec, destRec, texture.origin, rotation, WHITE); // Draw turret
    }
    virtual ~Turret()
    {
    }
};

class ClassicTurret : public Turret
{
 
public:
    ClassicTurret()
    {   
        damage = 10;
        price = 100;
        attackSpeed = 4;
        slowEffect = 1;
    }
};

class SlowingTurret : public Turret
{
public:
    SlowingTurret()
    {

        damage = 5;
        price = 150;
        attackSpeed = 2;
        slowEffect = 0.5;
    }
};

class ExplosiveTurret : public Turret
{
public:
    ExplosiveTurret()
    {

        damage = 10;
        price = 200;
        attackSpeed = 1;
        slowEffect = 1;
    }
};
