#include <iostream>
#include <fstream>
#include "game.hpp"
#include "resources.hpp"

#define FPS 60

void Game::UpdateAndDraw()
{
    TimerUpdater();

    if (!gameOver)
    {
        map.Draw(round);

        if (!pause)
        {
            DrawGame();
        }
        else
        {
            DrawPause();
        }
    }
    else
    {

        DrawGameOver();
    }
}

void Game::TimerUpdater()
{
        FrameTimer(timer.frameCounter);
    if (timer.frameCounter == 0)
    {
        timer.frameCounter = 60;
        timer.secondTimer++;
    }
    if (timer.secondTimer % 2)
        timer.parTimer = true;
    else
        timer.parTimer = false;
}

Game::Game()
{
    credit = false;
    opacityZone = 0.4;
    timer.spawnTimer = 600;
    timer.frameCounter = 60;
    timer.animationTimer = 300;
    timer.secondTimer = 0;
    timer.parTimer = false;
    maxEnemies = 10;
    gameSpeed = 1;
    timer.moneyTimer = 0;
    moneyGain = 0;
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
    music = true;       // Is music activated
    soundEffect = true; // Are sound effects activated
    highScoreBeated = false;
    hp = 20;
    maxHp = 20;
    money = 100;
    round = 0;
    timer.waveTimer= 0;
    timer.timerFadeScreen = FPS;
    showTurretRange = false;

    scrollingFive = 0.0f; // background slides positions in main menu
    scrollingFourth = 0.0f;
    scrollingThird = 0.0f;
    scrollingSecond = 0.0f;
    scrollingFirst = 0.0f;

    map.Init();
    DefSpawn(map.Spawn.pos);

    pauseSource = {map.texture[107].x, map.texture[107].y, SIZE, SIZE};

    classicTurret = {map.texture[250].x, map.texture[250].y, SIZE, SIZE};
    slowingTurret = {map.texture[249].x, map.texture[249].y, SIZE, SIZE};
    explosiveTurret = {map.texture[226].x, map.texture[226].y, SIZE, SIZE};

    warriorEnemy = {map.texture[247].x, map.texture[247].y, SIZE, SIZE};
    healerEnemy = {map.texture[245].x, map.texture[245].y, SIZE, SIZE};
    berserkerEnemy = {map.texture[246].x, map.texture[246].y, SIZE, SIZE};
}

bool Game::Button(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color) // Create a button, returns true when pressed
{
    bool res = false;

    DrawRectangle(x, y, width, height, color);

    if (InRec(x, y, width, height))
    {
        DrawRectangle(x, y, width, height, ColorAlpha(WHITE, 0.5));

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            if (soundEffect)
                PlaySound(gRes->sounds.button);

            res = true;
            DrawRectangle(x, y, width, height, RED);
        }
    }

    DrawText(name, x + nameSpacing * width, y + 0.25 * height, GetFontDefault().baseSize * nameSize, RAYWHITE);
    DrawRectangleLines(x, y, width, height, DARKGRAY);

    return res;
}

void DynamicTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint, bool parTimer, int frameCounter) //  animated DrawTexturePro (used for title in main menu)
{
    if (parTimer)
        DrawTexturePro(texture, source, {dest.x + (frameCounter - 30) / 4, dest.y + (frameCounter - 30) / 4, dest.width + 30 - frameCounter / 2, dest.height + 30 - frameCounter / 2}, origin, rotation, tint);

    else
        DrawTexturePro(texture, source, {dest.x - (frameCounter - 30) / 4, dest.y - (frameCounter - 30) / 4, dest.width + (frameCounter / 2), dest.height + frameCounter / 2}, origin, rotation, tint);
}

bool Game::DynamicButton(int x, int y, float width, float height, const char *name, float nameSpacing, float nameSize, Color color) //  animated button (used for ready button)
{
    if (timer.parTimer)
        return Button(x + (timer.frameCounter - 30) / 4, y + (timer.frameCounter - 30) / 4, width + 30 - timer.frameCounter / 2, height + 30 - timer.frameCounter / 2, name, nameSpacing - 0.05 + (timer.frameCounter / 2 * 0.001666), nameSize + 1.2 - (timer.frameCounter / 2 * 0.04), color);

    else
        return Button(x - (timer.frameCounter - 30) / 4, y - (timer.frameCounter - 30) / 4, width + (timer.frameCounter / 2), height + timer.frameCounter / 2, name, nameSpacing - (timer.frameCounter / 2 * 0.001666), nameSize + (timer.frameCounter / 2 * 0.04), color);
}

void Game::SoundButton(Rectangle dest, bool &type) // Create sound button, returns true when pressed
{

    if (InRec(dest))
    {
        DrawRectangleRec(dest, ColorAlpha(LIGHTGRAY, 0.5f));
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            type = !type;
            if (soundEffect)
                PlaySound(gRes->sounds.button);
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
    DrawTexturePro(gRes->textures.tilesheet, source, dest, {0, 0}, 0, WHITE);
}

void Game::EnemyDestroyedAnimation(Enemy *&e) // Enemies death animation
{

    Rectangle source;
    if (e->damage == 5)
    {
        source = {map.texture[269].x, map.texture[269].y, SIZE, SIZE};
        if (e->timer > 60 || e->timer % 3 == 0)
        {
            DrawTexturePro(gRes->textures.tilesheet, source, {e->pos.x - 32, e->pos.y - 32, 64, 64}, {0, 0}, 0, WHITE);
        }
    }
    else if (e->damage == 2)
    {

        source = {map.texture[270].x, map.texture[270].y, SIZE, SIZE};
        if (e->timer > 60 || e->timer % 3 == 0)
        {
            DrawTexturePro(gRes->textures.tilesheet, source, {e->pos.x - 32, e->pos.y - 32, 64, 64}, {0, 0}, 0, WHITE);
        }
    }
    else
    {
        source = {map.texture[268].x, map.texture[268].y, SIZE, SIZE};
        if (e->timer > 60 || e->timer % 3 == 0)
        {
            DrawTexturePro(gRes->textures.tilesheet, source, {e->pos.x - 32, e->pos.y - 32, 64, 64}, {0, 0}, 0, WHITE);
        }
    }
}

void Game::DrawTextWave()
{
    if (timer.waveTimer> 480)
    {
        DrawText(TextFormat("WAVE %i", round), 370, 350, 80, WHITE);
    }
    else
    {
        DrawText(TextFormat("WAVE %i", round), 370, 350, 80, ColorAlpha(WHITE, (timer.waveTimer- FPS * 7) / (float)FPS));
    }
}

void Game::Menu()
{

    FrameTimer(timer.frameCounter);
    if (timer.frameCounter == 0)
    {
        timer.frameCounter = 60;
        timer.secondTimer++;
    }
    if (timer.secondTimer % 2)
    {
        timer.parTimer = true;
    }
    else
    {
        timer.parTimer = false;
    }

    scrollingFive -= 0.1f;
    scrollingThird -= 0.5f;
    scrollingSecond -= 0.8f;
    scrollingFirst -= 1.2f;

    if (scrollingFive <= -gRes->textures.five.width * 2)
    {
        scrollingFive = 0;
    }
    if (scrollingThird <= -gRes->textures.third.width * 2)
    {
        scrollingThird = 0;
    }
    if (scrollingSecond <= -gRes->textures.second.width * 2)
    {
        scrollingSecond = 0;
    }
    if (scrollingFirst <= -gRes->textures.first.width * 2)
    {
        scrollingFirst = 0;
    }

    DrawTextureEx(gRes->textures.five, (Vector2){scrollingFive, 20}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(gRes->textures.five, (Vector2){gRes->textures.five.width * 2 + scrollingFive, 20}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(gRes->textures.fourth, (Vector2){1066, 369}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(gRes->textures.third, (Vector2){scrollingThird, 429}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(gRes->textures.third, (Vector2){gRes->textures.third.width * 2 + scrollingThird, 429}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(gRes->textures.second, (Vector2){scrollingSecond, 429}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(gRes->textures.second, (Vector2){gRes->textures.second.width * 2 + scrollingSecond, 429}, 0.0f, 2.0f, WHITE);

    DrawTextureEx(gRes->textures.first, (Vector2){scrollingFirst, 339}, 0.0f, 2.0f, WHITE);
    DrawTextureEx(gRes->textures.first, (Vector2){gRes->textures.first.width * 2 + scrollingFirst, 339}, 0.0f, 2.0f, WHITE);
    DynamicTexturePro(gRes->textures.title, {0, 0, (float)gRes->textures.title.width, (float)gRes->textures.title.height}, {320, 124, (float)gRes->textures.title.width, (float)gRes->textures.title.height}, {0, 0}, 0, WHITE, timer.parTimer, timer.frameCounter);

    if (Button(545, 535, 200, 50, "START", 0.22f, 3, GRAY))
    {
        StopMusicStream(gRes->sounds.mainTheme);
        start = true;
    }
    if (Button(545, 590, 200, 50, "QUIT", 0.32f, 3, GRAY))
    {
        quit = true;
    }
    if (Button(1050, 700, 150, 35, "CREDITS", 0.2f, 2, GRAY))
    {
        StopMusicStream(gRes->sounds.mainTheme);
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
        DrawText("Credits:  \"Blueberries\" coposed, performed, mixed and mastered by Viktor Kraus", 260, height + 430, 20, BLACK);
        creditHeight -= 2;
        if (creditHeight < -500)
        {
            titleID++;
            creditHeight = 780;
        }
    }

    if (Button(1050, 700, 150, 35, "MENU", 0.3f, 2, GRAY))
    {
        timer.timerFadeScreen--;
    }
    else if (timer.timerFadeScreen < FPS && timer.timerFadeScreen > 0)
    {
        if (music)
        {
            SetMusicVolume(gRes->sounds.creditsTheme, 0.5 - (0.5 - (timer.timerFadeScreen * 0.5 / (float)(FPS))));
        }
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timer.timerFadeScreen / (float)(FPS))));
        FrameTimer(timer.timerFadeScreen);
    }
    else if (timer.timerFadeScreen <= 0)
    {
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timer.timerFadeScreen / (float)(FPS))));
        titleID = 0;
        creditHeight = 768;
        timer.timerFadeScreen = FPS;
        StopMusicStream(gRes->sounds.creditsTheme);
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

    if (hp > 0 && enemies.size() != 0 && Button(1227, 69, 32, 32, TextFormat("x%i", gameSpeed), 0.2f, 2, BLANK))
    {
        switch (gameSpeed)
        {
        case 4:
            gameSpeed = 8;
            SetTargetFPS(480);

            break;
        case 8:
            gameSpeed = 1;
            SetTargetFPS(60);

            break;
        default:
            gameSpeed = 4;
            SetTargetFPS(240);

            break;
        }
    }

    DrawRectangleLinesEx(classicTurretIcon, 2, classicColor);
    DrawTexturePro(gRes->textures.tilesheet, classicTurret, classicTurretIcon, origin, 0, textureColor);

    DrawText("50", classicTurretIcon.x + 25, classicTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    Rectangle source = {map.texture[287].x, map.texture[287].y, SIZE, SIZE};
    Rectangle dest = {classicTurretIcon.x - 5, classicTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, priceColor);

    if (InRec(classicTurretIcon) && hp > 0)
    {
        DrawText("Classic Turret", 1070, 550, 20, RED);
        DrawText("Damage: Medium", 1050, 600, 20, BLACK);
        DrawText("Attack Speed: Medium", 1050, 630, 20, BLACK);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && money >= 50) // Buy and place new classic turret
        {
            turretSelected = true;
            turrets.push_back(new ClassicTurret);
            turrets.back()->sourceTexture = classicTurret;
        }
    }

    //UpdateAndDrawUI Slow turret
    if (money < 150 || round < 3)
    {
        priceColor = slowingColor = textureColor = LIGHTGRAY;
    }

    DrawRectangleLinesEx(slowingTurretIcon, 2, slowingColor);
    DrawTexturePro(gRes->textures.tilesheet, slowingTurret, slowingTurretIcon, origin, 0, textureColor);

    DrawText("150", slowingTurretIcon.x + 25, slowingTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    dest = {slowingTurretIcon.x - 5, slowingTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, priceColor);

    if (round < 3)
    {
        DrawTexturePro(gRes->textures.tilesheet, {map.texture[284].x, map.texture[284].y, SIZE, SIZE}, slowingTurretIcon, origin, 0, WHITE);
    }
    if (InRec(slowingTurretIcon) && hp > 0)
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
                turretSelected = true;
                turrets.push_back(new SlowingTurret);
                turrets.back()->sourceTexture = slowingTurret;
            }
        }
    }

    //UpdateAndDrawUI Explosive turret
    if (money < 300 || round < 5)
    {
        priceColor = explosiveColor = textureColor = LIGHTGRAY;
    }

    DrawRectangleLinesEx(explosiveTurretIcon, 2, explosiveColor);
    DrawTexturePro(gRes->textures.tilesheet, explosiveTurret, explosiveTurretIcon, origin, 0, textureColor);

    DrawText("300", explosiveTurretIcon.x + 25, explosiveTurretIcon.y + 70, GetFontDefault().baseSize * 2, priceColor);
    dest = {explosiveTurretIcon.x - 5, explosiveTurretIcon.y + 62, SIZE / 2, SIZE / 2};
    DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, priceColor);

    if (round < 5)
    {
        DrawTexturePro(gRes->textures.tilesheet, {map.texture[284].x, map.texture[284].y, SIZE, SIZE}, explosiveTurretIcon, origin, 0, WHITE);
    }
    if (InRec(explosiveTurretIcon) && hp > 0)
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
                turretSelected = true;
                turrets.push_back(new ExplosiveTurret);
                turrets.back()->sourceTexture = explosiveTurret;
            }
        }
    }

    //UpdateAndDrawUI jack hammer
    DrawRectangleLinesEx(jackHammerIcon, 2, SKYBLUE);

    if (!jackActive)
    {
        DrawTexture(gRes->textures.jackhammer, jackHammerIcon.x + 6, jackHammerIcon.y + 10, WHITE);
    }

    if (GetMousePosition().x < 1024 && GetMousePosition().x > 0 && GetMousePosition().y < 768 && GetMousePosition().y > 0)
    {
        DrawRectangleLines(map.tile[GetTile(GetMousePosition())].pos.x, map.tile[GetTile(GetMousePosition())].pos.y, SIZE, SIZE, ColorAlpha(WHITE, opacityZone));
    }

    if (InRec(jackHammerIcon) && hp > 0)
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
                PlaySound(gRes->sounds.sellTurret);
            }
            map.tile[GetTile(GetMousePosition())].environment = 9;
            timer.moneyTimer = FPS * 2;
            moneyGain = rand() % 15;
            money += moneyGain;
        }
        else
        {
            int a = 0;
            for (Turret *t : turrets)
            {

                if (GetTile(GetMousePosition()) == GetTile(t->pos))
                {
                    if (soundEffect)
                    {
                        PlaySound(gRes->sounds.sellTurret);
                    }
                    timer.moneyTimer = FPS * 2;
                    moneyGain = t->price / 2;
                    money += moneyGain;
                    delete t;
                    turrets.erase(turrets.begin() + a);
                    break;
                }
                a++;
            }
        }
        jackActive = !jackActive;
    }

    if (turretSelected)
    {
        if (GetMousePosition().x < 1024 && GetMousePosition().x > 0 && GetMousePosition().y < 768 && GetMousePosition().y > 0)
        {
            turrets.back()->pos.x = map.tile[GetTile(GetMousePosition())].pos.x + SIZE / 2;
            turrets.back()->pos.y = map.tile[GetTile(GetMousePosition())].pos.y + SIZE / 2;
        }
        else
        {
            turrets.back()->pos = GetMousePosition();
        }

        if ((GetMousePosition().x >= 1024 || GetMousePosition().x <= 0 || GetMousePosition().y >= 768 || GetMousePosition().y <= 0) || map.tile[GetTile(GetMousePosition())].active == true || map.tile[GetTile(GetMousePosition())].road != false)
        {
            turrets.back()->colorZone = RED;
            if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
            {
                delete turrets.back();
                turrets.pop_back();
                turretSelected = false;
            }
        }
        else
        {
            turrets.back()->colorZone = DARKBLUE;
            if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
            {
                money -= turrets.back()->price;
                map.tile[GetTile(GetMousePosition())].active = true;
                turrets.back()->active = true;
                turretSelected = false;
            }
        }
    }

    if (showTurretRange)
    {
        for (long unsigned int i = 0; i < turrets.size(); i++)
        {
            DrawCircleV(turrets[i]->pos, turrets[i]->range, ColorAlpha(turrets[i]->colorZone, opacityZone)); // Draw turret range
        }
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        showTurretRange = !showTurretRange;
    }

    DrawTexturePro(gRes->textures.tilesheet, pauseSource, pauseIcon, origin, 0, WHITE);
    if (hp > 0 && InRec(pauseIcon))
    {
        DrawRectangleLinesEx(pauseIcon, 1, ColorAlpha(WHITE, opacityZone));

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) // Pause the game
        {
            if (soundEffect)
            {
                PlaySound(gRes->sounds.button);
            }
            pause = true;
        }
    }
}

void Game::frontUI()
{
    if (jackActive)
    {
        DrawTexture(gRes->textures.jackhammer, GetMousePosition().x - 48 / 2, GetMousePosition().y, WHITE);
    }

    DrawText(TextFormat("%i", money), 60, 730, GetFontDefault().baseSize * 3, GOLD); // Money UI
    Rectangle source = {map.texture[287].x, map.texture[287].y, SIZE, SIZE};
    Rectangle dest = {10, 710, SIZE, SIZE};
    Vector2 origin = {0, 0};
    DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, GOLD);

    if (timer.moneyTimer > 0)
    {
        DrawText(TextFormat("+%i", moneyGain), 42, 700, GetFontDefault().baseSize * 3, ColorAlpha(GOLD, timer.moneyTimer / (float)(FPS / 2))); // Money gain indicator
    }

    // Health bar
    DrawRectangle(1040, 720, 225, 30, DARKBROWN);

    DrawRectangle(1040, 720, hp * 225 / maxHp, 30, ColorAlpha(GREEN, hp / (float)maxHp));
    DrawRectangle(1040, 720, hp * 225 / maxHp, 30, ColorAlpha(YELLOW, (1.0f - 2 * std::abs(0.5f - (hp / (float)maxHp)))));
    DrawRectangle(1040, 720, hp * 225 / maxHp, 30, ColorAlpha(RED, 1.0f - (hp / (float)maxHp)));

    DrawRectangleLines(1040, 720, 225, 30, WHITE);
    DrawText(TextFormat("%i / %i", hp, maxHp), 1050, 727, GetFontDefault().baseSize * 2, WHITE);

    if (timer.waveTimer== 0 && enemies.size() == 0 && hp > 0 && DynamicButton(400, 685, 224, 50, "Ready", 0.3f, 3, GREEN))
    {
        switch (gameSpeed)
        {
        case 4:
            SetTargetFPS(240);

            break;
        case 8:
            SetTargetFPS(480);

            break;
        default:
            SetTargetFPS(60);

            break;
        }

        round++;
        timer.waveTimer= timer.spawnTimer;
        if (round > 5)
        {
            maxEnemies += 2;
        }
    }
}

void Game::DeathAnimation()
{
    if (timer.animationTimer == 300)
    {
        SetTargetFPS(60);
        gameSpeed = 1;
        Despawn.environment = 1;
        StopMusicStream(gRes->sounds.secondTheme);
        if (soundEffect)
        {
            currentMusic = &(gRes->sounds.kaboom);
            SetMusicVolume(gRes->sounds.kaboom, 1);
            PlayMusicStream(gRes->sounds.kaboom);
        }

        if (turretSelected)
        {
            delete turrets.back();
            turrets.pop_back();
            turretSelected = false;
        }
        opacityZone = 0;
        map.Despawn.tilePos = 1000;
    }
    FrameTimer(timer.animationTimer);

    for (Turret *t : turrets)
    {
        t->active = false;
    }

    for (Enemy *e : enemies)
    {
        e->direction = {0, 0};
    }

    if (timer.animationTimer > 240)
    {

        Rectangle source = {map.texture[63].x, map.texture[63].y, SIZE, SIZE};
        Vector2 origin = {0, 0};
        if (timer.animationTimer % 4 == 0)
        {
            map.Despawn.environment = -1 * map.Despawn.environment;
        }

        Rectangle dest{float((int)map.Despawn.pos.x), map.Despawn.pos.y + map.Despawn.environment, SIZE, SIZE};
        DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, WHITE);
    }

    else if (timer.animationTimer <= 240 && timer.animationTimer > 60)
    {
        Rectangle dest{float((int)map.Despawn.pos.x), float((int)map.Despawn.pos.y), SIZE, SIZE};
        Vector2 origin = {0, 0};
        Rectangle source = {map.texture[86].x, map.texture[86].y, SIZE, SIZE};

        DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, WHITE);
        DrawCircle(map.Despawn.pos.x + 32, map.Despawn.pos.y + 32, 50.0f, ColorAlpha(RED, 0.25f / 30.f * ((timer.animationTimer / 4) - 30.0f)));
        DrawCircle(map.Despawn.pos.x + 32, map.Despawn.pos.y + 32, 20.0f, ColorAlpha(ORANGE, 0.3f / 30.f * ((timer.animationTimer / 4) - 30.0f)));
        float radius = (60 - (timer.animationTimer / 4)) * 2;

        DrawCircle(map.Despawn.pos.x + 32, map.Despawn.pos.y + 32 + radius, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32, map.Despawn.pos.y + 32 - radius, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32 + radius, map.Despawn.pos.y + 32, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32 - radius, map.Despawn.pos.y + 32, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32 + cos(45 * DEG2RAD) * radius, map.Despawn.pos.y + 32 + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32 - cos(45 * DEG2RAD) * radius, map.Despawn.pos.y + 32 + sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32 + cos(45 * DEG2RAD) * radius, map.Despawn.pos.y + 32 - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32 - cos(45 * DEG2RAD) * radius, map.Despawn.pos.y + 32 - sin(45 * DEG2RAD) * radius, 3, ColorAlpha(ORANGE, ((timer.animationTimer / 4) - 30) / 30.0f));
        DrawCircle(map.Despawn.pos.x + 32, map.Despawn.pos.y + 32, 1300 - ((timer.animationTimer - 120) * 1300 / 120), ColorAlpha(WHITE, 1 - (timer.animationTimer - 120) / 120.0f));
    }

    else
    {
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(WHITE, 1));
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

        StopMusicStream(gRes->sounds.secondTheme);
        gameOver = true;
        StopMusicStream(gRes->sounds.kaboom);
    }
}

void Game::NextWave()
{
    if (timer.waveTimer> timer.spawnTimer - (FPS * 3))
    {
        DrawTextWave();
    }
    if (timer.waveTimer!= 0 && round != 0) // WAVES
    {
        if (round == 1 && timer.waveTimer% (2 * FPS) == 0) // TEST WAVE 1
        {
            enemies.push_back(new Warrior);
            enemies.back()->sourceTexture = warriorEnemy;
        }

        else if (round == 2 && timer.waveTimer% FPS == 0) // TEST WAVE 2
        {
            enemies.push_back(new Warrior);
            enemies.back()->sourceTexture = warriorEnemy;
        }

        else if (round == 3 && timer.waveTimer% FPS == 0) // TEST WAVE 3
        {
            if (timer.waveTimer>= timer.spawnTimer - (2 * FPS))
            {
                enemies.push_back(new Berserker);
                enemies.back()->sourceTexture = berserkerEnemy;
            }
            else if (timer.waveTimer% (2 * FPS) == 0)
            {
                enemies.push_back(new Warrior);
                enemies.back()->sourceTexture = warriorEnemy;
            }
        }

        else if (round == 4 && timer.waveTimer% 60 == 0) // TEST WAVE 4
        {
            if (timer.waveTimer> timer.spawnTimer - (5 * FPS))
            {
                enemies.push_back(new Berserker);
                enemies.back()->sourceTexture = berserkerEnemy;
            }
            else if (timer.waveTimer% (2 * FPS) == 0)
            {
                enemies.push_back(new Warrior);
                enemies.back()->sourceTexture = warriorEnemy;
            }
        }

        else if (round == 5 && timer.waveTimer % FPS == 0) // TEST WAVE 5
        {
            if (timer.waveTimer>= timer.spawnTimer - (2 * FPS))
            {
                enemies.push_back(new Berserker);
                enemies.back()->sourceTexture = berserkerEnemy;
            }
            else if (timer.waveTimer> FPS)
            {
                enemies.push_back(new Warrior);
                enemies.back()->sourceTexture = warriorEnemy;
            }
            else
            {
                enemies.push_back(new Healer);
                enemies.back()->sourceTexture = healerEnemy;
            }
        }
        else if (round > 5 && timer.waveTimer% (timer.spawnTimer / maxEnemies) == 0)
        {

            int random = rand() % 10;

            if (random < 3)
            {
                enemies.push_back(new Berserker);
                enemies.back()->sourceTexture = berserkerEnemy;
            }

            else if (random < 5)
            {
                enemies.push_back(new Healer);
                enemies.back()->sourceTexture = healerEnemy;
            }

            else
            {
                enemies.push_back(new Warrior);
                enemies.back()->sourceTexture = warriorEnemy;
            }
        }
    }
}

void Game::DrawGame()
{
    backUI();

    if (turrets.size() > 0 && !turrets.back()->active)
    {
        DrawCircleV(turrets.back()->pos, turrets.back()->range, ColorAlpha(turrets.back()->colorZone, opacityZone)); // Draw turret range
    }
    for (Turret *t : turrets)

    {
        t->UpdateAndDraw(enemies, gRes->textures.tilesheet, map.texture[t->id + 295], gRes->sounds, soundEffect);

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
                    t->range += 64;
                    t->updatePrice *= 2;
                }
                DrawText(TextFormat("%i", t->updatePrice), t->pos.x + 30, t->pos.y - 14, GetFontDefault().baseSize * 2, GOLD);
                Rectangle source = {map.texture[287].x, map.texture[287].y, SIZE, SIZE};
                Rectangle dest = {t->pos.x, t->pos.y - 22, SIZE / 2, SIZE / 2};
                Vector2 origin = {0, 0};
                DrawTexturePro(gRes->textures.tilesheet, source, dest, origin, 0, GOLD);
            }
        }

        if (turrets.back()->active && InRec(t->pos.x - 32, t->pos.y - 32, SIZE, SIZE))
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

    for (long unsigned int t = 0; t < enemies.size(); t++) // DESTROY ENEMY CONDITIONS
    {
        if (enemies[t]->posTile == map.Despawn.tilePos)
        {
            if (enemies.size() == 1)
            {
                SetTargetFPS(60);
            }
            hp -= enemies[t]->damage;
            if (hp < 0)
            {
                hp = 0;
            }
            Enemy *tmp = enemies[t];
            enemies.erase(enemies.begin() + t);
            delete tmp;
            t--;
        }
        else if (enemies[t]->active)
        {
            enemies[t]->UpdateAndDraw(map, round, enemies);
            if (enemies[t]->hp <= 0)
            {
                timer.moneyTimer = FPS * 2;
                moneyGain = enemies[t]->reward;
                money += moneyGain;
                enemies[t]->timer = FPS * 2;
                enemies[t]->active = false;
            }
        }
        else if (enemies[t]->timer > 0)
        {

            EnemyDestroyedAnimation(enemies[t]);
            FrameTimer(enemies[t]->timer);
        }
        else
        {
            if (enemies.size() == 1)
            {
                SetTargetFPS(60);
            }
            Enemy *tmp = enemies[t];
            enemies.erase(enemies.begin() + t);
            delete tmp;
            t--;
        }
    }

    NextWave();

    if (IsKeyPressed(KEY_SPACE)) // TEST enemy spawner
    {
        enemies.push_back(new Warrior);
        enemies.back()->sourceTexture = warriorEnemy;
        enemies.push_back(new Healer);
        enemies.back()->sourceTexture = healerEnemy;
        enemies.push_back(new Berserker);
        enemies.back()->sourceTexture = berserkerEnemy;
        round++;
    }

    FrameTimer(timer.waveTimer);
    FrameTimer(timer.moneyTimer);

    frontUI();
    if (hp <= 0)
    {
        DeathAnimation();
    }
}

void Game::DrawPause()
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
    if (Button(440, 400, 400, 100, "MENU", 0.35f, 3, GRAY) && timer.timerFadeScreen == FPS)
    {
        SetTargetFPS(60);
        gameSpeed = 1;
        timer.timerFadeScreen--;
    }
    else if (timer.timerFadeScreen < FPS && timer.timerFadeScreen > 0)
    {
        if (music)
        {
            SetMusicVolume(gRes->sounds.secondTheme, 0.5 - (0.5 - (timer.timerFadeScreen * 0.5 / (float)(FPS))));
        }
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timer.timerFadeScreen / (float)(FPS))));
        FrameTimer(timer.timerFadeScreen);
    }
    else if (timer.timerFadeScreen <= 0)
    {
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timer.timerFadeScreen / (float)(FPS))));
        StopMusicStream(gRes->sounds.secondTheme);
        bool isCurrentMusicActive = music;
        bool isCurrentSoundActive = soundEffect;
        this->~Game();
        new (this) Game();
        this->music = isCurrentMusicActive;
        this->soundEffect = isCurrentSoundActive;
    }
}

void Game::DrawGameOver()
{
    if (timer.animationTimer > 0)
    {
        FrameTimer(timer.animationTimer);
    }
    else if (music && !IsMusicStreamPlaying(gRes->sounds.gameOver))
    {
        PlayMusicStream(gRes->sounds.gameOver);
    }
    DrawRectangleGradientV(0, 0, 1280, 1500, BLACK, MAROON);
    DrawText(TextFormat("WAVE %i", round), 535, 200, 50, LIGHTGRAY);
    if (highScoreBeated)
    {
        DrawText("New High Score!", 550, 250, 20, GOLD);
    }
    UpdateMusicStream(gRes->sounds.gameOver);

    if (Button(440, 400, 400, 100, "MENU", 0.35f, 3, GRAY) && timer.timerFadeScreen == FPS)
    {
        timer.timerFadeScreen--;
    }
    else if (timer.timerFadeScreen < FPS && timer.timerFadeScreen > 0)
    {
        if (music)
        {
            SetMusicVolume(gRes->sounds.gameOver, 0.5 - (0.5 - (timer.timerFadeScreen * 0.5 / (float)(FPS))));
        }
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timer.timerFadeScreen / (float)(FPS))));
        FrameTimer(timer.timerFadeScreen);
    }
    DrawRectangle(0, 0, 1280, 768, ColorAlpha(WHITE, (float)(timer.animationTimer / 60.0f)));
    if (timer.timerFadeScreen <= 0)
    {
        DrawRectangle(0, 0, 1280, 768, ColorAlpha(BLACK, 1.0 - (timer.timerFadeScreen / (float)(FPS))));
        StopMusicStream(gRes->sounds.secondTheme);
        timer.animationTimer = 300;
        opacityZone = 0.4;
        bool isCurrentMusicActive = music;
        bool isCurrentSoundActive = soundEffect;
        this->~Game();
        new (this) Game();
        this->music = isCurrentMusicActive;
        this->soundEffect = isCurrentSoundActive;
    }
}



Game::~Game()
{

    for (Turret *t : turrets)
        delete t;
    for (Enemy *e : enemies)
        delete e;
}