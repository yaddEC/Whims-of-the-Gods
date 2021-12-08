#include "sounds.hpp"

GameSounds::GameSounds()
{
    mainTheme = LoadSound("assets/mainTheme.mp3"); 
    SetSoundVolume(mainTheme, 0.5);

    secondTheme = LoadSound("assets/secondTheme.mp3"); 
    SetSoundVolume(secondTheme, 0.5);

    button = LoadSound("assets/buttonSound.wav"); 
    SetSoundVolume(button, 0.5);

    sellTurret = LoadSound("assets/sellSound.ogg"); 
    SetSoundVolume(sellTurret, 0.5);

    gameOver = LoadSound("assets/gameOverTheme.wav"); 
    SetSoundVolume(gameOver, 0.5);
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