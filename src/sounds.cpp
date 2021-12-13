#include "sounds.hpp"

GameSounds::GameSounds()
{
    mainTheme = LoadMusicStream("assets/mainTheme.mp3"); 
    secondTheme = LoadMusicStream("assets/secondTheme.mp3"); 
    gameOver = LoadMusicStream("assets/gameOverTheme.mp3"); 
    creditsTheme = LoadMusicStream("assets/creditsTheme.mp3"); 

    button = LoadSound("assets/buttonSound.wav"); 
    sellTurret = LoadSound("assets/sellSound.ogg"); 

}
GameSounds::~GameSounds()
{
    UnloadMusicStream(mainTheme);
    UnloadMusicStream(secondTheme);
    UnloadMusicStream(gameOver);
    UnloadMusicStream(creditsTheme);
    UnloadSound(button);
    UnloadSound(sellTurret);
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