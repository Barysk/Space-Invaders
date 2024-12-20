#include <raylib.h>
#include "game.h"
#include "string"

std::string FormatWithLeadingZeros(int number, int width)
{
  std::string numberText = std::to_string(number);
  int leadingZeros = width - numberText.length();
  return numberText = std::string(leadingZeros, '0') + numberText;
}

int main()
{
  Color grey = {10, 10, 10, 255};
  Color yellow = {243, 216, 63, 255};
  int offset = 50;
  int windowWidth = 750;
  int windowHeight = 700;

  // Creating window *Must be closed at the end
  InitWindow(windowWidth + offset, windowHeight + 2*offset, "Space Invaders");

  // Audio *Must be closed at the end
  InitAudioDevice();

  // Loading font
  Font font = LoadFontEx("Font/monogram.ttf", 64, 0, 0);

  // Loading spaceship sprite
  Texture2D spaceshipImage = LoadTexture("Graphics/spaceship.png");

  // Setting target FPS if not set than the game wil run as fast as it can
  SetTargetFPS(60);

  Game game;

  // If some destruction thing is happening eg. ESC pressed,
  // than WindowShouldClose will return true
  while(WindowShouldClose() == false)
    {
      UpdateMusicStream(game.music);

      game.HandleInput(); // Game handles input before anything happened on screen
      game.Update(); // Game update that handles moving of items not controlled by player

      BeginDrawing(); // Creates black canvas, so we can draw game objects on

      ClearBackground(grey); // Clears last frame and sets backround again
      DrawRectangleRoundedLinesEx({10,10,780,780}, 0.18f, 20, 3, yellow);
      DrawLineEx({25,730}, {775, 730}, 3, yellow);

      // Displaying game's state
      if(game.run)
        DrawTextEx(font, "LEVEL 01", {570, 740}, 34, 2, yellow);
      else
        DrawTextEx(font, "GAME OVER", {570, 740}, 34, 2, yellow);

      // Displaying player's health
      float x = 50.0;
      for(int i = 0; i < game.lives; i++)
        {
          DrawTextureV(spaceshipImage, {x, 745}, WHITE);
          x += 50;
        }

      DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
      std::string scoreText = FormatWithLeadingZeros(game.score, 6);
      DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

      DrawTextEx(font, "HI-SCORE", {570, 15}, 34, 2, yellow);
      std::string hiScoreText = FormatWithLeadingZeros(game.hiScore, 6);
      DrawTextEx(font, hiScoreText.c_str(), {570, 40}, 34, 2, yellow);

      game.Draw(); // Actually draw spaceship on screen using game class
      EndDrawing(); // Ends drawing canvas
    }

  // Destroing window
  CloseWindow();

  // Closing audio
  CloseAudioDevice();
}
