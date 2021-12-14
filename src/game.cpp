#include "game.hpp"
#include <iostream>
#include <fstream>

#define FPS 60

static bool pointSelected = false;
static bool jackActive = false;
static float opacityZone = 0.4;
static int spawnTimer = 600;
static int frameCounter = 60;
static int animationTimer = 300;
static int secondTimer = 0;
static bool parTimer = false;
static int maxEnemies = 10;

static int moneyTimer = 0;
static int moneyGain = 0;

Game::Game()
{
    credit = false;
    creditHeight = 780;
    creditTitle = {"Special Thanks",
                   "Caprice des dieux inc",
                   "Writers",
                   "Narrative Consultants",
                   "Performance Capture & Voice Over Director ",
                   "Stunt Coordinators",
                   "Casting",
                   "Cinematography &Visual ",
                   "Historian",
                   "Military Advisors",
                   "Motion Capture Personnel",
                   "Audio Location Recording",
                   "Executive Team",
                   "Planning Team",
                   "Consumer marketing",
                   "Corporate communication",
                   "Franchise Editorial",
                   "Finance",
                   "Global Analytics - Machine Learning",
                   "Global Digital and Americas Commercial",
                   "Global Experiential Marketing",
                   "GIS",
                   "Global IT",
                   "Global Media",
                   "Global Partnership",
                   "Human Ressources",
                   "Labs",
                   "Revenue Team",
                   "Legal Team - USA",
                   "Legal Team - EU",
                   "Legal Team - EMEA",
                   "Legal Team - ASIA PACIFIC",
                   "LIVE OPS ANALYTICS",
                   "Marketing Creative",
                   "Market insight /Competitive intelligence",
                   "Player Insights",
                   "Product Management",
                   "Product Marketing",
                   "Live Services",
                   "Production Management Group",
                   "Public Relations",
                   "Publishing Operations",
                   "Talent Acauisition",
                   "Quality Assurance",
                   "Technical Requirement Group",
                   "Technology"};
    titleID = 0;

    quit = false;
    start = false;
    pause = false;
    gameOver = false;
    music = true;
    soundEffect = true;
    highScoreBeated = false;
    hp = 20;
    maxHp = 20;
    money = 1000;
    round = 0;
    timer = 0;
    timerFadeScreen = FPS;
    showTurretRange = false;
    title = LoadTexture("assets/title.png");
    five = LoadTexture("assets/5_plan.png");
    fourth = LoadTexture("assets/4_plan.png");
    third = LoadTexture("assets/3_plan.png");
    second = LoadTexture("assets/2_plan.png");
    first = LoadTexture("assets/1_plan.png");
    scrollingFive = 0.0f;
    scrollingFourth = 0.0f;
    scrollingThird = 0.0f;
    scrollingSecond = 0.0f;
    scrollingFirst = 0.0f;

    map.Init();
    DefSpawn(map.Spawn.mPos);

    pauseSource = {map.texture[107].x, map.texture[107].y, SIZE, SIZE};

    jackhammer.model = LoadTexture("assets/jackhammer.png");

    classicTurret = {map.texture[250].x, map.texture[250].y, SIZE, SIZE};
    slowingTurret = {map.texture[249].x, map.texture[249].y, SIZE, SIZE};
    explosiveTurret = {map.texture[226].x, map.texture[226].y, SIZE, SIZE};

    warriorEnemy = {map.texture[247].x, map.texture[247].y, SIZE, SIZE};
    healerEnemy = {map.texture[245].x, map.texture[245].y, SIZE, SIZE};
    berserkerEnemy = {map.texture[246].x, map.texture[246].y, SIZE, SIZE};
}

bool Game::Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color)
{
    bool res = false;

    DrawRectangle(x, y, width, height, color);

    if (InRec(x, y, width, height))
    {
        DrawRectangle(x, y, width, height, ColorAlpha(WHITE, 0.5));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (soundEffect)
            {
                PlaySound(gameSounds.button);
            }
            res = true;
            DrawRectangle(x, y, width, height, RED);
        }
    }

    DrawText(name, x + nameSpacing * width, y + 0.25 * height, GetFontDefault().baseSize * nameSize, RAYWHITE);
    DrawRectangleLines(x, y, width, height, DARKGRAY);

    return res;
}

void DynamicTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint)
{
    if (parTimer)
    {
        DrawTexturePro(texture, source, {dest.x + (frameCounter - 30) / 4, dest.y + (frameCounter - 30) / 4, dest.width + 30 - frameCounter / 2, dest.height + 30 - frameCounter / 2}, origin, rotation, tint);
    }
    else
    {
        DrawTexturePro(texture, source, {dest.x - (frameCounter - 30) / 4, dest.y - (frameCounter - 30) / 4, dest.width + (frameCounter / 2), dest.height + frameCounter / 2}, origin, rotation, tint);
    }
}

bool Game::DynamicButton(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color)
{

    if (parTimer)
    {
        return Button(x + (frameCounter - 30) / 4, y + (frameCounter - 30) / 4, width + 30 - frameCounter / 2, height + 30 - frameCounter / 2, name, nameSpacing - 0.05 + (frameCounter / 2 * 0.001666), nameSize + 1.2 - (frameCounter / 2 * 0.04), color);
    }
    else
    {
        return Button(x - (frameCounter - 30) / 4, y - (frameCounter - 30) / 4, width + (frameCounter / 2), height + frameCounter / 2, name, nameSpacing - (frameCounter / 2 * 0.001666), nameSize + (frameCounter / 2 * 0.04), color);
    }
}
void Game::SoundButton(Rectangle dest, bool &type)
{

    if (InRec(dest))
    {
        DrawRectangleRec(dest, ColorAlpha(LIGHTGRAY, 0.5f));
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            type = !type;
            if (soundEffect)
            {
                PlaySound(gameSounds.button);
            }
        }
    }
    else
    {
        DrawRectangleRec(dest, ColorAlpha(DARKGRAY, 0.5f));
    }
    Rectangle source;
    if (type)
    {
        source = {map.texture[286].x, map.texture[286].y, SIZE, SIZE};
        DrawRectangleLinesEx(dest, 1.0f, GREEN);
    }
    else
    {
        source = {map.texture[285].x, map.texture[285].y, SIZE, SIZE};
        DrawRectangleLinesEx(dest, 1.0f, RED);
    }
    DrawTexturePro(map.tilesheet, source, dest, {0, 0}, 0, WHITE);
}

void Game::EnemyDestroyedAnimation(Enemy *&e)
{

    Rectangle source;
    if (e->damage == 5)
    {
        source = {map.texture[269].x, map.texture[269].y, SIZE, SIZE};
        if (e->timer > 60 || e->timer % 3 == 0)
        {
            DrawTexturePro(map.tilesheet, source, {e->pos.x - 32, e->pos.y - 32, 64, 64}, {0, 0}, 0, WHITE);
        }
    }
    else if (e->damage == 2)
    {

        source = {map.texture[270].x, map.texture[270].y, SIZE, SIZE};
        if (e->timer > 60 || e->timer % 3 == 0)
        {
            DrawTexturePro(map.tilesheet, source, {e->pos.x - 32, e->pos.y - 32, 64, 64}, {0, 0}, 0, WHITE);
        }
    }
    else
    {
        source = {map.texture[268].x, map.texture[268].y, SIZE, SIZE};
        if (e->timer > 60 || e->timer % 3 == 0)
        {
            DrawTexturePro(map.tilesheet, source, {e->pos.x - 32, e->pos.y - 32, 64, 64}, {0, 0}, 0, WHITE);
        }
    }
}

void Game::DrawTextWave()
{
    if (timer > 480)
    {
        DrawText(TextFormat("WAVE %i", round), 370, 350, 80, WHITE);
    }
    else
    {
        DrawText(TextFormat("WAVE %i", round), 370, 350, 80, ColorAlpha(WHITE, (timer - FPS * 2) / (float)FPS));
    }
}

void Game::Menu()
{

    FrameTimer(frameCounter);
    if (frameCounter == 0)
    {
        frameCounter = 60;
        secondTimer++;
    }
    if (secondTimer % 2)
    {
        parTimer = true;
    }
    else
        parTimer = false;

    scrollingFive -= 0.1f;
    scrollingThird -= 0.5f;
    scrollingSecond -= 0.8f;
    scrollingFirst -= 1.2f;

    if (scrollingFive <= -five.width * 2)
    {
        scrollingFive = 0;
    }
    if (scrollingThird <= -third.width * 2)
    {
        scrollingThird = 0;
    }
    if (scrollingSecond <= -second.width * 2)
    {
        scrollingSecond = 0;
    }
    if (scrollingFirst <= -first.width * 2)
    {
        scrollingFirst = 0;
    }

    DrawTextureEx(five, (Vector2){scrollingFive, 20}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(five, (Vector2){five.width * 2 + scrollingFive, 20}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(fourth, (Vector2){1066, 369}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(third, (Vector2){scrollingThird, 429}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(third, (Vector2){third.width * 2 + scrollingThird, 429}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(second, (Vector2){scrollingSecond, 429}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(second, (Vector2){second.width * 2 + scrollingSecond, 429}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(first, (Vector2){scrollingFirst, 339}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(first, (Vector2){first.width * 2 + scrollingFirst, 339}, 0.0f, 2.0f, WHITE);
    DynamicTexturePro(title, {0, 0, (float)title.width, (float)title.height}, {320, 124, (float)title.width, (float)title.height}, {0, 0}, 0, WHITE);

    if (Button(545, 535, 200, 50, "START", 0.22f, 3, GRAY))
    {
        StopMusicStream(gameSounds.mainTheme);
        start = true;
    }
    if (Button(545, 590, 200, 50, "QUIT", 0.32f, 3, GRAY))
    {
        quit = true;
    }
    if (Button(1050, 700, 150, 35, "CREDITS", 0.2f, 2, GRAY))
    {
        StopMusicStream(gameSounds.mainTheme);
        credit = true;
    }

    std::ifstream readScore("HighScore.txt");
    if (readScore)
    {
        int oldSocre;
        readScore >> oldSocre;
        DrawText(TextFormat("High Score: wave %i", oldSocre), 1050, 300, 20, WHITE);
    }

    SoundButton({520, 700, 48, 48}, music);
    SoundButton({720, 700, 48, 48}, soundEffect);

    DrawText("Music", 517, 670, 20, WHITE);
    DrawText("Sound", 715, 670, 20, WHITE);
}

void Game::Credit()
{
    if (titleID > 45)
    {
        titleID = 0;
    }
    if (titleID != 0)
    {
        DrawText(TextFormat("%s", creditTitle[titleID]), 500, creditHeight, 30, BLACK);
        for (int i = 0; i < 50; i += 2)
        {
            int height = creditHeight + 50 + (20 * i);
            DrawText("DECHAUX Yann", 550, height, 20, BLACK);
            DrawText("HENO Matias", 550, height + 20, 20, BLACK);
        }
        DrawText("KOJIMA Hideo", 550, creditHeight + 1050, 20, BLACK);

        creditHeight -= 5;
        if (creditHeight < -1100)
        {
            titleID++;
            creditHeight = 780;
        }
    }
    else
    {
        DrawText(TextFormat("%s", creditTitle[titleID]), 500, creditHeight, 30, BLACK);
        int height = creditHeight + 50;
        DrawText("GALINDO Paul", 550, height, 20, BLACK);
        DrawText("RAMPIN Stephane", 550, height + 20, 20, BLACK);
        DrawText("LECAYE Henri", 550, height + 40, 20, BLACK);
        DrawText("KFOURY Dimitry", 550, height + 60, 20, BLACK);
        DrawText("SANTAMARIA Ramon", 550, height + 80, 20, BLACK);
        DrawText("Every MGP2", 550, height + 100, 20, BLACK);
        DrawText("Musics", 600, height + 300, 30, BLACK);
        DrawText("Menu:  Tower defense style music loop by DST", 400, height + 350, 20, BLACK);
        DrawText("Game:  Return of Tower Defense Theme by DST", 400, height + 390, 20, BLACK);
        DrawText("Credits:  \"Blueberries\" composed, performed, mixed and mastered by Viktor Kraus", 260, height + 430, 20, BLACK);
        creditHeight -= 2;
        if (creditHeight < -500)
        {
            titleID++;
            creditHeight = 780;
        }
    }

    if (Button(1050, 700, 150, 35, "MENU", 0.3f, 2, GRAY))
    {
        timerFadeScreen--;
    }
    else if (timerFadeScreen < FPS && timerFadeScreen > 0)
    {
        if (music)
        {
            SetMusicVolume(gameSounds.creditsTheme, 0.5 - (0.5 - (timerFadeScreen * 0.5 / (float)(FPS))));
        }
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timerFadeScreen / (float)(FPS))));
        FrameTimer(timerFadeScreen);
    }
    else if (timerFadeScreen <= 0)
    {
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timerFadeScreen / (float)(FPS))));
        titleID = 0;
        creditHeight = 768;
        timerFadeScreen = FPS;
        StopMusicStream(gameSounds.creditsTheme);
        credit = false;
    }
}

void Game::backUI()
{
    const Rectangle classicTurretIcon = (Rectangle){1110, 152, SIZE, SIZE};
    const Rectangle slowingTurretIcon = (Rectangle){1110, 280, SIZE, SIZE};
    const Rectangle explosiveTurretIcon = (Rectangle){1110, 408, SIZE, SIZE};
    const Rectangle jackHammerIcon = (Rectangle){1110, 24, SIZE, SIZE};
    const Rectangle pauseIcon = (Rectangle){1210, 5, SIZE, SIZE};

    Color classicColor = RED;
    Color slowingColor = GREEN;
    Color explosiveColor = ORANGE;

    Color priceColor = GOLD;

    Color textureColor = WHITE;
    Vector2 origin = {0, 0};

    //UpdateAndDrawUI Normal turret
    if (money < 50)
    {
        priceColor = classicColor = textureColor = LIGHTGRAY;
    }

    DrawRectangleLinesEx(classicTurretIcon, 2, classicColor);
    DrawTexturePro(map.tilesheet, classicTurret, classicTurretIcon, origin, 0, textureColor);

    DrawText("50", classicTurretIcon.x + 25, classicTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    Rectangle source = {map.texture[287].x, map.texture[287].y, SIZE, SIZE};
    Rectangle dest = {classicTurretIcon.x - 5, classicTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, priceColor);

    if (InRec(classicTurretIcon))
    {
        DrawText("Classic Turret", 1070, 550, 20, RED);
        DrawText("Damage: Medium", 1050, 600, 20, BLACK);
        DrawText("Attack Speed: Medium", 1050, 630, 20, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 50) // Buy and place new classic turret
        {
            pointSelected = true;
            turret.push_back(new ClassicTurret);
            turret.back()->sourceTexture = classicTurret;
        }
    }

    //UpdateAndDrawUI Slow turret
    if (money < 150 || round < 3)
    {
        priceColor = slowingColor = textureColor = LIGHTGRAY;
    }

    DrawRectangleLinesEx(slowingTurretIcon, 2, slowingColor);
    DrawTexturePro(map.tilesheet, slowingTurret, slowingTurretIcon, origin, 0, textureColor);

    DrawText("150", slowingTurretIcon.x + 25, slowingTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    dest = {slowingTurretIcon.x - 5, slowingTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, priceColor);

    if (round < 3)
    {
        DrawTexturePro(map.tilesheet, {map.texture[284].x, map.texture[284].y, SIZE, SIZE}, slowingTurretIcon, origin, 0, WHITE);
    }
    if (InRec(slowingTurretIcon))
    {
        if (round < 3)
        {
            DrawText("Unlockable at", 1045, 600, 20, BLACK);
            DrawText("wave 3", 1190, 600, 20, GOLD);
        }
        else
        {
            DrawText("Slowing Turret", 1070, 550, 20, GREEN);
            DrawText("Damage: Low", 1050, 600, 20, BLACK);
            DrawText("Attack Speed: High", 1050, 630, 20, BLACK);
            DrawText("Special:  Slows", 1050, 655, 19, BLACK);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 150) // Buy and place new slowing turret
            {
                pointSelected = true;
                turret.push_back(new SlowingTurret);
                turret.back()->sourceTexture = slowingTurret;
            }
        }
    }

    //UpdateAndDrawUI Explosive turret
    if (money < 300 || round < 5)
    {
        priceColor = explosiveColor = textureColor = LIGHTGRAY;
    }

    DrawRectangleLinesEx(explosiveTurretIcon, 2, explosiveColor);
    DrawTexturePro(map.tilesheet, explosiveTurret, explosiveTurretIcon, origin, 0, textureColor);

    DrawText("300", explosiveTurretIcon.x + 25, explosiveTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    dest = {explosiveTurretIcon.x - 5, explosiveTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, priceColor);

    if (round < 5)
    {
        DrawTexturePro(map.tilesheet, {map.texture[284].x, map.texture[284].y, SIZE, SIZE}, explosiveTurretIcon, origin, 0, WHITE);
    }
    if (InRec(explosiveTurretIcon))
    {
        if (round < 5)
        {
            DrawText("Unlockable at", 1045, 600, 20, BLACK);
            DrawText("wave 5", 1190, 600, 20, GOLD);
        }
        else
        {
            DrawText("Explosive Turret", 1060, 550, 20, ORANGE);
            DrawText("Damage: High", 1050, 600, 20, BLACK);
            DrawText("Attack Speed: Low", 1050, 630, 20, BLACK);
            DrawText("Special:  Area Damage", 1050, 655, 19, BLACK);

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 300) // Buy and place new explosive turret
            {
                pointSelected = true;
                turret.push_back(new ExplosiveTurret);
                turret.back()->sourceTexture = explosiveTurret;
            }
        }
    }

    //UpdateAndDrawUI jack hammer
    DrawRectangleLinesEx(jackHammerIcon, 2, SKYBLUE);

    if (!jackActive)
    {
        DrawTexture(jackhammer.model, jackHammerIcon.x + 6, jackHammerIcon.y + 10, WHITE);
    }

    if (GetMousePosition().x < 1024 && GetMousePosition().x > 0 && GetMousePosition().y < 768 && GetMousePosition().y > 0)
    {
        DrawRectangleLines(map.tile[GetTile(GetMousePosition())].mPos.x, map.tile[GetTile(GetMousePosition())].mPos.y, SIZE, SIZE, ColorAlpha(WHITE, opacityZone));
    }

    if (InRec(jackHammerIcon))
    {
        DrawText("Sell Turret", 1090, 550, 20, SKYBLUE);
        DrawText("Recover half the", 1070, 580, 19, BLACK);
        DrawText("turret's price", 1080, 600, 19, BLACK);

        DrawText("Destroy Things", 1070, 630, 20, SKYBLUE);
        DrawText("Gain some money", 1077, 660, 19, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Buy and place new slowing turret
        {
            jackActive = !jackActive;
        }
    }

    else if (IsMouseButtonUp(MOUSE_LEFT_BUTTON) && jackActive)
    {
        map.tile[GetTile(GetMousePosition())].active = false;
        if (map.tile[GetTile(GetMousePosition())].environment != 9)
        {
            if (soundEffect)
            {
                PlaySound(gameSounds.sellTurret);
            }
            map.tile[GetTile(GetMousePosition())].environment = 9;
            moneyTimer = FPS * 2;
            moneyGain = rand() % 15;
            money += moneyGain;
        }
        else
        {
            int a = 0;
            for (Turret *t : turret)
            {

                if (GetTile(GetMousePosition()) == GetTile(t->pos))
                {
                    if (soundEffect)
                    {
                        PlaySound(gameSounds.sellTurret);
                    }
                    moneyTimer = FPS * 2;
                    moneyGain = t->price / 2;
                    money += moneyGain;
                    delete t;
                    turret.erase(turret.begin() + a);
                    break;
                }
                a++;
            }
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

        if ((GetMousePosition().x >= 1024 || GetMousePosition().x <= 0 || GetMousePosition().y >= 768 || GetMousePosition().y <= 0) || map.tile[GetTile(GetMousePosition())].active == true || map.tile[GetTile(GetMousePosition())].road != false)
        {
            turret.back()->colorZone = RED;
            if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
            {
                delete turret.back();
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
            DrawCircleV(turret[i]->pos, turret[i]->range, ColorAlpha(turret[i]->colorZone, opacityZone)); // Draw turret range
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        showTurretRange = !showTurretRange;
    }

    DrawTexturePro(map.tilesheet, pauseSource, pauseIcon, origin, 0, WHITE);
    if (InRec(pauseIcon))
    {
        DrawRectangleLinesEx(pauseIcon, 1, ColorAlpha(WHITE, opacityZone));

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Pause the game
        {
            if (soundEffect)
            {
                PlaySound(gameSounds.button);
            }
            pause = true;
        }
    }
}

void Game::frontUI()
{
    if (jackActive)
    {
        DrawTexture(jackhammer.model, GetMousePosition().x - 48 / 2, GetMousePosition().y, WHITE);
    }

    DrawText(TextFormat("%i", money), 60, 730, GetFontDefault().baseSize * 3, GOLD); // Money UI
    Rectangle source = {map.texture[287].x, map.texture[287].y, SIZE, SIZE};
    Rectangle dest = {10, 710, SIZE, SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(map.tilesheet, source, dest, origin, 0, GOLD);

    if (moneyTimer > 0)
    {
        DrawText(TextFormat("+%i", moneyGain), 42, 700, GetFontDefault().baseSize * 3, ColorAlpha(GOLD, moneyTimer / (float)(FPS / 2))); // Money gain indicator
    }

    // Health bar
    DrawRectangle(1040, 720, 225, 30, DARKBROWN);

    DrawRectangle(1040, 720, hp * 225 / maxHp, 30, ColorAlpha(GREEN, hp / (float)maxHp));
    DrawRectangle(1040, 720, hp * 225 / maxHp, 30, ColorAlpha(YELLOW, (1.0f - 2 * std::abs(0.5f - (hp / (float)maxHp)))));
    DrawRectangle(1040, 720, hp * 225 / maxHp, 30, ColorAlpha(RED, 1.0f - (hp / (float)maxHp)));

    DrawRectangleLines(1040, 720, 225, 30, WHITE);
    DrawText(TextFormat("%i / %i", hp, maxHp), 1050, 727, GetFontDefault().baseSize * 2, WHITE);

    if (timer == 0 && enemy.size() == 0 && DynamicButton(400, 685, 224, 50, "Ready", 0.3f, 3, GREEN))
    {
        round++;
        timer = spawnTimer;
        if (round > 5)
        {
            maxEnemies += 2;
        }
    }
}

void Game::UpdateAndDraw()
{
    FrameTimer(frameCounter);
    if (frameCounter == 0)
    {
        frameCounter = 60;
        secondTimer++;
    }
    if (secondTimer % 2)
        parTimer = true;
    else
        parTimer = false;
   
     if (!gameOver)
    {
         map.Draw(round);

        if (!pause)
        {
            backUI();

            if (turret.size() > 0 && !turret.back()->active)
            {
                DrawCircleV(turret.back()->pos, turret.back()->range, ColorAlpha(turret.back()->colorZone, opacityZone)); // Draw turret range
            }
            for (Turret *t : turret)

            {
                t->UpdateAndDraw(enemy, map.tilesheet, map.texture[t->id + 295], turretSounds, soundEffect);

                if (t->showTurretUpgrade) // Draw upgrade button
                {
                    Color buttonColor = GREEN;
                    if (t->updatePrice > t->price * 2) // Max Level Button
                    {
                        DrawRectangle(t->pos.x - 70, t->pos.y - 20, 140, 30, GRAY);
                        DrawText("MAX LEVEL", t->pos.x - 60, t->pos.y - 13, GetFontDefault().baseSize * 2, WHITE);
                    }
                    else
                    {
                        if (t->updatePrice > money) // Not enough money Button
                        {
                            DrawRectangle(t->pos.x - 70, t->pos.y - 20, 140, 30, GRAY);
                            DrawText("Upgrade", t->pos.x - 63, t->pos.y - 13, GetFontDefault().baseSize * 1.7, WHITE);
                        }
                        else if (Button(t->pos.x - 70, t->pos.y - 20, 140, 30, "Upgrade", 0.05, 1.7, buttonColor)) // enough money Button
                        {
                            money -= t->updatePrice;
                            t->range += 20;
                            t->updatePrice *= 2;
                        }
                        DrawText(TextFormat("%i", t->updatePrice), t->pos.x + 30, t->pos.y - 14, GetFontDefault().baseSize * 2, GOLD);
                        Rectangle source = {map.texture[287].x, map.texture[287].y, SIZE, SIZE};
                        Rectangle dest = {t->pos.x, t->pos.y - 22, SIZE / 2, SIZE / 2};
                        Vector2 origin = {0, 0};
                        DrawTexturePro(map.tilesheet, source, dest, origin, 0, GOLD);
                    }
                }

                if (turret.back()->active && InRec(t->pos.x - 32, t->pos.y - 32, SIZE, SIZE))
                {
                    DrawCircleLines(t->pos.x, t->pos.y, t->range, t->colorZone);                                            // Draw turret range
                    if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && t->showTurretUpgrade == false) || t->showTurretUpgrade) //Turn true showTurretRange
                    {
                        t->showTurretUpgrade = true;
                    }
                }
                else
                {
                    t->showTurretUpgrade = false;
                }
            }

            for (long unsigned int t = 0; t < enemy.size(); t++) // DESTROY ENEMY CONDITIONS
            {
                if (enemy[t]->posTile == map.Despawn.mTilePos)
                {
                    hp -= enemy[t]->damage;
                    Enemy *tmp = enemy[t];
                    enemy.erase(enemy.begin() + t);
                    delete tmp;
                    t--;
                }
                else if (enemy[t]->active)
                {
                    enemy[t]->UpdateAndDraw(map, round, enemy);
                    if (enemy[t]->hp <= 0)
                    {
                        moneyTimer = FPS * 2;
                        moneyGain = enemy[t]->reward;
                        money += moneyGain;
                        enemy[t]->timer = FPS * 2;
                        enemy[t]->active = false;
                    }
                }
                else if (enemy[t]->timer > 0)
                {
                    EnemyDestroyedAnimation(enemy[t]);
                    FrameTimer(enemy[t]->timer);
                }
                else
                {
                    Enemy *tmp = enemy[t];
                    enemy.erase(enemy.begin() + t);
                    delete tmp;
                    t--;
                }
            }

            if (timer > spawnTimer - (FPS * 3))
            {
                DrawTextWave();
            }

            if (timer != 0 && round != 0) // WAVES
            {
                if (round == 1 && timer % (2 * FPS) == 0) // TEST WAVE 1
                {
                    enemy.push_back(new Warrior);
                    enemy.back()->sourceTexture = warriorEnemy;
                }

                else if (round == 2 && timer % FPS == 0) // TEST WAVE 2
                {
                    enemy.push_back(new Warrior);
                    enemy.back()->sourceTexture = warriorEnemy;
                }

                else if (round == 3 && timer % FPS == 0) // TEST WAVE 3
                {
                    if (timer >= spawnTimer - (2 * FPS))
                    {
                        enemy.push_back(new Berserker);
                        enemy.back()->sourceTexture = berserkerEnemy;
                    }
                    else if (timer % (2 * FPS) == 0)
                    {
                        enemy.push_back(new Warrior);
                        enemy.back()->sourceTexture = warriorEnemy;
                    }
                }

                else if (round == 4 && timer % 60 == 0) // TEST WAVE 4
                {
                    if (timer > spawnTimer - (5 * FPS))
                    {
                        enemy.push_back(new Berserker);
                        enemy.back()->sourceTexture = berserkerEnemy;
                    }
                    else if (timer % (2 * FPS) == 0)
                    {
                        enemy.push_back(new Warrior);
                        enemy.back()->sourceTexture = warriorEnemy;
                    }
                }

                else if (round == 5 && timer % FPS == 0) // TEST WAVE 5
                {
                    if (timer >= spawnTimer - (2 * FPS))
                    {
                        enemy.push_back(new Berserker);
                        enemy.back()->sourceTexture = berserkerEnemy;
                    }
                    else if (timer > FPS)
                    {
                        enemy.push_back(new Warrior);
                        enemy.back()->sourceTexture = warriorEnemy;
                    }
                    else
                    {
                        enemy.push_back(new Healer);
                        enemy.back()->sourceTexture = healerEnemy;
                    }
                }
                else if (round > 5 && timer % (spawnTimer / maxEnemies) == 0)
                {

                    int random = rand() % 10;

                    if (random < 3)
                    {
                        enemy.push_back(new Berserker);
                        enemy.back()->sourceTexture = berserkerEnemy;
                    }

                    else if (random < 5)
                    {
                        enemy.push_back(new Healer);
                        enemy.back()->sourceTexture = healerEnemy;
                    }

                    else
                    {
                        enemy.push_back(new Warrior);
                        enemy.back()->sourceTexture = warriorEnemy;
                    }
                }
            }

            if (IsKeyPressed(KEY_SPACE)) // TEST enemy spawner
            {
                enemy.push_back(new Warrior);
                enemy.back()->sourceTexture = warriorEnemy;
                enemy.push_back(new Healer);
                enemy.back()->sourceTexture = healerEnemy;
                enemy.push_back(new Berserker);
                enemy.back()->sourceTexture = berserkerEnemy;
                round++;
            }

            FrameTimer(timer);
            FrameTimer(moneyTimer);

            frontUI();
            if (hp == 0)
            {
                FrameTimer(animationTimer);
            }
            if (hp <= 0 && animationTimer >= 60)
            {
                pointSelected = false;
                opacityZone = 0;
                map.Despawn.mTilePos = 1000;
                if (animationTimer == 300)
                {
                    Despawn.environment = 1;
                }

                if (animationTimer > 240)
                {

                    Rectangle source = {map.texture[63].x, map.texture[63].y, SIZE, SIZE};
                    Vector2 origin = {0, 0};
                    if (animationTimer % 4 == 0)
                    {
                        map.Despawn.environment = -1 * map.Despawn.environment;
                    }

                    Rectangle dest{float((int)map.Despawn.mPos.x), map.Despawn.mPos.y + map.Despawn.environment, SIZE, SIZE};
                    DrawTexturePro(map.tilesheet, source, dest, origin, 0, WHITE);
                }
                else if (animationTimer < 240)
                {
                    Rectangle dest{float((int)map.Despawn.mPos.x), float((int)map.Despawn.mPos.y), SIZE, SIZE};
                    Vector2 origin = {0, 0};
                    Rectangle source = {map.texture[86].x, map.texture[86].y, SIZE, SIZE};

                    DrawTexturePro(map.tilesheet, source, dest, origin, 0, WHITE);
                    DrawCircle(map.Despawn.mPos.x + 32, map.Despawn.mPos.y + 32, 50.0f, ColorAlpha(RED, 0.25f / 30.f * ((animationTimer / 4) - 30.0f)));
                    DrawCircle(map.Despawn.mPos.x + 32, map.Despawn.mPos.y + 32, 20.0f, ColorAlpha(ORANGE, 0.3f / 30.f * ((animationTimer / 4) - 30.0f)));
                    float radius = (60 - (animationTimer / 4)) * 2;

                    DrawCircle(map.Despawn.mPos.x + 32, map.Despawn.mPos.y + 32 + radius, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32, map.Despawn.mPos.y + 32 - radius, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32 + radius, map.Despawn.mPos.y + 32, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32 - radius, map.Despawn.mPos.y + 32, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32 + cos(45 * DEG2RAD) * radius, map.Despawn.mPos.y + 32 + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32 - cos(45 * DEG2RAD) * radius, map.Despawn.mPos.y + 32 + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32 + cos(45 * DEG2RAD) * radius, map.Despawn.mPos.y + 32 - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32 - cos(45 * DEG2RAD) * radius, map.Despawn.mPos.y + 32 - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((animationTimer / 4) - 30) / 30.0f));
                    DrawCircle(map.Despawn.mPos.x + 32, map.Despawn.mPos.y + 32, 1300 - ((animationTimer - 120) * 1300 / 120), ColorAlpha(WHITE, 1 - (animationTimer - 120) / 120.0f));
                }

                for (Turret *t : turret)
                {
                    t->active = false;
                }

                for (Enemy *e : enemy)
                {
                    e->direction = {0, 0};
                }

                hp = 0;
            }
            else if (hp <= 0 && animationTimer < 60)
            {
                DrawRectangle(0, 0, 1280, 768, ColorAlpha(WHITE,  1));
                std::ifstream readScore("HighScore.txt");
                if (readScore)
                {
                    int oldScore;
                    readScore >> oldScore;
                    if (round > oldScore)
                    {
                        highScoreBeated = true;
                        std::ofstream writeScore("HighScore.txt");
                        writeScore << round << std::endl;
                    }
                }
                else
                {
                    highScoreBeated = true;
                    std::ofstream writeScore("HighScore.txt");
                    writeScore << round << std::endl;
                }

                StopMusicStream(gameSounds.secondTheme);
                if (music)
                {
                    PlayMusicStream(gameSounds.gameOver);
                }
                gameOver = true;
            }
        }
        else
        {

            DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 0.3));

            SoundButton({480, 600, SIZE * 1.5f, SIZE * 1.5f}, music);
            SoundButton({700, 600, SIZE * 1.5f, SIZE * 1.5f}, soundEffect);

            DrawText("Music", 498, 570, 20, WHITE);
            DrawText("Sound Effects", 670, 570, 20, WHITE);

            if (Button(440, 200, 400, 100, "RESUME", 0.35f, 3, GRAY))
            {
                pause = false;
            }
            if (Button(440, 400, 400, 100, "MENU", 0.35f, 3, GRAY) && timerFadeScreen == FPS)
            {
                timerFadeScreen--;
            }
            else if (timerFadeScreen < FPS && timerFadeScreen > 0)
            {
                if (music)
                {
                    SetMusicVolume(gameSounds.secondTheme, 0.5 - (0.5 - (timerFadeScreen * 0.5 / (float)(FPS))));
                }
                DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timerFadeScreen / (float)(FPS))));
                FrameTimer(timerFadeScreen);
            }
            else if (timerFadeScreen <= 0)
            {
                DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timerFadeScreen / (float)(FPS))));
                bool currentMucic = music;
                bool currentSound = soundEffect;
                this->~Game();
                new (this) Game();
                this->music = currentMucic;
                this->soundEffect = currentSound;
            }
        }
    }
    else
    {

        if (animationTimer != 0)
        {
            FrameTimer(animationTimer);
        }
         DrawRectangleGradientV(0, 0, 1280, 1500, BLACK, MAROON);
        DrawText(TextFormat("WAVE %i", round), 540, 200, 40, LIGHTGRAY);
        if(highScoreBeated)
        {
            DrawText("New High Score!", 540, 250, 20, GOLD);
        }
        UpdateMusicStream(gameSounds.gameOver);
         
        if (Button(440, 400, 400, 100, "MENU", 0.35f, 3, GRAY) && timerFadeScreen == FPS)
        {
            timerFadeScreen--;
        }
        else if (timerFadeScreen < FPS && timerFadeScreen > 0)
        {
            if (music)
            {
                SetMusicVolume(gameSounds.gameOver, 0.5 - (0.5 - (timerFadeScreen * 0.5 / (float)(FPS))));
            }
            DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timerFadeScreen / (float)(FPS))));
            FrameTimer(timerFadeScreen);
        }
         DrawRectangle(0, 0, 1280, 768, ColorAlpha(WHITE,  (float)(animationTimer / 60.0f)));
         if (timerFadeScreen <= 0)
        {
            DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timerFadeScreen / (float)(FPS))));
            bool currentMucic = music;
            bool currentSound = soundEffect;
            animationTimer = 300;
            opacityZone = 0.4;
            this->~Game();
            new (this) Game();
            this->music = currentMucic;
            this->soundEffect = currentSound;
        }
       
       
    }
}

Game::~Game()
{

    for (Turret *t : turret)
        delete t;
    for (Enemy *e : enemy)
        delete e;
}