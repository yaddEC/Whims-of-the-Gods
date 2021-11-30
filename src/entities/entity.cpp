#include "enemy.hpp"
#include "turret.hpp"
#include "tower.hpp"



bool InRec(int x, int y, float width, float height)
{
    int X = GetMouseX();
    int Y = GetMouseY();

    if (
        (X >= x) &&
        (X <= x + width) &&
        (Y >= y) &&
        (Y <= y + height))
    {
        return true;
    }
    return false;
}
bool InRec(Rectangle rec)
{
    int X = GetMouseX();
    int Y = GetMouseY();

    if (
        (X >= rec.x) &&
        (X <= rec.x + rec.width) &&
        (Y >= rec.y) &&
        (Y <= rec.y + rec.height))
    {
        return true;
    }
    return false;
}

void FrameTimer(int &timer)
{
    if (timer > 0)
    {
        timer--;
    }
}

Enemy::Enemy()
{
    pos.x = rand() % 1024;
    pos.y = rand() % 768;

    int randomDegree = rand() % 360 + 1;
    direction.x = sin(randomDegree * DEG2RAD) * 3;
    direction.y = cos(randomDegree * DEG2RAD) * 3;
}

void Turret::UpdateAndDraw(std::vector<Enemy *> &enemy, Texture2D tilesheet, Vector2 sourcePos)
{
    if (active) //if the turret is active
    {
        FrameTimer(timer);
        if(id==3 && timer>0)
        {
            DrawCircle(explosionPos.x,explosionPos.y,50.0f,ColorAlpha(DARKGRAY, 0.5f/30.f * (timer-30.0f)));
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
                if(id==2)
                {
                    enemy[target]->slowingTimer=30;
                    enemy[target]->slowingCoef=slowEffect;
                }
                else if(id==3)
                {
                    for (Enemy *e : enemy)
                    {
                        if(e!=enemy[target] && collCirclex2(enemy[target]->pos, 50.0f, e->pos, e->radius))
                        {
                            e->hp-=damage;
                        }
                        explosionPos=enemy[target]->pos;
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



    if (active && timer > 60/attackSpeed - 3)
    {
        Rectangle source = {sourcePos.x, sourcePos.y, SIZE, SIZE};
        Rectangle dest = {pos.x, pos.y, SIZE, SIZE};
        Vector2 origin = {SIZE / 2, SIZE};
        DrawTexturePro(tilesheet, source, dest, origin, rotation, WHITE);
        
    }
    Rectangle destRec = {pos.x, pos.y, SIZE, SIZE};

    DrawTexturePro(texture.model, texture.sourceRec, destRec, texture.origin, rotation, WHITE); // Draw turret
}
