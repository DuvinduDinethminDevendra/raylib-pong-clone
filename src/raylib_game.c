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
#include <stdio.h>   // NOLINT

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
    Color ballColor = WHITE;  // Ball color (white)  // NOLINT

    // Score tracking
    int player1Score = 0;  // Player 1 (left paddle) score  // NOLINT
    int player2Score = 0;  // Player 2 (right paddle) score  // NOLINT

    // selected option for menu
    static int selectedOption = 0;

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // --- Main Game Loop ---
    // This loop runs 60 times a second, until you close the window
    while (!WindowShouldClose()) {    // Detect window close button or ESC key  // NOLINT
    // ----------------------------------------------------------------------------------
    // --- Update ---
    // This is where all your game logic (movement, input, collision) will go
    // ----------------------------------------------------------------------------------
    // Ball radius defined above
    // paddle speed
    float playerSpeed = 7.0f;   // NOLINT
    switch (currentScreen) {  // NOLINT
        case SCREEN_MENU:
            {
                // Toggle selection with arrow keys or mouse wheel
                if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
                    selectedOption = (selectedOption - 1 + 2) % 2;
                }
                if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
                    selectedOption = (selectedOption + 1) % 2;
                }
                int wheelMove = GetMouseWheelMove();
                if (wheelMove != 0) {
                    selectedOption = (selectedOption - wheelMove + 2) % 2;
                }

                // Select option with ENTER
                if (IsKeyPressed(KEY_ENTER)) {
                    if (selectedOption == 0) {
                        currentScreen = SCREEN_GAMEPLAY;
                        // Reset scores for new game
                        player1Score = 0;  // NOLINT
                        player2Score = 0;  // NOLINT
                    } else if (selectedOption == 1) {
                        // Option 1 (AI) - coming soon
                        currentScreen = ENDING;
                    }
                }
            } break;
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
                ballColor = YELLOW;  // Change ball color Player 2  // NOLINT
            }
            if (CheckCollisionCircleRec(ballPosition, ballRadius, player2)) {
                ballSpeed.x *= -1;  // Reverse horizontal direction
                ballColor = RED;  // Change ball color Player 1  // NOLINT
            }
            if (ballPosition.x < 0 || ballPosition.x > screenWidth) {
                // Reset ball position to center
                ballPosition.x = screenWidth / 2.0f;
                ballPosition.y = screenHeight / 2.0f;
                ballColor = WHITE;  // Reset ball color  // NOLINT

                // Award points based on which side ball went out
                if (ballPosition.x < 0) {
                    player2Score++;  // Ball went left, player 2 scores  // NOLINT
                } else {
                    player1Score++;  // Ball went right, player 1 scores  // NOLINT
                }
            }
            break;
        case ENDING:
            // Ending screen logic (if any)
            DrawText("THANK YOU FOR PLAYING!", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, LIGHTGRAY);
            DrawText("PRESS ENTER TO RETURN TO MENU", screenWidth / 2 - 150, screenHeight / 2 + 10, 20, LIGHTGRAY);
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = SCREEN_MENU;
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

        switch (currentScreen) {  // NOLINT
            case SCREEN_MENU:
                DrawText("MY PONG GAME", screenWidth / 2 - 150, screenHeight / 2 - 80, 40, LIGHTGRAY);
               // draw indicator - highlight the selected option
                if (selectedOption == 0) {
                    DrawText("1. Player vs Player", screenWidth / 2 - 100, screenHeight / 2 - 30, 15, YELLOW);
                    DrawText("2. Player vs AI (Coming Soon)", screenWidth / 2 - 100, screenHeight / 2 - 10, 15, LIGHTGRAY);  // NOLINT
                } else if (selectedOption == 1) {
                    DrawText("1. Player vs Player", screenWidth / 2 - 100, screenHeight / 2 - 30, 15, LIGHTGRAY);
                    DrawText("2. Player vs AI (Coming Soon)", screenWidth / 2 - 100, screenHeight / 2 - 10, 15, YELLOW);
                }
                DrawText("Created by Duvindu Dinethmin Devendra", screenWidth / 2 - 130, screenHeight - 40, 10, GRAY);
                break;
            case SCREEN_GAMEPLAY:
                // Draw paddles
                DrawRectangleRec(player1, RED);
                DrawRectangleRec(player2, YELLOW);
                // Draw ball
                DrawCircleV(ballPosition, ballRadius, ballColor);

                // Draw score
                char scoreText1[20];
                char scoreText2[20];
                sprintf(scoreText1, "Player 1: %d", player1Score);  // NOLINT
                sprintf(scoreText2, "Player 2: %d", player2Score);  // NOLINT
                DrawText(scoreText1, 20, 20, 20, RED);
                DrawText(scoreText2, screenWidth - 180, 20, 20, YELLOW);
                break;
            case ENDING:
                DrawText("THANK YOU FOR PLAYING!", screenWidth / 2 - 100, screenHeight / 2 - 20, 20, LIGHTGRAY);
                DrawText("PRESS ENTER TO RETURN TO MENU", screenWidth / 2 - 150, screenHeight / 2 + 10, 20, LIGHTGRAY);
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
