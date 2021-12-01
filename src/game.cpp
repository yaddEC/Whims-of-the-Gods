#include "game.hpp"

static bool pointSelected = false;
static bool jackActive = false;

Game::Game()
{
    map.Init();
    DefSpawn(map.Spawn.mPos);

    pauseSource = {map.texture[107].mPos.x, map.texture[107].mPos.y, SIZE, SIZE};

    jackhammer.model = LoadTexture("assets/jackhammer.png");

    classicTurret = {map.texture[250].mPos.x, map.texture[250].mPos.y, SIZE, SIZE};
    slowingTurret = {map.texture[249].mPos.x, map.texture[249].mPos.y, SIZE, SIZE};
    explosiveTurret = {map.texture[226].mPos.x, map.texture[226].mPos.y, SIZE, SIZE};

    warriorEnemy = {map.texture[247].mPos.x, map.texture[247].mPos.y, SIZE, SIZE};
    healerEnemy = {map.texture[246].mPos.x, map.texture[246].mPos.y, SIZE, SIZE};
    berserkerEnemy = {map.texture[245].mPos.x, map.texture[245].mPos.y, SIZE, SIZE};

    //menuScreen.model = LoadTexture("assets/menu_screen.png");
    //pauseScreen.model = LoadTexture("assets/pause_screen.png");
}

bool Button(int x, int y, float width, float height, const char *name, Color color)
{
    bool res = false;

    if (InRec(x, y, width, height))
    {
        DrawRectangle(x, y, width, height, ColorAlpha(LIGHTGRAY, 0.7));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {

            res = true;
            DrawRectangle(x, y, width, height, RED);
        }
    }
    else
        DrawRectangle(x, y, width, height, color);
    DrawText(name, x + 0.35 * width, y + 0.3 * height, GetFontDefault().baseSize * 3, RAYWHITE);
    DrawRectangleLines(x, y, width, height, DARKGRAY);

    return res;
}

void Game::Menu()
{
    if (Button(440, 200, 400, 100, "START", GRAY))
    {
        start = true;
    }
    if (Button(440, 400, 400, 100, "QUIT", GRAY))
    {
        quit = true;
    }
}

Tile::Tile()
{
    mWidthTile = SIZE;
}

void Tile::Init(int i, int mapWidth, char val)
{

    mTilePos = i;
    active = false;
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
    mHeight = 12;
    mWidth = 16;

    total = mHeight * mWidth;
    tile = new Tile[total];
    tilesheet = LoadTexture("assets/towerDefense_tilesheet.png");

    plan =
        {
            "IIIIOOOOOOOOOOOO"
            "OOOIOOOOOOOOOOOO"
            "OOOIOOOOOOOOOOOO"
            "OOOIOOOOOOOOOOOO"
            "OOOLIIIIIIIIIIOO"
            "OOOIOOOOOOOOOIOO"
            "OOOIOOOOOOOOOIOO"
            "OOO>IIIIIIIIIVOO"
            "OOOOOOOOOOOOOIOO"
            "OOOOOOOOOOOOOIOO"
            "OOOOOOOOOOOOOIOO"
            "OOOOOOOOOOOOOIII"};
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
    Spawn = tile[0];
    Despawn = tile[191];
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
        case 'L':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case 'T':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case 'A':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case 'V':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case '>':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case '<':
            tile[i].Draw(tilesheet, texture[50]);
            break;
        case '-':
            tile[i].Draw(tilesheet, texture[1]);
            break;
        case 'O':
            tile[i].Draw(tilesheet, texture[24]);
            break;
        }
    }
}

void Game::backUI()
{
    const Rectangle classicTurretIcon = (Rectangle){1110, 192, SIZE, SIZE};
    const Rectangle slowingTurretIcon = (Rectangle){1110, 320, SIZE, SIZE};
    const Rectangle explosiveTurretIcon = (Rectangle){1110, 448, SIZE, SIZE};
    const Rectangle jackHammerIcon = (Rectangle){1110, 64, SIZE, SIZE};
    const Rectangle pauseIcon = (Rectangle){1210, 5, SIZE, SIZE};

    Color priceColor = GOLD;
    Vector2 origin = {0, 0};

    //UpdateAndDrawUI Normal turret
    DrawRectangleLinesEx(classicTurretIcon, 2, RED);
    DrawTexturePro(map.tilesheet, classicTurret, classicTurretIcon, origin, 0, WHITE);

    if (money < 50)
    {
        priceColor = LIGHTGRAY;
    }
    DrawText("50", classicTurretIcon.x + 25, classicTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    Rectangle source = {map.texture[287].mPos.x, map.texture[287].mPos.y, SIZE, SIZE};
    Rectangle dest = {classicTurretIcon.x - 5, classicTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, priceColor);

    if (InRec(classicTurretIcon))
    {
        DrawText("Classic Turret", 1070, 600, 20, RED);
        DrawText("Damage: Medium", 1050, 650, 20, BLACK);
        DrawText("Attack Speed: Medium", 1050, 680, 20, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 50) // Buy and place new classic turret
        {
            pointSelected = true;
            turret.push_back(new ClassicTurret);
            turret.back()->sourceTexture = classicTurret;
            turret.back()->id = 1;
        }
    }

    //UpdateAndDrawUI Slow turret
    DrawRectangleLinesEx(slowingTurretIcon, 2, GREEN);
    DrawTexturePro(map.tilesheet, slowingTurret, slowingTurretIcon, origin, 0, WHITE);

    if (money < 150)
    {
        priceColor = LIGHTGRAY;
    }
    DrawText("150", slowingTurretIcon.x + 25, slowingTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    dest = {slowingTurretIcon.x - 5, slowingTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, priceColor);

    if (InRec(slowingTurretIcon))
    {
        DrawText("Slowing Turret", 1070, 600, 20, GREEN);
        DrawText("Damage: Low", 1050, 650, 20, BLACK);
        DrawText("Attack Speed: High", 1050, 680, 20, BLACK);
        DrawText("Special:  Slows", 1050, 705, 19, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 150) // Buy and place new slowing turret
        {
            pointSelected = true;
            turret.push_back(new SlowingTurret);
            turret.back()->sourceTexture = slowingTurret;
            turret.back()->id = 2;
        }
    }

    //UpdateAndDrawUI Explosive turret
    DrawRectangleLinesEx(explosiveTurretIcon, 2, ORANGE);
    DrawTexturePro(map.tilesheet, explosiveTurret, explosiveTurretIcon, origin, 0, WHITE);

    if (money < 300)
    {
        priceColor = LIGHTGRAY;
    }
    DrawText("300", explosiveTurretIcon.x + 25, explosiveTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    dest = {explosiveTurretIcon.x - 5, explosiveTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, priceColor);

    if (InRec(explosiveTurretIcon))
    {
        DrawText("Explosive Turret", 1060, 600, 20, ORANGE);
        DrawText("Damage: High", 1050, 650, 20, BLACK);
        DrawText("Attack Speed: Low", 1050, 680, 20, BLACK);
        DrawText("Special:  Area Damage", 1050, 705, 19, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 300) // Buy and place new explosive turret
        {
            pointSelected = true;
            turret.push_back(new ExplosiveTurret);
            turret.back()->sourceTexture = explosiveTurret;
            turret.back()->id = 3;
        }
    }

    //UpdateAndDrawUI jack hammer
    DrawRectangleLinesEx(jackHammerIcon, 2, SKYBLUE);

    if (!jackActive)
    {
        DrawTexture(jackhammer.model, jackHammerIcon.x + 6, jackHammerIcon.y + 10, WHITE);
    }

    if (InRec(jackHammerIcon))
    {
        DrawText("Sell Turret", 1080, 600, 20, SKYBLUE);
        DrawText("Recover half the", 1060, 650, 20, BLACK);
        DrawText("turret's price", 1070, 680, 20, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Buy and place new slowing turret
        {
            jackActive = !jackActive;
        }
    }

    else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON) && jackActive)
    {
        map.tile[GetTile(GetMousePosition())].active = false;
        int a = 0;
        for (Turret *t : turret)
        {

            if (GetTile(GetMousePosition()) == GetTile(t->pos))
            {
                money += t->price / 2;
                turret.erase(turret.begin() + a);
                break;
            }
            a++;
        }
        jackActive = !jackActive;
    }

    if (pointSelected)
    {
        if (GetMousePosition().x < 1024 && GetMousePosition().x > 0 && GetMousePosition().y < 768 && GetMousePosition().y > 0)
        {
            turret.back()->pos.x = map.tile[GetTile(GetMousePosition())].mPos.x + SIZE / 2;
            turret.back()->pos.y = map.tile[GetTile(GetMousePosition())].mPos.y + SIZE / 2;
        }
        else
        {
            turret.back()->pos = GetMousePosition();
        }

        if ((GetMousePosition().x >= 1024 || GetMousePosition().x <= 0 || GetMousePosition().y >= 768 || GetMousePosition().y <= 0) || map.tile[GetTile(GetMousePosition())].active == true || map.tile[GetTile(GetMousePosition())].value != 'O')
        {
            turret.back()->colorZone = RED;
            if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
            {
                turret.pop_back();
                pointSelected = false;
            }
        }
        else
        {
            turret.back()->colorZone = DARKBLUE;
            if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
            {
                money -= turret.back()->price;
                map.tile[GetTile(GetMousePosition())].active = true;
                turret.back()->active = true;
                pointSelected = false;
            }
        }
    }

    if (showTurretRange)
    {
        for (long unsigned int i = 0; i < turret.size(); i++)
        {
            DrawCircleV(turret[i]->pos, turret[i]->range, ColorAlpha(turret[i]->colorZone, 0.3)); // Draw turret range
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        showTurretRange = !showTurretRange;
    }

    DrawTexturePro(map.tilesheet, pauseSource, pauseIcon, origin, 0, WHITE);
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && InRec(pauseIcon))
    {
        pause = true;
    }
}

void Game::frontUI()
{
    if (jackActive)
    {
        DrawTexture(jackhammer.model, GetMousePosition().x - 48 / 2, GetMousePosition().y, WHITE);
    }

    DrawText(TextFormat("%i", money), 60, 730, GetFontDefault().baseSize * 3, GOLD);
    Rectangle source = {map.texture[287].mPos.x, map.texture[287].mPos.y, SIZE, SIZE};
    Rectangle dest = {10, 710, SIZE, SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, GOLD);
}

void Game::UpdateAndDraw()
{
    map.Draw();

    if (!pause)
    {
        backUI();

        if (turret.size() > 0 && !turret.back()->active)
        {
            DrawCircleV(turret.back()->pos, turret.back()->range, ColorAlpha(turret.back()->colorZone, 0.3)); // Draw turret range
        }
        for (Turret *t : turret)

        {
            if (turret.back()->active && InRec(t->pos.x - 32, t->pos.y - 32, SIZE, SIZE))
            {
                DrawCircleV(t->pos, t->range, ColorAlpha(t->colorZone, 0.3)); // Draw turret range
            }

            t->UpdateAndDraw(enemy, map.tilesheet, map.texture[t->id + 295].mPos);
        }

        for (long unsigned int t = 0; t < enemy.size(); t++)
        {
            enemy[t]->UpdateAndDraw(map, round, enemy);
            if (enemy[t]->hp <= 0)
            {
                enemy.erase(enemy.begin() + t);
                money += enemy[t]->reward;
            }
            else if (enemy[t]->posTile == map.Despawn.mTilePos)
            {
                enemy.erase(enemy.begin() + t);
            }
            
        }

        if (IsKeyPressed(KEY_SPACE)) // TEST enemy spawner
        {
            enemy.push_back(new Warrior);
            enemy.push_back(new Healer);
            enemy.push_back(new Berserker);
            round++;
        }

        frontUI();
    }
    else
    {
        if (Button(440, 200, 400, 100, "RESUME", GRAY))
        {
            pause = false;
        }
        if (Button(440, 400, 400, 100, "MENU", GRAY))
        {
            pause = false;
            start = false;
        }
    }
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;
    }
}

Game::~Game()
{
    for (Turret *t : turret)
        delete t;
    for (Enemy *e : enemy)
        delete e;
}
