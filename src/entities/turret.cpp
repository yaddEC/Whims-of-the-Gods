#include "turret.hpp"

Turret::Turret()
{
    range = 100.0f;
    target = -1;
    slowEffect = 1;
    timer = 0;
    colorZone = DARKBLUE;
}

void Turret::UpdateAndDraw(std::vector<Enemy *> &enemy, Texture2D tilesheet, Vector2 sourcePos)
{
    if (active) //if the turret is active
    {
        FrameTimer(timer);
        if (id == 3 && timer > 0)
        {
            DrawCircle(explosionPos.x, explosionPos.y, 50.0f, ColorAlpha(ORANGE, 0.5f / 30.f * (timer - 30.0f)));
        }
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
        if (target != -1 && enemy[target]->hp > 0 && norm(vector(enemy[target]->pos, Vector2{pos.x, pos.y})) <= range) // The turret rotate to aim the target
        {
            rotation = -acos((enemy[target]->pos.x - pos.x) / norm(vector(enemy[target]->pos, Vector2{pos.x, pos.y}))) * RAD2DEG;
            if (enemy[target]->pos.y - pos.y > 0)
            {
                rotation = -rotation;
            }
            rotation += 90;

            if (timer <= 0)
            {
                timer = 60 / attackSpeed;
                enemy[target]->hp -= damage;
                if (id == 2)
                {
                    enemy[target]->slowingTimer = 30;
                    enemy[target]->slowingCoef = slowEffect;
                }
                else if (id == 3)
                {
                    for (Enemy *e : enemy)
                    {
                        if (e != enemy[target] && collCirclex2(enemy[target]->pos, 50.0f, e->pos, e->radius))
                        {
                            e->hp -= damage;
                        }
                        explosionPos = enemy[target]->pos;
                    }
                }
                if (enemy[target]->hp <= 0) // target dead
                {
                    target = -1;
                }
            }
        }
        else // No more target
        {
            target = -1;
        }
    }

    if (active && timer > 60 / attackSpeed - 3)
    {
        Rectangle source = {sourcePos.x, sourcePos.y, SIZE, SIZE};
        Rectangle dest = {pos.x, pos.y, SIZE, SIZE};
        Vector2 origin = {SIZE / 2, SIZE};
        DrawTexturePro(tilesheet, source, dest, origin, rotation, WHITE);
    }
    Rectangle destRec = {pos.x, pos.y, SIZE, SIZE};

    DrawTexturePro(tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, WHITE); // Draw turret
}

ClassicTurret::ClassicTurret()
{
    damage = 10;
    price = 50;
    attackSpeed = 2;
}

SlowingTurret::SlowingTurret()
{
    damage = 5;
    price = 150;
    attackSpeed = 6;
    slowEffect = 0.5f;
}

ExplosiveTurret::ExplosiveTurret()
{
    damage = 20;
    price = 300;
    attackSpeed = 1;
}