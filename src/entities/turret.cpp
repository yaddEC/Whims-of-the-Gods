#include "../resources.hpp"
#include "enemy.hpp"
#include "turret.hpp"

Turret::Turret()
{
    range = 100.0f;
    target = -1;
    slowEffect = 1;
    colorZone = DARKBLUE;
    showTurretUpgrade = false;
}

void Turret::UpdateAndDraw(std::vector<Enemy *> &enemy, Texture2D tilesheet, Vector2 sourcePos, Sounds &turretSounds, bool soundEffect)
{
    if (active) //if the turret is active
    {
        FrameTimer(timer);
        if (id == EXPLOSIVE && timer > 0)
        {
            DrawExplosionAnimation();
        }

        int nearestEnemyId = -1;
        int nearestEnemyDistance = -1;
        for (auto j = 0u; target == -1 && j < enemy.size(); j++) // Check every enemy if turret has no current target
        {
            if (enemy[j]->active)
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

            if (timer <= 0) // if can shoot
            {
                timer = 60 / attackSpeed;
                enemy[target]->hp -= damage;
                enemy[target]->timer = 5;

                if (id == CLASSIC && soundEffect) // Classic turret
                {
                    PlaySound(turretSounds.classic);
                }

                if (id == SLOWING) // Slowing turret
                {
                    if (soundEffect)
                    {
                        PlaySound(turretSounds.slowing);
                    }
                    enemy[target]->slowingTimer = FPS/2;  // Slowing effect
                    enemy[target]->slowingCoef = slowEffect;
                }
                else if (id == EXPLOSIVE) // Explosive turret
                {
                    if (soundEffect)
                    {
                        PlaySound(turretSounds.explosion);
                    }
                    for (Enemy *e : enemy) // Area Damage
                    {
                        if (e != enemy[target] && e->active && collCirclex2(enemy[target]->pos, 50.0f, e->pos, e->radius))
                        {
                            e->hp -= damage;
                            e->timer = 5;
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

    if (active && timer > 60 / attackSpeed - 3)  // Draw shoot animation
    {
        Rectangle source = {sourcePos.x, sourcePos.y, SIZE, SIZE};
        Rectangle dest = {pos.x, pos.y, SIZE, SIZE};
        Vector2 origin = {SIZE / 2, SIZE};
        DrawTexturePro(tilesheet, source, dest, origin, rotation, WHITE);
    }
    Rectangle destRec = {pos.x, pos.y, SIZE, SIZE};
    if (active)
        DrawTexturePro(tilesheet, {1280, 448, SIZE, SIZE}, destRec, {SIZE / 2, SIZE / 2}, 0, LIGHTGRAY); // Draw turret base

    DrawTexturePro(tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, WHITE); // Draw turret
}

void Turret::DrawExplosionAnimation()
{
    DrawCircleV(explosionPos, 50.0f, ColorAlpha(RED, 0.25f / 30.f * (timer - 30.0f)));
    DrawCircleV(explosionPos, 20.0f, ColorAlpha(ORANGE, 0.3f / 30.f * (timer - 30.0f)));
    float radius = (60 - timer) * 2;

    DrawCircle(explosionPos.x, explosionPos.y + radius, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x, explosionPos.y - radius, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x + radius, explosionPos.y, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x - radius, explosionPos.y, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x + cos(45 * DEG2RAD) * radius, explosionPos.y + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x - cos(45 * DEG2RAD) * radius, explosionPos.y + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x + cos(45 * DEG2RAD) * radius, explosionPos.y - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
    DrawCircle(explosionPos.x - cos(45 * DEG2RAD) * radius, explosionPos.y - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - 30) / 30.0f));
}

ClassicTurret::ClassicTurret()
{
    id = CLASSIC;
    damage = 10;
    price = 50;
    updatePrice = price / 2;
    attackSpeed = 2;
}

SlowingTurret::SlowingTurret()
{
    id = SLOWING;
    damage = 5;
    price = 150;
    updatePrice = price / 2;
    attackSpeed = 6;
    slowEffect = 0.5f;
}

ExplosiveTurret::ExplosiveTurret()
{
    id = EXPLOSIVE;
    damage = 20;
    price = 300;
    updatePrice = price / 2;
    attackSpeed = 1;
}