#include "enemy.hpp"

static Vector2 Spawn;

void DefSpawn(Vector2 pos)
{
    Spawn = pos;
    
}

Enemy::Enemy()
{
    radius = 10.0f;
    prevTile = 0;
    healTimer = 0;
    slowingTimer = 0;
    slowingCoef = 1;
    active = true;

    pos.x = Spawn.x + 32;
    pos.y = Spawn.y + 32;
}

void Enemy::UpdateAndDraw(Tilemap &map, int round, std::vector<Enemy *> &enemy)
{
    float rot;
    Vector2 dirmem;

    if (posTile != GetTile(pos))
    {
        prevTile = posTile;
        posTile = GetTile(pos);
    }

    if ((map.tile[posTile].value == '>') || ((map.tile[posTile].value == 'L' && round < 20) && (round % 2 == 1)))
    {
        dirmem = {1, 0};
        rot = 0;
    }
    else if ((map.tile[posTile].value == 'V') || ((map.tile[posTile].value == 'L' && round < 20) && (round % 2 == 0)))
    {
        dirmem = {0, 1};
        rot = 90;
    }

    else if (map.tile[posTile].value == '<')
    {
        dirmem = {-1, 0};
        rot = 180;
    }

    else if (map.tile[posTile].value == 'A')
    {
        dirmem = {0, -1};
        rot = -90;
    }
    else
    {

        Tile nullTile(999, 64, 'g');
        Tile *leftTile = (map.tile[posTile - 1].road == true && posTile % map.width != 0) ? &map.tile[posTile - 1] : &nullTile;
        Tile *rightTile = (map.tile[posTile + 1].road == true && (posTile % map.width) != 15) ? &map.tile[posTile + 1] : &nullTile;
        Tile *forwardTile = (map.tile[posTile + map.width].road == true && posTile < 176) ? &map.tile[posTile + map.width] : &nullTile;
        Tile *backwardTile = (map.tile[posTile - map.width].road == true && posTile > map.width) ? &map.tile[posTile - map.width] : &nullTile;

        if (static_cast<int>(pos.x) % 64 >= 30 && static_cast<int>(pos.x) % 64 <= 33 && static_cast<int>(pos.y) % 64 >= 30 && static_cast<int>(pos.y) % 64 <= 33)
        {
            RandDirChooser(dirmem, pos, leftTile, rightTile, forwardTile, backwardTile, prevTile, rot);
        }
    }
    if (static_cast<int>(pos.x) % 64 >= 30 && static_cast<int>(pos.x) % 64 <= 33 && static_cast<int>(pos.y) % 64 >= 30 && static_cast<int>(pos.y) % 64 <= 33)
    {
        direction = dirmem;
        rotation = rot;
    }

    FrameTimer(slowingTimer);
    FrameTimer(timer);
    FrameTimer(healTimer);

    if (slowingTimer == 0 && slowingCoef != 1)
    {
        slowingCoef = 1;
    }
    pos.x += direction.x * slowingCoef * speed;
    pos.y += direction.y * slowingCoef * speed;

    if (maxHp == 30)
    {
        if (healTimer > 30)
        {
            DrawCircleLines(pos.x, pos.y, 50.0f, ColorAlpha(YELLOW, 0.5f / 30.f * (healTimer - 30.0f)));
        }
        if (healTimer == 0)
        {
            speed = 1;

            bool selfHeal = true;
            for (Enemy *t : enemy)
            {
                if (t != this && t->active && t->hp < t->maxHp && collCirclex2(t->pos, 50.0f, pos, radius))
                {
                    speed = 0.7f;
                    t->hp += 10;
                    healTimer = 60;
                    if (t->hp > t->maxHp)
                    {
                        t->hp = t->maxHp;
                    }
                    selfHeal = false;
                }
            }
            if (hp < maxHp && selfHeal)
            {
                hp += 10;
                healTimer = 60;
                if (hp > maxHp)
                {
                    hp = maxHp;
                }
            }
        }
    }

    Rectangle destRec{float((int)pos.x), float((int)pos.y), SIZE, SIZE};

    if (slowingTimer > 0)
    {
        DrawTexturePro(map.tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, SKYBLUE);
    }
    else
    {
        DrawTexturePro(map.tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, WHITE);
    }

    if (timer > 0)
    {
        DrawTexturePro(map.tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, ColorAlpha(RED, 0.5));
    }
  
    if (direction.x != 0 || direction.y!=0)
    {
        DrawRectangle(pos.x - 20, pos.y + 20, 40, 10, ColorAlpha(BLACK, 0.5));
        DrawRectangle(pos.x - 20, pos.y + 20, hp * 40 / maxHp, 10, GREEN);
        DrawRectangleLines(pos.x - 21, pos.y + 20, 42, 10, BLACK);
    }
}

Enemy::~Enemy()
{
}

Warrior::Warrior()
{
    damage = 2;
    speed = 0.8;
    hp = 60;
    maxHp = 60;
    reward = 5;
}

Healer::Healer()
{
    damage = 1;
    speed = 1;
    hp = 30;
    maxHp = 30;
    reward = 10;
}

Berserker::Berserker()
{
    damage = 5;
    speed = 0.6;
    hp = 120;
    maxHp = 120;
    reward = 20;
}