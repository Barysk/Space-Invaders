#include "spaceship.h"


Spaceship::Spaceship()
{
  image = LoadTexture("Graphics/spaceship.png");
  position.x = (GetScreenWidth() - image.width)/2;
  position.y = (GetScreenHeight() - image.height);
  speed = 5;
  cooldown = 0.3f;
  last_fire_time = 0.0;
}

// Every time when load image we need to unload it, to free memory it requires
Spaceship::~Spaceship()
{
  UnloadTexture(image);
}

void Spaceship::Draw()
{
  DrawTextureV(image, position, WHITE);
}

void Spaceship::MoveLeft()
{
  position.x -= speed;
  if(position.x < 0)
    position.x = 0;
}

void Spaceship::MoveRight()
{
  position.x += speed;
  if(position.x > GetScreenWidth() - image.width)
    position.x = GetScreenWidth() - image.width;
}

void Spaceship::FireLaser()
{
  if(GetTime() - last_fire_time >= cooldown)
    {
      lasers.push_back(Laser({position.x + image.width/2 - 2, position.y}, -6));
      last_fire_time = GetTime();
    }
}
