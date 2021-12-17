#include "../resources.hpp"
#include "../game.hpp"
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

void Turret::UpdateAndDraw(Texture2D tilesheet, Vector2 sourcePos, Game &game)
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
        for (auto j = 0u; target == -1 && j < game.enemies.size(); j++) // Check every enemy if turret has no current target
        {
            if (game.enemies[j]->active)
            {

              
                float normTurretEnemy = distance(game.enemies[j]->pos, Vector2{pos.x, pos.y});
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
        if (target != -1 && game.enemies[target]->hp > 0 && distance(game.enemies[target]->pos, Vector2{pos.x, pos.y}) <= range) // The turret rotate to aim the target
        {
            rotation = -acos((game.enemies[target]->pos.x - pos.x) / distance(game.enemies[target]->pos, Vector2{pos.x, pos.y})) * RAD2DEG;
            if (game.enemies[target]->pos.y - pos.y > 0)
            {
                rotation = -rotation;
            }
            rotation += 90;

            if (timer <= 0) // shoot if it can (timer = number of frames between each shots)
            {
                timer = FPS / attackSpeed;
                game.enemies[target]->hp -= damage;
                game.enemies[target]->timer = 5;

                DoSpecificEffect(game); // Specific effect for each turret type

                if (game.enemies[target]->hp <= 0) // target dead
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

    if (active && timer > FPS / attackSpeed - 3) // Draw shoot animation
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
    DrawCircleV(explosionPos, 50.0f, ColorAlpha(RED, 0.25f / (FPS / 2.0f) * (timer - (FPS / 2.0f))));
    DrawCircleV(explosionPos, 20.0f, ColorAlpha(ORANGE, 0.3f / (FPS / 2.0f) * (timer - (FPS / 2.0f))));
    float radius = (FPS - timer) * 2;

    DrawCircle(explosionPos.x, explosionPos.y + radius, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x, explosionPos.y - radius, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x + radius, explosionPos.y, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x - radius, explosionPos.y, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x + cos(45 * DEG2RAD) * radius, explosionPos.y + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x - cos(45 * DEG2RAD) * radius, explosionPos.y + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x + cos(45 * DEG2RAD) * radius, explosionPos.y - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
    DrawCircle(explosionPos.x - cos(45 * DEG2RAD) * radius, explosionPos.y - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, (timer - (FPS / 2.0f)) / (FPS / 2.0f)));
}

ClassicTurret::ClassicTurret()
{
    id = CLASSIC;
    damage = 10;
    price = 50;
    updatePrice = price / 2;
    attackSpeed = 2;
}

void ClassicTurret::DoSpecificEffect(Game& game)
{
    game.PlaySound(gRes->sounds.classic);
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

void SlowingTurret::DoSpecificEffect(Game& game)
{
    game.PlaySound(gRes->sounds.slowing);
    game.enemies[target]->slowingTimer = FPS / 2; // Slowing effect
    game.enemies[target]->slowingCoef = slowEffect;
}

ExplosiveTurret::ExplosiveTurret()
{
    id = EXPLOSIVE;
    damage = 20;
    price = 300;
    updatePrice = price / 2;
    attackSpeed = 1;
}

void ExplosiveTurret::DoSpecificEffect(Game& game)
{
    game.PlaySound(gRes->sounds.explosion);
    for (Enemy *e : game.enemies) // Area Damage
    {
        if (e != game.enemies[target] && e->active && collCirclex2(game.enemies[target]->pos, 50.0f, e->pos, e->radius))
        {
            e->hp -= damage;
            e->timer = 5;
        }
        explosionPos = game.enemies[target]->pos;
    }
}