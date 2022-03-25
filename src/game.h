#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "square.h"
#include "circle.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height,std::vector<std::shared_ptr<Square>> &squVec, std::vector<std::shared_ptr<Circle>>& ballVec);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

 private:
  Snake snake;
  SDL_Point food;
  
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
  std::vector<std::shared_ptr<Square>> squares;
  std::vector<std::shared_ptr<Circle>> balls;
  int score{0};
  void PlaceObstacle(std::shared_ptr<Square> sqr);
  void PlaceObstacle(std::shared_ptr<Circle> circ);
  void PlaceFood();
  void Update();
};

#endif