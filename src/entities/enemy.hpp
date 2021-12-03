#pragma once
#include "entity.hpp"
bool checkTile(int tile, std::vector<int *> PrevTiles);

void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b = nullptr, int PrevTile = 999, Tile *c = nullptr, std::vector<int *> PrevTiles = {}, Tile *d = nullptr);

class Enemy : public Entity
{
public:
    Enemy();

    int radius = 5.0f;
    int damage;
    std::vector<int *> PrevTiles;
    int hp = 60;
    int maxHp = 60;
    int prevTile = 0;
    int timer = 0;
    float speed = 1;
    int slowingTimer = 0;
    float slowingCoef = 1;
    Vector2 direction;
    int reward;
    Color color; // TEMPORAIRE

    void UpdateAndDraw(Tilemap &map, int round,std::vector<Enemy *> &enemy)
    {

        if (posTile != GetTile(pos))
        {
            prevTile = posTile;
            posTile = GetTile(pos);
        }

        if (map.tile[posTile].value == '>')
        {
            RandDirChooser(direction, pos, &map.tile[posTile + 1]);
        }
        else if (map.tile[posTile].value == '<')
        {
            RandDirChooser(direction, pos, &map.tile[posTile - 1]);
        }
        else if (map.tile[posTile].value == 'T' && round<20)
        {
            if(round%2==1)
            {
                RandDirChooser(direction, pos, &map.tile[posTile + 1]);
            }
            else
            {
                RandDirChooser(direction, pos, &map.tile[posTile - 1]);
            }

        }
         else if (map.tile[posTile].value == 'L' && round<20)
        {
            if(round%2==1)
            {
                RandDirChooser(direction, pos, &map.tile[posTile + 1]);
            }
            else
            {
                RandDirChooser(direction, pos, &map.tile[posTile + 16]);
            }

        }
        else if (map.tile[posTile].value == 'V')
        {
            RandDirChooser(direction, pos, &map.tile[posTile + 16]);
        }
        else if (map.tile[posTile].value == 'A')
        {
            RandDirChooser(direction, pos, &map.tile[posTile - 16]);
        }
        else
        {

            if (posTile > 16) // if not the first line we can do -16
            {
                if (posTile < 176) // if not last line we can do +16
                {
                    if (posTile % 16 == 0) // if first of line we cant do -1
                    {
                        if (map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                        {
                            PrevTiles.push_back(new int);
                            PrevTiles.back() = &prevTile;
                            RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile + 16], prevTile, &map.tile[posTile - 16], PrevTiles);
                        }
                        else
                        {
                            if (map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile + 16], prevTile);
                            else if (map.tile[posTile + 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile - 16], prevTile);
                            else if (map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 16], &map.tile[posTile - 16], prevTile);
                            else
                            {
                                if (map.tile[posTile + 1].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 1]);
                                else if (map.tile[posTile + 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 16]);
                                else if (map.tile[posTile - 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                            }
                        }
                    }
                    else if ((posTile % 16) + 15 == 15) //if last of line we cant do +1
                    {

                        if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                        {
                            PrevTiles.push_back(new int);
                            PrevTiles.back() = &prevTile;
                            RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 16], prevTile, &map.tile[posTile - 16], PrevTiles);
                        }
                        else
                        {
                            if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 16], prevTile);
                            else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile - 16], prevTile);
                            else if (map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 16], &map.tile[posTile - 16], prevTile);
                            else
                            {
                                if (map.tile[posTile - 1].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 1]);
                                else if (map.tile[posTile + 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 16]);
                                else if (map.tile[posTile - 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                            }
                        }
                    }
                    else // if neither of those we can do +1 / -1
                    {
                        if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                        {
                            PrevTiles.push_back(new int);
                            PrevTiles.back() = &prevTile;
                            RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile, &map.tile[posTile + 16], PrevTiles, &map.tile[posTile + 16]);
                        }
                        else
                        {
                            if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                            {
                                PrevTiles.push_back(new int);
                                PrevTiles.back() = &prevTile;
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile, &map.tile[posTile + 16], PrevTiles);
                            }
                            else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                            {
                                PrevTiles.push_back(new int);
                                PrevTiles.back() = &prevTile;
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile, &map.tile[posTile - 16], PrevTiles);
                            }
                            else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                            {
                                PrevTiles.push_back(new int);
                                PrevTiles.back() = &prevTile;
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 16], prevTile, &map.tile[posTile - 16], PrevTiles);
                            }
                            else if (map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                            {
                                PrevTiles.push_back(new int);
                                PrevTiles.back() = &prevTile;
                                RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile + 16], prevTile, &map.tile[posTile - 16], PrevTiles);
                            }
                            else
                            {
                                if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile);
                                else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 16], prevTile);
                                else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile - 16], prevTile);
                                else if (map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile + 16], prevTile);
                                else if (map.tile[posTile + 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile - 16], prevTile);
                                else if (map.tile[posTile + 16].value != 'O' && map.tile[posTile - 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 16], &map.tile[posTile - 16], prevTile);
                                else
                                {
                                    if (map.tile[posTile + 1].value != 'O')
                                        RandDirChooser(direction, pos, &map.tile[posTile + 1]);
                                    else if (map.tile[posTile - 1].value != 'O')
                                        RandDirChooser(direction, pos, &map.tile[posTile - 1]);
                                    else if (map.tile[posTile + 16].value != 'O')
                                        RandDirChooser(direction, pos, &map.tile[posTile + 16]);
                                    else if (map.tile[posTile - 16].value != 'O')
                                        RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                                }
                            }
                        }
                    }
                }
                else // if last line cant do +16
                {
                    if (posTile % 16 == 0) // if first of line we cant do -1
                    {
                        if (map.tile[posTile + 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile - 16], prevTile);
                        else
                        {
                            if (map.tile[posTile + 1].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 1]);
                            else if (map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                        }
                    }
                    else if ((posTile % 16) + 15 == 15) //if last of line we cant do +1
                    {

                        if (map.tile[posTile - 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile - 16], prevTile);

                        else
                        {
                            if (map.tile[posTile - 1].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 1]);

                            else if (map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                        }
                    }
                    else // if neither of those we can do +1 / -1
                    {
                        if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                        {
                            PrevTiles.push_back(new int);
                            PrevTiles.back() = &prevTile;
                            RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile, &map.tile[posTile - 16], PrevTiles);
                        }
                        else
                        {
                            if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile);
                            else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile - 16], prevTile);

                            else if (map.tile[posTile + 1].value != 'O' && map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile - 16], prevTile);
                            else
                            {
                                if (map.tile[posTile + 1].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile + 1]);
                                else if (map.tile[posTile - 1].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 1]);
                                else if (map.tile[posTile - 16].value != 'O')
                                    RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                            }
                        }
                    }
                }
            }
            else // if first line cant do -16
            {
                if (posTile % 16 == 0) // if first of line we cant do -1
                {
                    if (map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                        RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile + 16], prevTile);

                    else
                    {
                        if (map.tile[posTile + 1].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile + 1]);
                        else if (map.tile[posTile + 16].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile + 16]);
                    }
                }
                else if ((posTile % 16) + 15 == 15) //if last of line we cant do +1
                {
                    if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                        RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 16], prevTile);
                    else
                    {
                        if (map.tile[posTile - 1].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile - 1]);
                        else if (map.tile[posTile + 16].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile + 16]);
                    }
                }
                else // if neither of those we can do +1 / -1
                {
                    if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                    {
                        PrevTiles.push_back(new int);
                        PrevTiles.back() = &prevTile;
                        RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile, &map.tile[posTile + 16], PrevTiles);
                    }
                    else
                    {
                        if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 1].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 1], prevTile);
                        else if (map.tile[posTile - 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile - 1], &map.tile[posTile + 16], prevTile);

                        else if (map.tile[posTile + 1].value != 'O' && map.tile[posTile + 16].value != 'O')
                            RandDirChooser(direction, pos, &map.tile[posTile + 1], &map.tile[posTile + 16], prevTile);

                        else
                        {
                            if (map.tile[posTile + 1].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile + 1]);
                            else if (map.tile[posTile - 1].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 1]);
                            else if (map.tile[posTile - 16].value != 'O')
                                RandDirChooser(direction, pos, &map.tile[posTile - 16]);
                        }
                    }
                }
            }
        }

        FrameTimer(slowingTimer);
        FrameTimer(timer);



        if (slowingTimer == 0 && slowingCoef != 1)
        {
            slowingCoef = 1;
        }
        pos.x += direction.x * slowingCoef * speed;
        pos.y += direction.y * slowingCoef * speed;

        if (maxHp == 30)
        {
            
            if(timer>30)
            {
                DrawCircleLines(pos.x, pos.y, 50.0f, ColorAlpha(YELLOW, 0.5f/30.f * (timer-30.0f)));
            }
            if (timer == 0)
            {
                speed = 1;
                
                bool selfHeal = true;
                for (Enemy *t : enemy)
                {
                    if (t != this && t->hp < t->maxHp && collCirclex2(t->pos, 50.0f, pos, radius))
                    {
                        speed = 0.7f;
                        t->hp += 10;
                        timer=60;
                        if (t->hp > t->maxHp)
                        {
                            t->hp = t->maxHp;
                        }
                        selfHeal = false;
                    }
                }
                if (hp<maxHp && selfHeal)
                {
                    hp += 10;
                    timer=60;
                    if (hp > maxHp)
                    {
                        hp = maxHp;
                    }
                }
            }
        }

        Rectangle destRec {pos.x, pos.y, SIZE, SIZE};
        rotation = -atan((direction.y) / (direction.x) ) * RAD2DEG  ;
        if (pos.y + direction.y)
        {
            rotation = -rotation;
        }
        DrawTexturePro(map.tilesheet, sourceTexture, destRec, {SIZE/2, SIZE/2}, rotation, WHITE);
        DrawRectangle(pos.x - 20, pos.y + 20, 40, 10, ColorAlpha(BLACK, 0.5));
        DrawRectangle(pos.x - 20, pos.y + 20, hp * 40 / maxHp, 10, GREEN);
        DrawRectangleLines(pos.x - 21, pos.y + 20, 42, 10, BLACK);
    }
    virtual ~Enemy()
    {
    }
};

class Warrior : public Enemy
{
public:
    Warrior()
    {
        color = RED;
        damage = 2;
        speed = 0.8;
        hp = 60;
        maxHp = 60;
        reward = 5;
    }
};

class Healer : public Enemy
{

public:
    Healer()
    {
        color = VIOLET;
        damage = 1;
        speed = 1;
        hp = 30;
        maxHp = 30;
        reward = 10;
    }
};

class Berserker : public Enemy
{
public:
    Berserker()
    {
        color = MAROON;
        radius = 7.0f;
        damage = 5;
        speed = 0.6;
        hp = 120;
        maxHp = 120;
        reward = 20;
    }
};
