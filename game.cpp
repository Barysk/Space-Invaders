#include "game.h"

Game::Game()
{
  obstacles = CreateObstacles();
}

Game::~Game()
{

}

void Game::Update()
{
  for(auto& laser: spaceship.lasers)
    {
      laser.Update();
    }

  deleteInactiveLasers();
}

void Game::Draw()
{
  spaceship.Draw();

  // Range Based For Loop
  // basicly foreach loop that loops through every element of spaceship.lasers vector
  // auto is a variable type, compiler will autmaticly identify that it is Vector
  // auto can be changed to a std:Vector var named Laser. auto here adds a layer of readability
  // & is need for referenciing every var in array, so no need to copy it.
  for(auto& laser: spaceship.lasers)
    {
      laser.Draw();
    }

  for(auto& obstacle: obstacles)
    {
      obstacle.Draw();
    }
}

void Game::HandleInput()
{
  if(IsKeyDown(KEY_LEFT))
    {
      spaceship.MoveLeft();
    }
  else if(IsKeyDown(KEY_RIGHT))
    {
      spaceship.MoveRight();
    }
  else if(IsKeyDown(KEY_SPACE))
    {
      spaceship.FireLaser();
    }
}

void Game::deleteInactiveLasers()
{
  // Iterator usage
  for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
      // it->active checks whether the active property of the object pointed to by the iterator (it) is false.
      // !it->active means "if the laser is inactive"
      // it deletes current element if it's inactive and does NOT iterates to the next one
      // sice indexation is changed.
      if(!it -> active)
        {
          it = spaceship.lasers.erase(it);
        }
      else
        {
          ++it;
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
  int obstacleWidth = Obstacle::grid[0].size() * 3;
  int gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

  for(int i = 0; i < 4; i++){
      float offsetX = (i + 1) * gap + i * obstacleWidth;
      obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }

  return obstacles;
}
