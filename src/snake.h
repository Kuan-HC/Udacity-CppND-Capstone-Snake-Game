#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <deque>
#include <SDL2/SDL.h>

class Snake
{
public:
  enum Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight,
    unknown
  };

  Snake(int grid_width, int grid_height, int num) : grid_width(grid_width), grid_height(grid_height), head_y(grid_height * 0.75f)
  {
    if (num == 0)
      head_x = grid_width * 0.25;
    else
      head_x = grid_width * 0.75;
    speed = 0.0f;
  }

  static std::vector<std::vector<bool>> grid;

  virtual void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);
  bool GetFood(SDL_Point food);

  Direction direction = kUp;

  float speed{0.2f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::deque<SDL_Point> body;
  int score{0};

protected:
  void UpdateHead();
  void UpdateBody(const SDL_Point *current_head_cell, SDL_Point &prev_head_cell);

  bool growing{false};
  int grid_width;
  int grid_height;
};

#endif