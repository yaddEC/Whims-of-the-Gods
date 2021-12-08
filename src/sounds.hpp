#include <raylib.h>

class GameSounds
{
public:
    Sound mainTheme;
    Sound secondTheme;
    Sound button;
    Sound sellTurret;
    Sound gameOver;
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