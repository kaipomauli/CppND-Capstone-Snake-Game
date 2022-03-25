#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "square.h"
#include "circle.h"

int main(int argc, char* argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  std::vector<std::shared_ptr<Square>> squares;
  squares.push_back(std::make_shared<Square>(2,3,0.1,Obstacle::Direction::kRight,kGridWidth,kGridHeight));
  squares.push_back(std::make_shared<Square>(3,3, 0.1, Obstacle::Direction::kUp, kGridWidth, kGridHeight));
  
  std::vector<std::shared_ptr<Circle>> balls;
  balls.push_back(std::make_shared<Circle>(1, 0.1, Obstacle::Direction::kDown, kGridWidth, kGridHeight));
  balls.push_back(std::make_shared<Circle>(2, 0.1, Obstacle::Direction::kLeft, kGridWidth, kGridHeight));
  Game game(kGridWidth, kGridHeight,squares,balls);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}