#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

constexpr int gWindowWidth  {384};
constexpr int gWindowHeight {384};

int main()
{

        Texture2D   map;
        Vector2     mapPos   {0.0, 0.0};
        float       mapScale {4.0f};



    InitWindow (gWindowWidth, gWindowHeight, "Open World Game");

    map = LoadTexture ("NatureTileset/OpenWorldMap24x24.png");

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture ("NatureTileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture ("NatureTileset/Log.png")}};

        Character   knight {gWindowWidth, gWindowHeight};

        Enemy goblin1{
            Vector2{900.f, 550.f},
            LoadTexture ("characters/goblin_idle_spritesheet.png"),
            LoadTexture ("characters/goblin_run_spritesheet.png")};

        Enemy goblin2{
            Vector2{300.f, 250.f},
            LoadTexture ("characters/goblin_idle_spritesheet.png"),
            LoadTexture ("characters/goblin_run_spritesheet.png")};

        Enemy slime1{
            Vector2{900.f, 250.f},
            LoadTexture ("characters/slime_idle_spritesheet.png"),
            LoadTexture ("characters/slime_run_spritesheet.png")};

        Enemy slime2{
            Vector2{500.f, 700.f},
            LoadTexture ("characters/slime_idle_spritesheet.png"),
            LoadTexture ("characters/slime_run_spritesheet.png")};

        Enemy * enemies[] {&goblin1, &goblin2, &slime1, &slime2};

    for (auto enemy : enemies)
        enemy->setTarget (&knight);

    SetTargetFPS (60);

    while (!WindowShouldClose ())
    {
        BeginDrawing ();
        ClearBackground (WHITE);

        mapPos = Vector2Scale (knight.getWorldPos (), -1.f);

        // draw the map
        DrawTextureEx (map, mapPos, 0.0, 4.0, WHITE);

        // draw the props
        for (auto prop : props)
            prop.Render (knight.getWorldPos ());

        if (!knight.getAlive ()) { // Character is not alive

            DrawText ("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing ();
            continue;

        } else { // Character is alive

            std::string knightsHealth = "Health: ";

            knightsHealth.append (std::to_string (knight.getHealth ()), 0, 5);
            DrawText (knightsHealth.c_str (), 55.f, 45.f, 40, RED);
        }

        knight.tick(GetFrameTime ());

        // check map bounds

        if (knight.getWorldPos ().x < 0.f ||
            knight.getWorldPos ().y < 0.f ||
            knight.getWorldPos ().x + gWindowWidth > map.width * mapScale ||
            knight.getWorldPos ().y + gWindowHeight > map.height * mapScale)
            knight.undoMovement ();

        // check prop collisions
        for (auto prop : props) {

            if (CheckCollisionRecs (prop.getCollisionRec (knight.getWorldPos ()), knight.getCollisionRec ()))
                knight.undoMovement ();
        }

        for (auto enemy : enemies)
            enemy->tick (GetFrameTime ());

        if (IsMouseButtonPressed (MOUSE_LEFT_BUTTON)) {

            for (auto enemy : enemies) {

                if (CheckCollisionRecs (enemy->getCollisionRec (), knight.getWeaponCollisionRec ()))
                    enemy->setAlive (false);
            }
        }

        EndDrawing ();
    }

    CloseWindow ();
}