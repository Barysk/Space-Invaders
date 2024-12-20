#pragma once
#include "spaceship.h"
#include "obstacle.h"
#include "alien.h"
#include "mysteryship.h"

class Game
{
public:
  Game();
  ~Game();
  void Draw(); // Draw all game objects
  void Update(); // Update positions of all game objects
  void HandleInput(); // Handle player input
  bool run;
  unsigned int lives;
  unsigned int score;
  unsigned int hiScore;
  Music music;

private:
  // Game
  void GameOver();
  void Reset();
  void InitGame();
  void CheckForHiScore();
  void SaveHiScoreToFile(int highscore);
  int LoadHighScoreFromFile();
  Sound explosionSound;

  // Spaceship
  Spaceship spaceship; // spaceship atribute

  // Obstacle
  std::vector<Obstacle> CreateObstacles(); // Method to create obstacles
  void deleteInactiveLasers(); // Method to delete lasers that left the screen
  std::vector<Obstacle> obstacles; // Var to keep all obstacles

  // Alien
  std::vector<Alien> CreateAliens();
  std::vector<Alien> aliens;
  void MoveAliens();
  void MoveDownAliens(int distance);
  int aliensDirection;
  void AlienShootLaser();
  std::vector<Laser> alienLasers;
  constexpr static float alienLaserShootInterval = 0.35; // constexpr used for giving value here in header file
  float timeLastAlienFired;

  // MysteryShip
  MysteryShip mysteryShip;
  float mysteryShipSpawnInteval;
  float timeLastSpawn;

  // Collisions
  void CheckForCollisions();
};
