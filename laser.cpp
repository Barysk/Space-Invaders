#include "laser.h"
#include <iostream>

Laser::Laser(Vector2 position, int speed)
{
  this -> position = position;
  this -> speed = speed;
  active = true;
}

void Laser::Draw()
{
  if(active)
    DrawRectangle(position.x, position.y, 4, 16, {243, 216, 63, 255});
}

void Laser::Update()
{
  position.y += speed;
  if(position.y > GetScreenHeight() || position.y < 0)
    {
      active = false;
      std::cout << "laser inactive" << std::endl;
    }
}
