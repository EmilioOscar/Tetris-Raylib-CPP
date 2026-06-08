#include <raylib.h>
#include "game.h"
#include "colors.h"
#include <iostream>

double LastUpdateTime = 0; // Global variable to track the last time an event was triggered

bool eventTriggered(double interval) // Function to check if a certain time interval has passed since the last event
{
  double currentTime = GetTime();
  if (currentTime - LastUpdateTime >= interval)
  {
    LastUpdateTime = currentTime;
    return true; // Time interval has passed, trigger the event
  }
  return false;
}

int main()
{
  const int screenWidth = 500;  // 10 columns * 30 pixels each
  const int screenHeight = 620; // 20 rows * 30 pixels each

  InitWindow(screenWidth, screenHeight, "raylib Tetris");
  SetTargetFPS(60);

  Font font = LoadFontEx("font/PixelifySans-Regular.ttf", 64, 0, 0); // Load a pixel font for drawing text

  Game game = Game(); // Initialize the game

  while (WindowShouldClose() == false) // Main game loop
  {
    UpdateMusicStream(game.music); // Update the music stream to keep it playing smoothly
    game.HandleInput();            // Handle user input for moving the current block
    if (eventTriggered(0.2))
    {
      game.MoveBlockDown(); // Move the current block down every 0.2 seconds
    }

    BeginDrawing();
    ClearBackground(DarkBlue);
    DrawTextEx(font, "Score", {365, 15}, 38, 2, WHITE);
    DrawTextEx(font, "Next", {370, 175}, 38, 2, WHITE);
    if (game.gameOver)
    {
      DrawTextEx(font, "GAME OVER", {320, 450}, 38, 2, RED);
    }
    DrawRectangleRounded({320, 55, 170, 60}, 0.3, 6, LightBlue);
    char ScoreText[10];
    sprintf(ScoreText, "%d", game.score);                     // Convert score to string for drawing
    Vector2 TextSize = MeasureTextEx(font, ScoreText, 38, 2); // Measure the width of the score text

    DrawTextEx(font, ScoreText, {320 + (170 - TextSize.x) / 2, 65}, 38, 2, WHITE);
    DrawRectangleRounded({320, 215, 170, 180}, 0.3, 6, LightBlue);
    game.Draw();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
