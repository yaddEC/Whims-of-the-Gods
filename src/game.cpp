#include "game.hpp"

static bool pointSelected = false;

Game::Game()
{
    map.Init();
    classicTurret.model = LoadTexture("assets/classic_turret.png");
    slowingTurret.model = LoadTexture("assets/slowing_turret.png");
    explosiveTurret.model = LoadTexture("assets/explosive_turret.png");
}

bool Button(int x, int y, float width, float height, const char *name, Color color)
{
    bool res = false;

    if (InRec(x, y, width, height))
    {
        DrawRectangle(x, y, width, height, LIGHTGRAY);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            res = true;
            DrawRectangle(x, y, width, height, RED);
        }
    }
    else
        DrawRectangle(x, y, width, height, color);
    DrawText(name, x + 0.35 * width, y + 0.3 * height, GetFontDefault().baseSize * 2, RAYWHITE);
    DrawRectangleLines(x, y, width, height, DARKGRAY);

    return res;
}

Tile::Tile()
{
    mWidthTile = SIZE;
}

void Tile::Init(int i, int mapWidth, char val)
{

    mTilePos = i;
    value = val;
    mPos.x = (i % mapWidth) * mWidthTile;
    mPos.y = static_cast<int>(i / mapWidth) * mWidthTile;
}

void Tile::Draw(Texture2D tilesheet, Tile frame)
{

    Rectangle source = {frame.mPos.x, frame.mPos.y, SIZE, SIZE};
    Rectangle dest = {mPos.x, mPos.y, SIZE, SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(tilesheet, source, dest, origin, 0, WHITE);

    if (GetTile(GetMousePosition()) == mTilePos && GetMousePosition().x < 1024)
    {
        DrawRectangleLines(mPos.x, mPos.y, SIZE, SIZE, ColorAlpha(WHITE, 0.5));
    }
}

Tile::~Tile()
{
}

Tilemap::Tilemap()
{
    mHeight = 12;
    mWidth = 16;
    total = mHeight * mWidth;
    tile = new Tile[total];
    tilesheet = LoadTexture("assets/towerDefense_tilesheet.png");

    plan =
        {
            "-------T|OOOOOOO"
            "OOOOOOOl|OOOOOOO"
            "OOOOOOOl|OOOOOOO"
            "OOOOOOOl|OOOOOOO"
            "OOOOOOOl|OOOOOOO"
            "OO[____JL____]OO"
            "OOlb--------d|OO"
            "OOl|OOOOOOOOl|OO"
            "OOlL________J|OO"
            "OO{---------d|OO"
            "OOOOOOOOOOOOl|OO"
            "OOOOOOOOOOOOlL__"};
}

Tilemap::~Tilemap()
{

    delete[] tile;
}

void Tilemap::Init()
{
    for (int i = 0; i < total; i++)
    {
        tile[i].Init(i, mWidth, plan[i]);
    }

    for (int i = 0; i < 368; i++)
    {
        texture[i].Init(i, 23, 'a');
    }
}

void Tilemap::Draw()
{

    for (int i = 0; i < total; i++)
    {
        switch (tile[i].value)
        {
        case 'I':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case '-':
            tile[i].Draw(tilesheet, texture[1]);
            break;
        case 'T':
            tile[i].Draw(tilesheet, texture[2]);
            break;
        case 'l':
            tile[i].Draw(tilesheet, texture[25]);
            break;
        case '|':
            tile[i].Draw(tilesheet, texture[23]);
            break;
        case 'L':
            tile[i].Draw(tilesheet, texture[46]);
            break;
        case 'J':
            tile[i].Draw(tilesheet, texture[48]);
            break;
        case '_':
            tile[i].Draw(tilesheet, texture[47]);
            break;
        case 'O':
            tile[i].Draw(tilesheet, texture[24]);
            break;
        case '[':
            tile[i].Draw(tilesheet, texture[3]);
            break;
        case ']':
            tile[i].Draw(tilesheet, texture[4]);
            break;
        case '{':
            tile[i].Draw(tilesheet, texture[26]);
            break;
        case '}':
            tile[i].Draw(tilesheet, texture[27]);
            break;

        case 'd':
            tile[i].Draw(tilesheet, texture[2]);
            break;

        case 'b':
            tile[i].Draw(tilesheet, texture[0]);
            break;
        }
    }
}

void Game::UpdateAndDrawUI()
{
    const Rectangle classicTurretIcone = (Rectangle){1110, 64, SIZE, SIZE};
    const Rectangle slowingTurretIcone = (Rectangle){1110, 256, SIZE, SIZE};
    const Rectangle explosiveTurretIcone = (Rectangle){1110, 448, SIZE, SIZE};

    //UpdateAndDrawUI turret Normal
    DrawRectangleLinesEx(classicTurretIcone, 2, RED);
    DrawTexture(classicTurret.model, classicTurretIcone.x, classicTurretIcone.y, WHITE);
    //UpdateAndDrawUI turret Slow
    DrawRectangleLinesEx(slowingTurretIcone, 2, GREEN);
    DrawTexture(slowingTurret.model, slowingTurretIcone.x, slowingTurretIcone.y, WHITE);
    //UpdateAndDrawUI turret Explsive
    DrawRectangleLinesEx(explosiveTurretIcone, 2, ORANGE);
    DrawTexture(explosiveTurret.model, explosiveTurretIcone.x, explosiveTurretIcone.y, WHITE);

    if (InRec(classicTurretIcone))
    {
        DrawText("Classic Turret", 1070, 600, 20, RED);
        DrawText("Damage: Medium", 1050, 650, 20, BLACK);
        DrawText("Attack Speed: Medium", 1050, 680, 20, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Buy and place new classic turret
        {
            turret.push_back(new Turret);
            turret.back()->texture = classicTurret;
        }
    }

    if (InRec(slowingTurretIcone))
    {
        DrawText("Slowing Turret", 1070, 600, 20, GREEN);
        DrawText("Damage: Low", 1050, 650, 20, BLACK);
        DrawText("Attack Speed: High", 1050, 680, 20, BLACK);
        DrawText("Special:  Slows", 1050, 705, 19, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Buy and place new slowing turret
        {
            turret.push_back(new Turret);
            turret.back()->texture = slowingTurret;
        }
    }

    if (InRec(explosiveTurretIcone))
    {
        DrawText("Explosive Turret", 1060, 600, 20, ORANGE);
        DrawText("Damage: High", 1050, 650, 20, BLACK);
        DrawText("Attack Speed: Low", 1050, 680, 20, BLACK);
        DrawText("Special:  Area Damage", 1050, 705, 19, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Buy and place new explosive turret
        {
            turret.push_back(new Turret);
            turret.back()->texture = explosiveTurret;
        }
    }
    if ((pointSelected || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (InRec(classicTurretIcone) || InRec(slowingTurretIcone) || InRec(explosiveTurretIcone)))))
    {
        if (GetMousePosition().x < 1024)
        {
            turret.back()->pos.x = map.tile[GetTile(GetMousePosition())].mPos.x + SIZE / 2;
            turret.back()->pos.y = map.tile[GetTile(GetMousePosition())].mPos.y + SIZE / 2;
        }
        else
        {
              turret.back()->pos=GetMousePosition();
        }

        pointSelected = true;

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON) && GetMousePosition().x < 1024)
        {

            turret.back()->active = true;
            pointSelected = false;
        }
        else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON) && GetMousePosition().x >= 1024)
        {
            turret.pop_back();
            pointSelected = false;
        }
    }

    if (showTurretRange)
    {
        for (long unsigned int i = 0; i < turret.size(); i++)
        {
            DrawCircleV(turret[i]->pos, turret[i]->range, ColorAlpha(DARKBLUE, 0.3)); // Draw turret range
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        showTurretRange = !showTurretRange;
    }
}

void Game::UpdateAndDraw()
{
    map.Draw();
    UpdateAndDrawUI();
    for (Turret *t : turret)
    {
        t->UpdateAndDraw(enemy);
    }

    for (Enemy *t : enemy)
    {
        t->UpdateAndDraw();
    }

    if (IsKeyDown(KEY_SPACE)) // TEST enemy spawner
    {
        enemy.push_back(new Enemy);
    }
}

Game::~Game()
{
    for (Turret *t : turret)
        delete t;
    for (Enemy *e : enemy)
        delete e;
}

bool Timer(int &timer, int const second)
{

    timer++;
    if (timer == second * 60)
    {
        timer = 0;
        return true;
    }
    return false;
}