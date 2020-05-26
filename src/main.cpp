#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <utility>

int main(int argc, char **argv) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(std::move(kGridWidth), std::move(kGridHeight));
  game.Run(controller, renderer, std::move(kMsPerFrame));
  std::cout << "Game has terminated successfully!\n";
  #ifdef PLAYER
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  #endif
  return 0;
}