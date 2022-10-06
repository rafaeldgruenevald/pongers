#include "raylib.h"


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    Rectangle borderTop = {0, 0, screenWidth, 20};
    Rectangle borderBottom = {0, 430, screenWidth, 20};
    
    Rectangle bola = {screenWidth/2 - 10, screenHeight/2 - 10, 20, 20};
    Vector2 velsBola = {4.0f, -3.0f};

    Rectangle player = {screenWidth/2 - 380, screenHeight/2, 20, 60};
    float velPlayer = 5.0f;
    int pontosPlayer = 0;

    Rectangle enemy = {screenWidth/2 + 360, screenHeight/2, 20, 60};
    float velEnemy = 5.0f;
    int pontosEnemy = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] - PONG!");
    
    Image marcao = LoadImage("../image/boludomarcao.png");
    Texture2D textura = LoadTextureFromImage(marcao);


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if (IsKeyDown(KEY_W)) player.y -= velPlayer;
        if (IsKeyDown(KEY_S)) player.y += velPlayer;
        
        bola.x += velsBola.x;
        bola.y += velsBola.y;

        enemy.y += velEnemy;

        if (CheckCollisionRecs(player, borderTop)) {
            player.y = 20;
        }

        if (CheckCollisionRecs(player, borderBottom)) {
            player.y = 375;
        }

        if (CheckCollisionRecs(enemy, borderTop)) {
            velEnemy *= -1;
        }

        if (CheckCollisionRecs(enemy, borderBottom)) {
            enemy.y = 370;
            velEnemy *= -1;
        }
        
        if (CheckCollisionRecs(bola, borderTop) || CheckCollisionRecs(bola, borderBottom)) {
            velsBola.y *= -1;
            bola.y += velsBola.y;
        }

        if (CheckCollisionRecs(bola, enemy) || CheckCollisionRecs(bola, player)) {
            velsBola.x *= -1;
            bola.x += velsBola.x;
        }

        if (bola.x <= 0) {
            bola.x = screenWidth/2 - 10;
            bola.y = screenHeight/2 - 10;
            pontosEnemy++;
        }

        if (bola.x >= screenWidth) {
            bola.x = screenWidth/2 - 10;
            bola.y = screenHeight/2 - 10;
            pontosPlayer++;
        }


        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            DrawText("PONG!", screenWidth/2 - 40, screenHeight/2 - 10, 40, LIGHTGRAY);
            DrawTexture(textura, bola.x, bola.y, WHITE);
            DrawText(TextFormat("%i", pontosPlayer), 100, 40, 60, LIGHTGRAY);
            DrawText(TextFormat("%i", pontosEnemy), 700, 40, 60, LIGHTGRAY);
            DrawRectangle(borderTop.x, borderTop.y, borderTop.width, borderTop.height, WHITE);
            DrawRectangle(borderBottom.x, borderBottom.y, borderBottom.width, borderBottom.height, WHITE);
            // DrawRectangle(bola.x, bola.y, bola.width, bola.height, RED);
            DrawRectangle(player.x, player.y, player.width, player.height, WHITE);
            DrawRectangle(enemy.x, enemy.y, enemy.width, enemy.height, WHITE);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    UnloadTexture(textura);
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}