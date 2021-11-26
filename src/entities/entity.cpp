#include "turret.hpp"
#include "enemy.hpp"
#include "tower.hpp"
#include "entity.hpp"

Enemy::Enemy()
{
    pos.x = rand() % 1024;
    pos.y = rand() % 728;

    int randomDegree = rand() % 360 + 1;
    direction.x = sin(randomDegree * DEG2RAD) * 3;
    direction.y = cos(randomDegree * DEG2RAD) * 3;
}

