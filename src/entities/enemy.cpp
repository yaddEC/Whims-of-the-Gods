#include "enemy.hpp"
#include "../resources.hpp"

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

void Enemy::UpdateAndDraw(Tilemap &map, int round, std::vector<Enemy *> &enemies)
{

    GetEnemyDirection(map, round);

    FrameTimer(slowingTimer); // Update Timers
    FrameTimer(timer);
    FrameTimer(healTimer);

    if (slowingTimer == 0 && slowingCoef != 1) // Update slowing effect
    {
        slowingCoef = 1;
    }

    pos.x += direction.x * slowingCoef * speed; // Update enemy position
    pos.y += direction.y * slowingCoef * speed;

    if (id == HEALER)
    {
        ActivateHealingZone(enemies);
    }

    Rectangle destRec{float((int)pos.x), float((int)pos.y), SIZE, SIZE};

    if (slowingTimer > 0) // slowed enemy animation
    {
        DrawTexturePro(gRes->textures.tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, SKYBLUE);
    }
    else // draw enemy
    {
        DrawTexturePro(gRes->textures.tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, WHITE);
    }

    if (timer > 0) // Enemy hit animation
    {
        DrawTexturePro(gRes->textures.tilesheet, sourceTexture, destRec, {SIZE / 2, SIZE / 2}, rotation, ColorAlpha(RED, 0.5));
    }

    if (active && (direction.x!=0 || direction.y!=0)) // Draw enemy health bar
    {
        DrawRectangle(pos.x - 20, pos.y + 20, 40, 10, ColorAlpha(BLACK, 0.5));
        DrawRectangle(pos.x - 20, pos.y + 20, hp * 40 / maxHp, 10, GREEN);
        DrawRectangleLines(pos.x - 21, pos.y + 20, 42, 10, BLACK);
    }
}

void Enemy::GetEnemyDirection(Tilemap &map, int round)
{
    float rot;
    Vector2 dirmem;

    if (posTile != Tile::GetTile(pos))
    {
        prevTile = posTile;
        posTile = Tile::GetTile(pos);
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

        Tile nullTile(999, SIZE, 'g');
        Tile *leftTile = (map.tile[posTile - 1].road == true && posTile % map.width != 0) ? &map.tile[posTile - 1] : &nullTile;
        Tile *rightTile = (map.tile[posTile + 1].road == true && (posTile % map.width) != 15) ? &map.tile[posTile + 1] : &nullTile;
        Tile *forwardTile = (map.tile[posTile + map.width].road == true && posTile < 176) ? &map.tile[posTile + map.width] : &nullTile;
        Tile *backwardTile = (map.tile[posTile - map.width].road == true && posTile > map.width) ? &map.tile[posTile - map.width] : &nullTile;

        if (static_cast<int>(pos.x) % (int)SIZE >= 30 && static_cast<int>(pos.x) % (int)SIZE <= 33 && static_cast<int>(pos.y) % (int)SIZE >= 30 && static_cast<int>(pos.y) % (int)SIZE <= 33)
        {
            RandDirChooser(dirmem, pos, leftTile, rightTile, forwardTile, backwardTile, prevTile, rot);
        }
    }
    if (static_cast<int>(pos.x) % (int)SIZE >= 30 && static_cast<int>(pos.x) % (int)SIZE <= 33 && static_cast<int>(pos.y) % (int)SIZE >= 30 && static_cast<int>(pos.y) % (int)SIZE <= 33)
    {
        direction = dirmem;
        rotation = rot;
    }
}

void Enemy::ActivateHealingZone(std::vector<Enemy *> &enemies)
{
    if (healTimer > FPS / 2)
    {
        DrawCircleLines(pos.x, pos.y, 50.0f, ColorAlpha(YELLOW, 0.5f / (FPS / 2.0f) * (healTimer - (FPS / 2.0f))));
    }
    if (healTimer == 0)
    {
        speed = 1.4;

        bool selfHeal = true;
        for (Enemy *t : enemies)
        {
            if (t != this && t->active && t->hp < t->maxHp && collCirclex2(t->pos, 50.0f, pos, radius))
            {
                speed = 1.1;
                t->hp += 10;
                healTimer = FPS;
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
            healTimer = FPS;
            if (hp > maxHp)
            {
                hp = maxHp;
            }
        }
    }
}

Enemy::~Enemy()
{
}

Warrior::Warrior()
{
    id = WARRIOR;
    damage = 2;
    speed = 1.2;
    hp = 90;
    maxHp = 90;
    reward = 5;
}

Healer::Healer()
{
    id = HEALER;
    damage = 1;
    speed = 1.4;
    hp = 45;
    maxHp = 45;
    reward = 10;
}

Berserker::Berserker()
{
    id = BERSERKER;
    damage = 5;
    speed = 1.0;
    hp = 180;
    maxHp = 180;
    reward = 20;
}