#include <raylib.h>

class GameSounds
{
public:
    Music mainTheme;
    Music secondTheme;
    Sound button;
    Sound sellTurret;
    Music gameOver;
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