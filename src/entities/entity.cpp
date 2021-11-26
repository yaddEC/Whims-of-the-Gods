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


Enemy::Enemy()
{
    pos.x = rand() % 1024;
    pos.y = rand() % 768;

    int randomDegree = rand() % 360 + 1;
    direction.x = sin(randomDegree * DEG2RAD) * 3;
    direction.y = cos(randomDegree * DEG2RAD) * 3;
}

