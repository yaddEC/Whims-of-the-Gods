#include "game.hpp"

static bool pointSelected = false;
static Vector2 mousePos;
const Rectangle classicTurretIcone = (Rectangle){1110, 64, SIZE, SIZE};
const Rectangle slowingTurretIcone = (Rectangle){1110,  256, SIZE, SIZE};
const Rectangle explosiveTurretIcone = (Rectangle){1110, 448, SIZE, SIZE};

std::vector<Turret *> turret;
std::vector<Enemy *> enemy;

Game::Game()
{
    map.Init();
    classicTurret.model = LoadTexture("assets/classic_turret.png");
    slowingTurret.model = LoadTexture("assets/slowing_turret.png");
    explosiveTurret.model = LoadTexture("assets/explosive_turret.png");
}

bool InRec(int x, int y, float width, float height)
{
    int X = GetMouseX();
    int Y = GetMouseY();

    if (
        (X >= x) &&
        (X <= x + width) &&
        (Y >= y) &&
        (Y <= y + height))
    {
        return true;
    }
    return false;
}

bool InRec(Rectangle rec)
{
    int X = GetMouseX();
    int Y = GetMouseY();

    if (
        (X >= rec.x) &&
        (X <= rec.x + rec.width) &&
        (Y >= rec.y) &&
        (Y <= rec.y + rec.height))
    {
        return true;
    }
    return false;
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

void Game::UpdateAndDraw()
{
    map.Draw();

    DrawRectangleLinesEx(classicTurretIcone, 2, RED);
    DrawTexture(classicTurret.model, classicTurretIcone.x, classicTurretIcone.y, WHITE);

    DrawRectangleLinesEx(slowingTurretIcone, 2, GREEN);
    DrawTexture(slowingTurret.model, slowingTurretIcone.x, slowingTurretIcone.y, WHITE);

    DrawRectangleLinesEx(explosiveTurretIcone, 2, ORANGE);
    DrawTexture(explosiveTurret.model, explosiveTurretIcone.x, explosiveTurretIcone.y, WHITE);

    mousePos.x = GetMousePosition().x;
    mousePos.y = GetMousePosition().y;

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

    if (pointSelected || (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && (InRec(classicTurretIcone) || InRec(slowingTurretIcone) || InRec(explosiveTurretIcone))))
    {

        turret.back()->pos = mousePos;
        pointSelected = true;

        if (IsMouseButtonUp(MOUSE_LEFT_BUTTON))
        {
            turret.back()->active = true;
            pointSelected = false;
        }
    }

    for (long unsigned int i = 0; i < turret.size(); i++)
    {
        if (turret[i]->active) //if the turret is active
        {
            int nearestEnemyId = -1;
            int nearestEnemyDistance = -1;
            for (auto j = 0u; turret[i]->target == -1 && j < enemy.size(); j++) // Check every enemy if turret has no current target
            {
                float normTurretEnemy = norm(vector(enemy[j]->pos, Vector2{turret[i]->pos.x, turret[i]->pos.y}));
                if (normTurretEnemy <= turret[i]->range) // if enemy in turret range
                {
                    if (nearestEnemyDistance == -1 || normTurretEnemy < nearestEnemyDistance) // if enemy closer than current nearest enemy
                    {
                        nearestEnemyDistance = normTurretEnemy;
                        nearestEnemyId = j;
                    }
                }
            }
            if (nearestEnemyId != -1) // targets nearest enemy if turret has no current target
            {
                turret[i]->target = nearestEnemyId;
            }
            if (turret[i]->target != -1 && norm(vector(enemy[turret[i]->target]->pos, Vector2{turret[i]->pos.x, turret[i]->pos.y})) <= turret[i]->range) // The turret rotate to aim the target
            {
                turret[i]->rotation = -acos((enemy[turret[i]->target]->pos.x - turret[i]->pos.x) / norm(vector(enemy[turret[i]->target]->pos, Vector2{turret[i]->pos.x, turret[i]->pos.y}))) * RAD2DEG;
                if (enemy[turret[i]->target]->pos.y - turret[i]->pos.y > 0)
                {
                    turret[i]->rotation = -turret[i]->rotation;
                }
                turret[i]->rotation += 90;
            }
            else // No more target
            {
                turret[i]->target = -1;
            }
        }

        if (showTurretRange || InRec(turret[i]->pos.x - 32, turret[i]->pos.y - 32, SIZE, SIZE))
        {
            DrawCircleV(turret[i]->pos, turret[i]->range, ColorAlpha(DARKBLUE, 0.3)); // Draw turret range
        }
        Rectangle destRec = {turret[i]->pos.x, turret[i]->pos.y, SIZE, SIZE};
        DrawTexturePro(turret[i]->texture.model, turret[i]->texture.sourceRec, destRec, turret[i]->texture.origin, turret[i]->rotation, WHITE); // Draw turret
    }
    for (auto i = 0u; i < enemy.size(); i++)
    {

        if (enemy[i]->pos.x - enemy[i]->radius < 0 || enemy[i]->pos.x + enemy[i]->radius > 1024) // TEST ENEMY
            enemy[i]->direction.x *= -1;
        if (enemy[i]->pos.y - enemy[i]->radius < 0 || enemy[i]->pos.y + enemy[i]->radius > 728)
            enemy[i]->direction.y *= -1;
        enemy[i]->pos.x += enemy[i]->direction.x;
        enemy[i]->pos.y += enemy[i]->direction.y;
        DrawCircle(enemy[i]->pos.x, enemy[i]->pos.y, enemy[i]->radius, RED);
    }

    if (IsKeyPressed(KEY_SPACE)) // TEST enemy spawner
    {
        enemy.push_back(new Enemy);
    }

    if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
    {
        showTurretRange = !showTurretRange;
    }
}

void Game::Delete()
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