#include "tile.hpp"

Tile::Tile()
{
}

Tile::Tile(int i, int mapWidth, char val)
{
    mWidthTile = SIZE;
    mTilePos = i;
    active = false;
    road = false;
    value = val;
    mPos.x = (i % mapWidth) * mWidthTile;
    mPos.y = (i / mapWidth) * mWidthTile;
}

void Tile::Draw(Texture2D tilesheet, Vector2 frame)
{
    Rectangle source = {frame.x, frame.y, SIZE, SIZE};
    Rectangle dest{float((int)mPos.x), float((int)mPos.y), SIZE, SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(tilesheet, source, dest, origin, 0, WHITE);

    if (GetTile(GetMousePosition()) == mTilePos && GetMousePosition().x < 1024 && GetMousePosition().x > 0 && GetMousePosition().y < 768 && GetMousePosition().y > 0)
    {
        DrawRectangleLines(mPos.x, mPos.y, SIZE, SIZE, ColorAlpha(WHITE, 0.5));
    }
}

Tile::~Tile()
{
}

Tilemap::Tilemap()
{
    height = 12;
    width = 16;

    total = height * width;
    tilesheet = LoadTexture("assets/towerDefense_tilesheet.png");

    plan =
        {
            "IIIIlOOOOOOOOOOO"
            "__)IlOOOOOOOOOOO"
            "OO|IlOOOOOOOOOOO"
            "OO|I[---------}O"
            "OO|L>IIIIIIIIIlO"
            "OO|V(_______)IlO"
            "OO|I[-------]IlO"
            "OO|>IIIIIIIIIVlO"
            "OO{_________)IlO"
            "OOOOOOOOOOOO|IlO"
            "OOOOOOOOOOOO|I[-"
            "OOOOOOOOOOOO|III"};
}

Tilemap::~Tilemap()
{

    tile.clear();
}

void Tilemap::Init()
{

    Tile temp;
    for (int i = 0; i < total; i++)
    {
        temp = Tile(i, width, plan[i]);
        tile.push_back(temp);
    }

    Spawn = tile[0];
    Despawn = tile[191];
    for (int i = 0; i < 299; i++)
    {
        texture[i].x = (i % 23) * 64;
        texture[i].y = (i / 23) * 64;
    }
}

void Tilemap::Draw(int round)
{
    int id = 0;
    for (int i = 0; i < total; i++)
    {
        if (Spawn.mTilePos == tile[i].mTilePos)
        {

            id = 64;
            tile[i].road = true;
        }
        else if (Despawn.mTilePos == tile[i].mTilePos)
        {
            id = 63;
            tile[i].Draw(tilesheet, texture[50]);
            tile[i].road = true;
        }
        else

        {

            
            switch (tile[i].value)
            {
            case '_': id = 116; break;
            case '{': id = 115; break;
            case ']': id =  96; break;
            case '[': id =  95; break;
            case '}': id = 71; break;
            case '-': id = 70; break;
            case 'l': id = 94; break;
            case '|': id = 92; break;
            case ')': id = 73; break;
            case '(': id = 72; break;
            case 'I': id = 50; tile[i].road = true;break;
            case 'A': id = 50; tile[i].road = true;break;
            case 'V': id = 50; tile[i].road = true;break;
            case '>': id = 50; tile[i].road = true;break;
            case '<': id = 50; tile[i].road = true;break;
            case 'O': id = 24; break;
            case 'L': 
            if (round > 20)
            {
            id = 62;
            }
            else if (round % 2 == 1 || round == 0)
            {
            id = 65;
            }
            else
            {
            id = 68;
            tile[i].road = true;
            }
            break;
            }
        
        
        }
        tile[i].Draw(tilesheet, texture[id]);
    }
}