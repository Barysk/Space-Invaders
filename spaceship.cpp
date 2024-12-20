#include "spaceship.h"


Spaceship::Spaceship()
{
  image = LoadTexture("Graphics/spaceship.png");
  position.x = (GetScreenWidth() - image.width)/2;
  position.y = (GetScreenHeight() - image.height) - 100;
  speed = 5;
  cooldown = 0.3f;
  last_fire_time = 0.0;
  laserSound = LoadSound("Sounds/laser.ogg");
}

// Every time when load image we need to unload it, to free memory it requires
Spaceship::~Spaceship()
{
  UnloadTexture(image);
  UnloadSound(laserSound);
}

void Spaceship::Draw()
{
  DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
  position.x -= speed;
  if(position.x < 25)
    position.x = 25;
}

void Spaceship::MoveRight()
{
  position.x += speed;
  if(position.x > GetScreenWidth() - image.width - 25)
    position.x = GetScreenWidth() - image.width - 25;
}

void Spaceship::FireLaser()
{
  if(GetTime() - last_fire_time >= cooldown)
    {
      lasers.push_back(Laser({position.x + image.width/2 - 2, position.y}, -6));
      last_fire_time = GetTime();
      PlaySound(laserSound);
    }
}

Rectangle Spaceship::getRect()
{
  return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
  position.x = (GetScreenWidth() - image.width)/2;
  position.y = (GetScreenHeight() - image.height) - 100;
  lasers.clear();
}
