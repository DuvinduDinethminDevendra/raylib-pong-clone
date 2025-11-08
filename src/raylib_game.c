/*******************************************************************************************
*
* My First Pong Game
*
* This is a simple Pong clone created with raylib.
* This code is in a single file to make it easy to learn.
*
********************************************************************************************/
#include "raylib.h"

//----------------------------------------------------------------------------------
// Program main entry point
//----------------------------------------------------------------------------------
int main(void)
{
    // --- Initialization ---
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "My Pong Game");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // --- Main Game Loop ---
    // This loop runs 60 times a second, until you close the window
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //----------------------------------------------------------------------------------
        // --- Update ---
        // This is where all your game logic (movement, input, collision) will go
        //----------------------------------------------------------------------------------
        // (Your logic code will go here)
        //----------------------------------------------------------------------------------
        // --- Draw ---
        // This is where you draw everything to the screen
        //----------------------------------------------------------------------------------
        BeginDrawing();

            // Clear the screen with a color
            ClearBackground(BLACK);

            // --- Draw your game objects here ---
            // Draw a welcome message
            DrawText("Welcome to Pong! Let's start building.", 190, 200, 20, LIGHTGRAY);


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // --- De-Initialization ---
    CloseWindow();        // Close window and OpenGL context

    return 0;
}