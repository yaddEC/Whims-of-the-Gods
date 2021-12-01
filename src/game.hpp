#pragma once
#include <mathematics.hpp>
#include <iostream>
#include <raylib.h>
#include "entities/turret.hpp"
#include "entities/enemy.hpp"
#include "entities/tower.hpp"



class Game
{
public:
    bool quit = false;
    bool start = false;
    int money = 100;
    int timer;
    int round;
    bool showTurretRange = false;
    TextureObject classicTurret;
    TextureObject slowingTurret;
    TextureObject explosiveTurret;
    TextureObject jackhammer;
    Tilemap map;
    std::vector<Turret *> turret;
    std::vector<Enemy *> enemy;
    Game();
    void Menu();
    void UpdateAndDraw();
    void UpdateAndDrawUI();
    void UpdateAndDrawTurret();
    void UpdateAndDrawEnemy();
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, Color color);
