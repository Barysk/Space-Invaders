#pragma once
#include "spaceship.h"
#include "obstacle.h"

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
  std::vector<Obstacle> CreateObstacles(); // Method to create obstacles
  void deleteInactiveLasers(); // Method to delete lasers that left the screen
  std::vector<Obstacle> obstacles; // Var to keep all obstacles
};
