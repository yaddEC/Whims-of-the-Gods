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

    //Game status
    bool quit;
    bool start;
    bool pause;
    bool gameOver;

    //Credits variables
    bool credit;
    int creditHeight;
    std::vector<const char *> creditTitle;
    int titleID;

    //Sound and music variables
    bool music;
    bool soundEffect;
    Music *currentMusic = nullptr;

    bool turretSelected = false; // Is a turret selected (dragged)
    bool jackActive = false;     // Is jackhammer slected (dragged)
    
    Timer timer; // Every timers

    // Turrets range variables
    bool showTurretRange;
    float opacityZone;
    
    //General variables
    int hp;
    int maxHp;
    int money;
    int moneyGain;
    int round;
    int maxEnemies;
    float newEnemiesMaxHp;
    int gameSpeed;
    bool highScoreBeated;

    //UI variables
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

    Tile Spawn;
    Tile Despawn;
    Tilemap map;

    std::vector<Turret *> turrets;
    std::vector<Enemy *> enemies;   

    //Functions
    Game();
    void Menu();
    void Credit();
    void UpdateAndDraw();
    void backUI();
    void frontUI();
    void UpdateAndDrawTurret();
    void UpdateAndDrawEnemy();
    bool Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color);
    void DrawUiTurret(int moneyNeeded, int roundUnlock, int type, const char *turretName, const char *damage, const char *speed, const char *special, Rectangle turret, Rectangle turretIcon, Color turretColor, Color textureColor, Color priceColor, Vector2 origin);
    bool DynamicButton(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color);
    void SoundButton(Rectangle dest, bool &type);
    void DrawTextWave();
    void NextWave();
    void DeathAnimation();
    void DrawGame();
    void DrawPause();
    void TimerUpdater();
    void DrawGameOver();
    void DrawUiTurret();
    void EnemyDestroyedAnimation(Enemy *&e);
    ~Game();
};

bool InRec(int x, int y, float width, float height);

bool InRec(Rectangle rec);

