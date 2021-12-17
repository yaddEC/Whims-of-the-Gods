#include "resources.hpp"

Resources* gRes = nullptr;

Resources::Resources()
{
    //TEXTURES
    textures.tilesheet = LoadTexture("assets/towerDefense_tilesheet.png");
    textures.jackhammer= LoadTexture("assets/jackhammer.png");
    textures.title = LoadTexture("assets/title.png");
    textures.five = LoadTexture("assets/5_plan.png");
    textures.fourth = LoadTexture("assets/4_plan.png");
    textures.third = LoadTexture("assets/3_plan.png");
    textures.second = LoadTexture("assets/2_plan.png");
    textures.first = LoadTexture("assets/1_plan.png");

    //MUSICS AND SOUNDS
    sounds.mainTheme = LoadMusicStream("assets/mainTheme.mp3"); 
    sounds.secondTheme = LoadMusicStream("assets/secondTheme.mp3"); 
    sounds.gameOver = LoadMusicStream("assets/gameOverTheme.mp3"); 
    sounds.creditsTheme = LoadMusicStream("assets/creditsTheme.mp3"); 
    sounds.kaboom = LoadMusicStream("assets/Kaboom.mp3"); 

    sounds.button = LoadSound("assets/buttonSound.wav"); 
    sounds.sellTurret = LoadSound("assets/sellSound.ogg"); 

    sounds.classic = LoadSound("assets/hit01.wav");
    SetSoundVolume(sounds.classic, 0.3); 

    sounds.slowing = LoadSound("assets/hit02.wav");
    SetSoundVolume(sounds.slowing, 0.1); 

    sounds.explosion = LoadSound("assets/hit03.wav");
    SetSoundVolume(sounds.explosion, 0.5); 
}

Resources::~Resources()
{
    UnloadMusicStream(sounds.mainTheme);
    UnloadMusicStream(sounds.secondTheme);
    UnloadMusicStream(sounds.gameOver);
    UnloadMusicStream(sounds.creditsTheme);
    UnloadMusicStream(sounds.kaboom);
    UnloadSound(sounds.button);
    UnloadSound(sounds.sellTurret);

    UnloadSound(sounds.classic);
    UnloadSound(sounds.slowing);
    UnloadSound(sounds.explosion);
}
