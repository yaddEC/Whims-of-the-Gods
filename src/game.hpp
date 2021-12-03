#pragma once
#include <mathematics.hpp>
#include <iostream>
#include <raylib.h>
#include "entities/turret.hpp"
#include "entities/enemy.hpp"

class Game
{
public:
    bool quit;
    bool start;
    bool pause;
    int money;
    int timer;
    int round;
    bool showTurretRange;
    Rectangle classicTurret;
    Rectangle slowingTurret;
    Rectangle explosiveTurret;
    Rectangle pauseSource;
    Rectangle warriorEnemy;
    Rectangle healerEnemy;
    Rectangle berserkerEnemy;
    TextureObject jackhammer;
    TextureObject menuScreen;
    TextureObject pauseScreen;
    Tile Spawn;
    Tile Despawn;
    Tilemap map;
    std::vector<Turret *> turret;
    std::vector<Enemy *> enemy;
    Game();
    void Menu();
    void UpdateAndDraw();
    void backUI();
    void frontUI();
    void UpdateAndDrawTurret();
    void UpdateAndDrawEnemy();
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, Color color);
