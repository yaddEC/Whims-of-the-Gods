#include <raylib.h>

class GameSounds
{
public:
    Music mainTheme;
    Music secondTheme;
    Music gameOver;
    Music creditsTheme;
    Music kaboom;
    Sound button;
    Sound sellTurret;
    GameSounds();
    ~GameSounds();
};

class TurretSounds
{
public:
    Sound classic;
    Sound slowing;
    Sound explosion;
    TurretSounds();
    ~TurretSounds();
};

class EnemySounds
{
public:
    EnemySounds();
    ~EnemySounds();
};