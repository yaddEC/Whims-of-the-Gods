#pragma once
#include <mathematics.hpp>
#include <iostream>
#include <raylib.h>
#include "entities/turret.hpp"
#include "entities/enemy.hpp"
#include "entities/tile.hpp"

class Game
{
public:
    bool quit;
    bool start;
    bool pause;
    bool gameOver;
    bool music;
    bool soundEffect;
    int hp;
    int maxHp;
    int money;
    int timer;
    int timerFadeScreen;
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
    float scrollingFive;
    float scrollingFourth;
    float scrollingThird;
    float scrollingSecond;
    float scrollingFirst;
    Texture2D five ;
    Texture2D fourth ;
    Texture2D third ;
    Texture2D second;
    Texture2D first ;
    Texture2D title ;
    Tile Spawn;
    Tile Despawn;
    Tilemap map;
    GameSounds gameSounds;
    TurretSounds turretSounds;
    EnemySounds enemySounds;
    std::vector<Turret *> turret;
    std::vector<Enemy *> enemy;
    Game();
    void Menu();
    void UpdateAndDraw();
    void backUI();
    void frontUI();
    void UpdateAndDrawTurret();
    void UpdateAndDrawEnemy();
    bool Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color);
    bool DynamicButton(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color);
    void SoundButton(Rectangle dest, bool &type);
    void DrawTextWave();
    void EnemyDestroyedAnimation(Enemy *&e);
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color, Sound &sound);
