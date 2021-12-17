#pragma once
#include <mathematics.hpp>
#include <iostream>
#include <raylib.h>
#include "entities/turret.hpp"
#include "entities/enemy.hpp"
struct Timer
{
    int spawnTimer;
    int frameCounter;
    int animationTimer;
    int secondTimer;
    bool parTimer;
    int moneyTimer; // Timer for the money gain animation (the "+$" stay for a cupple of frames)
    int waveTimer;
    int timerFadeScreen;

};

class Game
{
public:
    bool quit;
    bool start;
    bool pause;
    bool gameOver;
    bool music;
    bool soundEffect;
    bool turretSelected = false; // Is a turret selected (dragged)
    bool jackActive = false;     // Is jackhammer slected (dragged)
    float opacityZone;
    Timer timer;

    int maxEnemies;
    int gameSpeed;

    int moneyGain;

    bool credit;
    int creditHeight;
    std::vector<const char *> creditTitle;
    int titleID;

    int hp;
    int maxHp;
    int money;

    int round;
    bool showTurretRange;
    bool highScoreBeated;
    Rectangle classicTurret;
    Rectangle slowingTurret;
    Rectangle explosiveTurret;
    Rectangle pauseSource;
    Rectangle warriorEnemy;
    Rectangle healerEnemy;
    Rectangle berserkerEnemy;
    float scrollingFive;
    float scrollingFourth;
    float scrollingThird;
    float scrollingSecond;
    float scrollingFirst;

    Music *currentMusic = nullptr;

    Tile Spawn;
    Tile Despawn;
    Tilemap map;

    std::vector<Turret *> turrets; // TODO: Rename turrets
    std::vector<Enemy *> enemies;   // TODO: Rename enemies
    Game();
    void Menu();
    void Credit();
    void UpdateAndDraw();
    void backUI();
    void frontUI();
    void UpdateAndDrawTurret();
    void UpdateAndDrawEnemy();
    bool Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color);
    bool DynamicButton(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color);
    void SoundButton(Rectangle dest, bool &type);
    void DrawTextWave();
    void NextWave();
    void DeathAnimation();
    void DrawGame();
    void DrawPause();
    void TimerUpdater();
    void DrawGameOver();
    void EnemyDestroyedAnimation(Enemy *&e);
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

bool Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color, Sound &sound);
