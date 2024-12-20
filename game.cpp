#include "game.h"
#include <iostream>
#include <fstream>

Game::Game()
{
  music = LoadMusicStream("Sounds/Music.wav");
  explosionSound = LoadSound("Sounds/Explosion.wav");
  PlayMusicStream(music);
  InitGame();
}

Game::~Game()
{
  Alien::UnloadImages();
  UnloadMusicStream(music);
  UnloadSound(explosionSound);
}

void Game::Update()
{
  if(run)
    {
    double currentTime = GetTime();
    if(currentTime - timeLastSpawn > mysteryShipSpawnInteval)
      {
        mysteryShip.Spawn();
        timeLastSpawn = GetTime();
        mysteryShipSpawnInteval = GetRandomValue(10, 20);
      }

    for(auto& laser: spaceship.lasers)
      {
        laser.Update();
      }

    MoveAliens();

    AlienShootLaser();

    for(auto& laser: alienLasers)
      {
        laser.Update();
      }

    deleteInactiveLasers();

    mysteryShip.Update();

    CheckForCollisions();
    }
  else
    {
      if(IsKeyDown(KEY_ENTER))
        {
          Reset();
          InitGame();
        }
    }
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
      laser.Draw();

  for(auto& obstacle: obstacles)
      obstacle.Draw();

  for(auto& alien: aliens)
      alien.Draw();

  for(auto& laser: alienLasers)
      laser.Draw();

  mysteryShip.Draw();
}

void Game::HandleInput()
{
  if(run)
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

  for(auto it = alienLasers.begin(); it != alienLasers.end();)
    {
      // it->active checks whether the active property of the object pointed to by the iterator (it) is false.
      // !it->active means "if the laser is inactive"
      // it deletes current element if it's inactive and does NOT iterates to the next one
      // sice indexation is changed.
      if(!it -> active)
        {
          it = alienLasers.erase(it);
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
      obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }

  return obstacles;
}

std::vector<Alien> Game::CreateAliens(){
  std::vector<Alien> aliens;
  for(int row = 0; row < 5; row++)
    {
      for(int column = 0; column < 11; column++)
        {
          int alienType;
          switch (row) {
            case 0:
              alienType = 3;
              break;
            case 1:
            case 2:
              alienType = 2;
              break;
            default:
              alienType = 1;
              break;
            }
          float x = 75 + column * 55; // cellSize
          float y = 110 + row * 55;
          aliens.push_back(Alien(alienType, {x, y}));
        }
    }
  return aliens;
}

void Game::MoveAliens()
{
  for(auto& alien: aliens)
    {
      if(alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 25)
        {
          aliensDirection = -1;
          MoveDownAliens(4);
        }
      else if(alien.position.x < 25)
        {
          aliensDirection = 1;
          MoveDownAliens(4);
        }
      alien.Update(aliensDirection);
    }
}

void Game::MoveDownAliens(int distance)
{
  for(auto& alien: aliens)
    {
      alien.position.y += distance;
    }
}

void Game::AlienShootLaser()
{
  double currentTime = GetTime();
  if(currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty())
    {
      int randomIndex = GetRandomValue(0, aliens.size() - 1);
      Alien& alien = aliens[randomIndex];
      alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type - 1].width/2,
                                   alien.position.y + alien.alienImages[alien.type - 1].height}, 6));
      timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{
  // Spaceship Lasers
  for(auto& laser: spaceship.lasers)
    {
      auto it = aliens.begin();
      while(it != aliens.end())
        {
          if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
              switch (it -> type) {
                case 1:
                  score += 100;
                  break;
                case 2:
                  score += 200;
                  break;
                case 3:
                  score += 300;
                  break;
                default:
                  score += 100;
                }

              CheckForHiScore();
              PlaySound(explosionSound);
              it = aliens.erase(it);
              laser.active = false;
            }
          else
            {
              ++it;
            }
        }

      for(auto& obstacle: obstacles)
        {
          auto it = obstacle.blocks.begin();
          while(it != obstacle.blocks.end())
            {
              if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
                {
                  it = obstacle.blocks.erase(it);
                  laser.active = false;
                }
              else
                {
                  ++it;
                }
            }
        }

      if(CheckCollisionRecs(mysteryShip.getRect(), laser.getRect()))
        {
          score += 500;
          CheckForHiScore();
          PlaySound(explosionSound);
          mysteryShip.isAlive = false;
          laser.active = false;
        }
    }

  // Alien Lasers
  for(auto& laser: alienLasers)
    {
      if(CheckCollisionRecs(laser.getRect(), spaceship.getRect()))
        {
          laser.active = false;
          lives--;
          if(lives == 0)
            GameOver();
        }

      for(auto& obstacle: obstacles)
        {
          auto it = obstacle.blocks.begin();
          while(it != obstacle.blocks.end())
            {
              if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
                {
                  it = obstacle.blocks.erase(it);
                  laser.active = false;
                }
              else
                {
                  ++it;
                }
            }
        }
    }

  // Alien Collision with obstacle
  for(auto& alien: aliens)
    {
      for(auto& obstacle: obstacles)
        {
          auto it = obstacle.blocks.begin();
          while(it != obstacle.blocks.end())
            {
              if(CheckCollisionRecs(it -> getRect(), alien.getRect()))
                {
                  it = obstacle.blocks.erase(it);
                }
              else
                {
                  it ++;
                }
            }
        }

      if(CheckCollisionRecs(alien.getRect(), spaceship.getRect()))
        GameOver();
    }
}

void Game::GameOver()
{
  run = false;
  std::cout << "Game Over" << std::endl;
}

void Game::InitGame()
{
  obstacles = CreateObstacles();
  aliens = CreateAliens();
  aliensDirection = 1;
  timeLastAlienFired = 0.0;
  mysteryShipSpawnInteval = GetRandomValue(10, 20);
  timeLastSpawn = 0.0;
  score = 0;
  hiScore = LoadHighScoreFromFile();
  lives = 3;
  run = true;
}

void Game::Reset()
{
  spaceship.Reset();
  aliens.clear();
  alienLasers.clear();
  obstacles.clear();
}

void Game::CheckForHiScore()
{
  if(score > hiScore)
    {
      hiScore = score;
      SaveHiScoreToFile(hiScore);
    }
}

void Game::SaveHiScoreToFile(int highscore)
{
  std::ofstream highscorefile("highscore.txt");
  if(highscorefile.is_open())
    {
      highscorefile << highscore;
      highscorefile.close();
    }
  else
    {
      std::cerr << "Failed to save highscore to file" << std::endl;
    }
}

int Game::LoadHighScoreFromFile()
{
  int loadedHiScore = 0;
  std::ifstream highscorefile("highscore.txt");
  if(highscorefile.is_open())
    {
      highscorefile >> loadedHiScore;
      highscorefile.close();
    }
  else
    {
      std::cerr << "Failed to load highscore from file" << std::endl;
      loadedHiScore = 1000;
    }
  return loadedHiScore;
}
