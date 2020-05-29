#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <deque>
#include <SDL2/SDL.h>
#include <iostream>

class Snake
{
public: 

  Snake(int grid_width, int grid_height, int num) : grid_width(grid_width), grid_height(grid_height), head_y(grid_height * 0.75f)
  {
    if (num == 0)
      head_x = grid_width * 0.25;
    else
      head_x = grid_width * 0.75;
      
    speed = 0.2f;
  }

  enum Direction
  {
    kUp,
    kDown,
    kLeft,
    kRight,
    unknown
  };
  Direction direction = kUp;
  std::deque<SDL_Point> body;

  float speed{0.0f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;

  static std::vector<std::vector<bool>> grid;

  virtual void Update(const std::deque<SDL_Point> & other_body);

  void GrowBody();
  bool SnakeCell(int x, int y);
  bool GetFood(SDL_Point food);
  int get_score()const{return score;}

protected:
  int score{0};
  bool growing{false};
  int grid_width;
  int grid_height;

  void UpdateHead();
  void UpdateBody(const SDL_Point *current_head_cell, SDL_Point &prev_head_cell, const std::deque<SDL_Point> & other_body);

};

#endif