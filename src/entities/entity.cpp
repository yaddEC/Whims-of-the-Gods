#include "enemy.hpp"
#include "turret.hpp"
#include "../game.hpp"

Entity::Entity()
{
    rotation = 0.0f;
    active = false;
    posTile = 0;
    timer = 0;
}


void RandDirChooser(Vector2 &direction, Vector2 pos, Tile *a, Tile *b, Tile *c, Tile *d, int PrevTile,float &rotation)
{
    srand(time(0));
    int i = 0;
    int random;
    bool check = false;
    check = false;
    if (a->value != 'g')
    {
        i++;
    }

    if (b->value != 'g')
    {
        i++;
    }
    if (c->value != 'g')
    {
        i++;
    }
    if (d->value != 'g')
    {
        i++;
    }
    
    
        random = rand()%4;
    
    
        while (!check)
        {
                random = rand()%4;

            switch (random)
            {
            case 0:
            
                if ( PrevTile != a->tilePos &&  a->value!='g')
                {
                    direction={-1,0};
                    check = true;
                    rotation=180;
                }
                break;
            case 1:
                if ( PrevTile != b->tilePos &&  b->value!='g')
                {
                    direction={1,0};
                    check = true;
                    rotation=0;
                }
                break;
            case 2:
                if ( PrevTile != c->tilePos &&  c->value!='g')
                {
                    direction={0,1};
                    check = true;
                    rotation=90;
                }
                break;
            case 3:
                if ( PrevTile != d->tilePos &&  d->value!='g')
                {
                    direction={0,-1};
                    check = true;
                    rotation=-90;
                }
                break;
            default:
                break;
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

void FrameTimer(int &timer) // decrease timer by one if is greater than 0
{
    if (timer > 0)
    {
        timer--;
    }
}



