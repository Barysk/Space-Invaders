#pragma once
#include "spaceship.h"

class Game
{
public:
  Game();
  ~Game();
  void Draw(); // Draw all game objects
  void Update(); // Update positions of all game objects
  void HandleInput(); // Handle player input
private:
  Spaceship spaceship; // spaceship atribute
  void deleteInactiveLasers();
};
