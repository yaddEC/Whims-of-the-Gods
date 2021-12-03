#include "enemy.hpp"
#include "turret.hpp"
#include "../game.hpp"

Entity::Entity()
{
    rotation = 0.0f;
    active = false;
    posTile=0;
}

bool checkTile(int tile, std::vector<int > PrevTiles)
{
    for (int i : PrevTiles)
    {
        if (i == tile)
            return false;
    }
    return true;
}

void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b, int PrevTile, Tile *c, std::vector<int > PrevTiles, Tile *d)
{
    srand(time(0));
    int i = 0;
    int random;
    bool check = false;
    check = false;
    if (b != nullptr)
        i++;
    if (c != nullptr)
        i++;
    if (d != nullptr)
        i++;
    if (i == 0)
        random = 0;
    else
        random = (rand() % i) + 1;
    if (random < 2)
    {
        while (!check)
        {
            if (i == 0)
                random = 0;
            else
                random = (rand() % 2) ;
    
            switch (random)
            {
            case 0:
                if (PrevTile != a->mTilePos)
                {
                    DirGet(pos, a->mPos, direction);
                    check = true;
                }
                break;
            case 1:
                if (PrevTile != b->mTilePos)
                {
                    DirGet(pos, b->mPos, direction);
                    check = true;
                }
                break;
            default:
                break;
            }
        }
    }
    else
    {
        while (!check)
        {

            if (i == 0)
                random = 0;
            else
                random = (rand() % i) ;
               
            switch (random)
            {
            case 0:
                if (checkTile(a->mTilePos, PrevTiles) && PrevTile != a->mTilePos)
                {
                    DirGet(pos, a->mPos, direction);
                    check = true;
                }
                break;
            case 1:
                if (checkTile(b->mTilePos, PrevTiles) && PrevTile != b->mTilePos)
                {
                    DirGet(pos, b->mPos, direction);
                    check = true;
                }
                break;
            case 2:
                if (checkTile(c->mTilePos, PrevTiles) && PrevTile != c->mTilePos)
                {
                    DirGet(pos, c->mPos, direction);
                    check = true;
                }
                break;
            case 3:
                if (checkTile(d->mTilePos, PrevTiles) && PrevTile != d->mTilePos)
                {
                    DirGet(pos, d->mPos, direction);
                    check = true;
                }
                break;
            default:
                break;
            }
        }
    }
}

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




