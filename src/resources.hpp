#pragma once
#include <raylib.h>
#include <mathematics.hpp>

struct Textures
{
    Texture2D tilesheet;
    Texture2D jackhammer;

    //menu background
    Texture2D five;
    Texture2D fourth;
    Texture2D third;
    Texture2D second;
    Texture2D first;
    Texture2D title;
};

struct Sounds
{
    Music mainTheme;
    Music secondTheme;
    Music gameOver;
    Music creditsTheme;
    Music kaboom;
    Sound button;
    Sound sellTurret;

    Sound classic;
    Sound slowing;
    Sound explosion;
};

class Resources
{
public:
    Textures textures;
    Sounds sounds;

    Resources();
    ~Resources();
};

extern Resources* gRes;
