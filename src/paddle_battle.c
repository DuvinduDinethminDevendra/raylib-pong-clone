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

// Game modes
typedef enum GameMode {  // NOLINT
    PVP = 0,     // Player vs Player
    PVAI = 1 }   // Player vs AI
GameMode;

//----------------------------------------------------------------------------------
// AI Function - Makes the AI paddle track the ball
//----------------------------------------------------------------------------------
void UpdateAIPaddle(Rectangle *aiPaddle, Vector2 ballPosition, float aiSpeed,
                    int screenHeight) {
    float paddle_center = aiPaddle->y + aiPaddle->height / 2.0f;

    // AI tries to center the paddle on the ball
    if (paddle_center < ballPosition.y - 35.0f) {
        aiPaddle->y += aiSpeed;  // Move paddle down  // NOLINT
    } else if (paddle_center > ballPosition.y + 35.0f) {
        aiPaddle->y -= aiSpeed;  // Move paddle up  // NOLINT
    }

    // Keep AI paddle inside the screen
    if (aiPaddle->y < 0) {
        aiPaddle->y = 0;
    }
    if ((aiPaddle->y + aiPaddle->height) > screenHeight) {
        aiPaddle->y = screenHeight - aiPaddle->height;
    }
}

//----------------------------------------------------------------------------------
// Program main entry point
//----------------------------------------------------------------------------------
int main(void) {
    // --- Initialization ---
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Paddle Battle");

    // Initialize audio device
    InitAudioDevice();  // NOLINT

    // Load sound effects
    Sound paddleHitSound = LoadSound("resources/paddle_hit.wav");  // NOLINT
    Sound wallHitSound = LoadSound("resources/wall_hit.wav");  // NOLINT
    Sound ballMissSound = LoadSound("resources/mixkit-funny-game-over-2878.wav");  // NOLINT
    Sound pointMadeSound = LoadSound("resources/coin.wav");  // NOLINT

    GameScreen currentScreen = SCREEN_MENU;

    // Game mode tracking
    GameMode gameMode = PVP;  // Start with Player vs Player  // NOLINT

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
    int winPoints = 5;    // Points needed to win  // NOLINT
    int winner = 0;       // Winner: 0 = none, 1 = player1, 2 = player2  // NOLINT

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
                        gameMode = PVP;  // Set to Player vs Player  // NOLINT
                        currentScreen = SCREEN_GAMEPLAY;
                        // Reset scores for new game
                        player1Score = 0;  // NOLINT
                        player2Score = 0;  // NOLINT
                    } else if (selectedOption == 1) {
                        gameMode = PVAI;  // Set to Player vs AI  // NOLINT
                        currentScreen = SCREEN_GAMEPLAY;
                        // Reset scores for new game
                        player1Score = 0;  // NOLINT
                        player2Score = 0;  // NOLINT
                    }
                }
            } break;
        case SCREEN_GAMEPLAY:
            // player 1 controls
            if (IsKeyDown(KEY_W) && player1.y > 0)
                player1.y -= playerSpeed;  // Move paddle up
            if (IsKeyDown(KEY_S) && (player1.y + player1.height) < screenHeight)
                player1.y += playerSpeed;  // Move paddle down
            
            // player 2 controls - depends on game mode
            if (gameMode == PVP) {
                // Player vs Player - human controls
                if (IsKeyDown(KEY_UP) && player2.y > 0)
                    player2.y -= playerSpeed;  // Move paddle up
                if (IsKeyDown(KEY_DOWN) && (player2.y + player2.height) < screenHeight)
                    player2.y += playerSpeed;  // Move paddle down
            } else if (gameMode == PVAI) {
                // Player vs AI - use AI logic
                UpdateAIPaddle(&player2, ballPosition, playerSpeed, screenHeight);
            }

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
                PlaySound(wallHitSound);  // Play wall collision sound  // NOLINT
            }
            // ball bounce logic paddles
            if (CheckCollisionCircleRec(ballPosition, ballRadius, player1)) {
                ballSpeed.x *= -1;  // Reverse horizontal direction
                ballColor = YELLOW;  // Change ball color Player 2  // NOLINT
                PlaySound(paddleHitSound);  // Play paddle collision sound  // NOLINT
            }
            if (CheckCollisionCircleRec(ballPosition, ballRadius, player2)) {
                ballSpeed.x *= -1;  // Reverse horizontal direction
                ballColor = RED;  // Change ball color Player 1  // NOLINT
                PlaySound(paddleHitSound);  // Play paddle collision sound  // NOLINT
            }
            if (ballPosition.x < 0 || ballPosition.x > screenWidth) {
                // Award points based on which side ball went out
                if (ballPosition.x < 0) {
                    PlaySound(ballMissSound);  // Play ball miss sound  // NOLINT
                    WaitTime(0.7f);  // Brief pause after scoring  // NOLINT
                    player2Score++;  // Ball went left, player 2 scores  // NOLINT
                    PlaySound(pointMadeSound);  // Play point made sound  // NOLINT

                } else {
                    PlaySound(ballMissSound);  // Play ball miss sound  // NOLINT
                    WaitTime(0.7f);  // Brief pause after scoring  // NOLINT
                    player1Score++;  // Ball went right, player 1 scores  // NOLINT
                    PlaySound(pointMadeSound);  // Play point made sound  // NOLINT
                }

                // Reset ball position to center
                ballPosition.x = screenWidth / 2.0f;
                ballPosition.y = screenHeight / 2.0f;
                ballColor = WHITE;  // Reset ball color  // NOLINT

                // Check for winner (first to 5 points)
                if (player1Score >= winPoints) {
                    winner = 1;  // Player 1 wins  // NOLINT
                    currentScreen = ENDING;
                } else if (player2Score >= winPoints) {
                    winner = 2;  // Player 2 wins  // NOLINT
                    currentScreen = ENDING;
                }
            }
            break;
        case ENDING:
            // Ending screen logic
            if (IsKeyPressed(KEY_ENTER)) {
                currentScreen = SCREEN_MENU;
                // Reset scores and winner for next game
                player1Score = 0;  // NOLINT
                player2Score = 0;  // NOLINT
                winner = 0;        // NOLINT
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
                    DrawText("2. Player vs AI", screenWidth / 2 - 100, screenHeight / 2 - 10, 15, LIGHTGRAY);
                } else if (selectedOption == 1) {
                    DrawText("1. Player vs Player", screenWidth / 2 - 100, screenHeight / 2 - 30, 15, LIGHTGRAY);
                    DrawText("2. Player vs AI", screenWidth / 2 - 100, screenHeight / 2 - 10, 15, YELLOW);
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
                // Display winner message
                if (winner == 1) {
                    DrawText("PLAYER 1 WINS!", screenWidth / 2 - 120, screenHeight / 2 - 60, 40, RED);
                } else if (winner == 2) {
                    DrawText("PLAYER 2 WINS!", screenWidth / 2 - 120, screenHeight / 2 - 60, 40, YELLOW);
                }

                // Display final scores
                char finalScore1[30];
                char finalScore2[30];
                sprintf(finalScore1, "Final Score - Player 1: %d", player1Score);  // NOLINT
                sprintf(finalScore2, "Final Score - Player 2: %d", player2Score);  // NOLINT
                DrawText(finalScore1, screenWidth / 2 - 150, screenHeight / 2, 20, RED);
                DrawText(finalScore2, screenWidth / 2 - 150, screenHeight / 2 + 30, 20, YELLOW);

                DrawText("PRESS ENTER TO RETURN TO MENU", screenWidth / 2 - 180, screenHeight / 2 + 80, 20, LIGHTGRAY);
                break;

            default:
                break;
        }



        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // --- De-Initialization ---
    UnloadSound(paddleHitSound);  // Unload paddle hit sound  // NOLINT
    UnloadSound(wallHitSound);    // Unload wall hit sound  // NOLINT
    CloseAudioDevice();           // Close audio device  // NOLINT
    CloseWindow();        // Close window and OpenGL context

    return 0;
}
