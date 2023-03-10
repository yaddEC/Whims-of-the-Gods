#include "tile.hpp"
#include "../resources.hpp"

Tile::Tile()
{
}

Tile::Tile(int i, int mapWidth, char val)
{
    mWidthTile = SIZE;
    tilePos = i;
    if (val == 'I' || val == 'L' || val == 'V' || val == '>' || val == '<' || val == 'A')
    {
        active = true;
        road = true;
    }
    else
    {
        active = false;
        road = false;
    }

    value = val;
    pos.x = (i % mapWidth) * mWidthTile;
    pos.y = (i / mapWidth) * mWidthTile;
}

void Tile::Draw(Vector2 frame)
{
    Rectangle source = {frame.x, frame.y, SIZE, SIZE};
    Rectangle dest{float((int)pos.x), float((int)pos.y), SIZE, SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, WHITE);

    
}

Tile::~Tile()
{
}

Tilemap::Tilemap()
{
    height = 12;
    width = 16;

    total = height * width;

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
        tile.back().environment = 9;
    }

    Spawn = tile[0];
    Despawn = tile[191];
    bool check = false;
    int random;
    srand(time(0));

    for (int i = 0; i < 16; i++)
    {

        while (!check)
        {

            random = rand() % 191;
            if (tile[random].road == false && tile[random].active == false)
            {
                tile[random].active = true;
                tile[random].environment = rand() % 8;
                check = true;
            }
        }
        check = false;
    }
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
        if (Spawn.tilePos == tile[i].tilePos)
        {

            id = 64;
            tile[i].road = true;
        }
        else if (Despawn.tilePos == tile[i].tilePos)
        {
            id = 63;
            tile[i].Draw(texture[50]);
            tile[i].road = true;
        }
        else

        {

            switch (tile[i].value)
            {
            case '_':
                id = 116;
                break;
            case '{':
                id = 115;
                break;
            case ']':
                id = 96;
                break;
            case '[':
                id = 95;
                break;
            case '}':
                id = 71;
                break;
            case '-':
                id = 70;
                break;
            case 'l':
                id = 94;
                break;
            case '|':
                id = 92;
                break;
            case ')':
                id = 73;
                break;
            case '(':
                id = 72;
                break;
            case 'I':
                id = 50;
                break;
            case 'A':
                id = 50;
                break;
            case 'V':
                id = 50;
                break;
            case '>':
                id = 50;
                break;
            case '<':
                id = 50;
                break;
            case 'O':
                id = 24;
                break;
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
                }
                break;
            }
        }

        tile[i].Draw(texture[id]);
        if (tile[i].environment != 9)
        {
            tile[i].Draw(texture[130 + tile[i].environment]);
        }
    }
}