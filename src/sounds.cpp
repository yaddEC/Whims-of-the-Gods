#include "sounds.hpp"

GameSounds::GameSounds()
{
    mainTheme = LoadSound("assets/mainTheme.mp3"); 

    secondTheme = LoadSound("assets/secondTheme.mp3"); 

    button = LoadSound("assets/buttonSound.wav"); 

    sellTurret = LoadSound("assets/sellSound.ogg"); 

    gameOver = LoadSound("assets/gameOverTheme.wav"); 
}
GameSounds::~GameSounds()
{
    UnloadSound(mainTheme);
    UnloadSound(secondTheme);
    UnloadSound(button);
    UnloadSound(sellTurret);
    UnloadSound(gameOver);
}


TurretSounds::TurretSounds()
{
    classic = LoadSound("assets/hit01.wav");
    SetSoundVolume(classic, 0.3); 

    slowing = LoadSound("assets/hit02.wav");
    SetSoundVolume(slowing, 0.1); 

    explosion = LoadSound("assets/hit03.wav");
    SetSoundVolume(explosion, 0.5); 
}
TurretSounds::~TurretSounds()
{
    UnloadSound(classic);
    UnloadSound(slowing);
    UnloadSound(explosion);
}

EnemySounds::EnemySounds()
{

}
EnemySounds::~EnemySounds()
{

}