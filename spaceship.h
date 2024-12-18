#pragma once
#include <raylib.h>
#include <vector> // used to hold lasers
#include "laser.h"

class Spaceship
{
public:
  Spaceship(); // Constructor
  ~Spaceship();	// Destructor

  // Declaring some public methods
  // Those are public becouse other parts of the program are going to call it
  void Draw();
  void MoveLeft();
  void MoveRight();
  void FireLaser();
  std::vector<Laser> lasers;
private:
  // Fairly enough those functions are private
  // becouse they are going to be local to the ship
  Texture2D image;
  Vector2 position;
  unsigned int speed;
  float cooldown;
  double last_fire_time;
};
