/*******************************************************************************************  // NOLINT
 *
 * My First Pong Game
 *
 * Copyright 2025 Duvindu Dinethmin Devendra
 *
 * This is a simple Pong clone created with raylib.
 * This code is in a single file to make it easy to learn.
 *
 ********************************************************************************************/
#include "raylib.h"  // NOLINT

// states
typedef enum GameScreen {   // NOLINT
    LOGO = 0,
    TITLE,
    SCREEN_MENU,
    SCREEN_GAMEPLAY,
    ENDING } GameScreen;

//----------------------------------------------------------------------------------
// Program main entry point
//----------------------------------------------------------------------------------
int main(void) {
    // --- Initialization ---
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "My Pong Game");

    GameScreen currentScreen = SCREEN_MENU;

    Rectangle player1 = { 50, screenHeight/2 - 40, 10, 80 };  // Left paddle  // NOLINT
    player1.width = 20;
    player1.height = 100;
    player1.x = 50;
    player1.y = screenHeight / 2 - player1.height / 2;  // Center paddle vertically  // NOLINT
    
    // Define the opponent paddle (right side)  // NOLINT
    Rectangle player2 = { screenWidth - 70, screenHeight/2 - 40, 10, 80 };  // Right paddle  // NOLINT
    player2.width = 20;
    player2.height = 100;
    player2.x = screenWidth - player2.width - 10;
    player2.y = screenHeight / 2 - player2.height / 2;  // Center paddle vertically  // NOLINT

    // Define the ball  // NOLINT
    Vector2 ballPosition = { screenWidth / 2.0f, screenHeight / 2.0f };  // Ball position  // NOLINT
    float ballRadius = 10.0f;  // Ball radius  // NOLINT

    Vector2 ballSpeed = { 5.0f, 5.0f };  // Ball speed (pixels per frame)  // NOLINT



    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // --- Main Game Loop ---
    // This loop runs 60 times a second, until you close the window
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {  // NOLINT
    // ----------------------------------------------------------------------------------
    // --- Update ---
    // This is where all your game logic (movement, input, collision) will go
    // ----------------------------------------------------------------------------------
    // Ball radius defined above
    // paddle speed
        float playerSpeed = 7.0f;   // NOLINT
    switch (currentScreen)
    {
        case SCREEN_MENU:
            if (IsKeyPressed(KEY_ENTER))
            {
                    currentScreen = SCREEN_GAMEPLAY;
            }break;
        case SCREEN_GAMEPLAY:
            // player 1 controls
            if (IsKeyDown(KEY_W) && player1.y > 0)
                player1.y -= playerSpeed;  // Move paddle up
            if (IsKeyDown(KEY_S) && (player1.y + player1.height) < screenHeight)
                player1.y += playerSpeed;  // Move paddle down
            // player 2 controls
            if (IsKeyDown(KEY_UP) && player2.y > 0)
                player2.y -= playerSpeed;  // Move paddle up
            if (IsKeyDown(KEY_DOWN) && (player2.y + player2.height) < screenHeight)
                player2.y += playerSpeed;  // Move paddle down

            // keep paldles inside the screen
            if (player1.y < 0) player1.y = 0;
            if ((player1.y + player1.height) > screenHeight) player1.y = screenHeight - player1.height;
            if (player2.y < 0) player2.y = 0;
            if ((player2.y + player2.height) > screenHeight) player2.y = screenHeight - player2.height;

            // ball movement logic
            ballPosition.x += ballSpeed.x;  // Move ball to the right
            ballPosition.y += ballSpeed.y;  // Move ball down

            // ball bounce logic walls
            if (ballPosition.y > (screenHeight - ballRadius) || ballPosition.y < ballRadius) {
                ballSpeed.y *= -1;  // Reverse vertical direction
            }
            // ball bounce logic paddles
            if (CheckCollisionCircleRec(ballPosition, ballRadius, player1)) {
                ballSpeed.x *= -1;  // Reverse horizontal direction
            }
            if (CheckCollisionCircleRec(ballPosition, ballRadius, player2)) {
                ballSpeed.x *= -1;  // Reverse horizontal direction
            }
            if (ballPosition.x < 0 || ballPosition.x > screenWidth) {
                // Reset ball position to center
                ballPosition.x = screenWidth / 2.0f;
                ballPosition.y = screenHeight / 2.0f;
            }
            break;
        default:
            break;
    }



    // ----------------------------------------------------------------------------------
    // --- Draw ---
    // This is where you draw everything to the screen
    // ----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        switch (currentScreen)
        {
            case SCREEN_MENU:
                DrawText("MY PONG GAME", screenWidth / 2 - 100, screenHeight / 2 - 60, 40, LIGHTGRAY);
                DrawText("PRESS ENTER TO START", screenWidth / 2 - 200, screenHeight / 2 - 20, 20, LIGHTGRAY);
                DrawText("Created by Duvindu Dinethmin Devendra", screenWidth / 2 - 130, screenHeight - 40, 10, GRAY);
                break;
            case SCREEN_GAMEPLAY:
                // Draw paddles
                DrawRectangleRec(player1, WHITE);
                DrawRectangleRec(player2, WHITE);
                // Draw ball
                DrawCircleV(ballPosition, ballRadius, WHITE);
                break;
            default:
                break;
        }



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // --- De-Initialization ---
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
