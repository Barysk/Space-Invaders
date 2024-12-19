#include <raylib.h>
#include "game.h"

int main()
{
  Color grey = {10, 10, 10, 255};
  int windowWidth = 800;
  int windowHeight = 600;

  // Creating window
  InitWindow(windowWidth, windowHeight, "Space Invaders");

  // Setting target FPS if not set than the game wil run as fast as it can
  SetTargetFPS(60);

  Game game;

  // If some destruction thing is happening eg. ESC pressed,
  // than WindowShouldClose will return true
  while(WindowShouldClose() == false)
    {

      game.HandleInput(); // Game handles input before anything happened on screen
      game.Update(); // Game update that handles moving of items not controlled by player

      BeginDrawing(); // Creates black canvas, so we can draw game objects on

      ClearBackground(grey); // Clears last frame and sets backround again
      game.Draw(); // Actually draw spaceship on screen using game class
      EndDrawing(); // Ends drawing canvas
    }

  // Destroing window
  CloseWindow();
}
