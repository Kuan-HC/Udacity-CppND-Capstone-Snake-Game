#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  SDL_Point prev_cell
  {
    static_cast<int>(head_x),
    static_cast<int>(head_y)
  };  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell
  {
    static_cast<int>(head_x),
    static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(&current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }
  
  //std::cout << "head_y:" << head_y <<std::endl;

  // Wrap the Snake around to the beginning if going off of the screen.
  // head_x = fmod(head_x + grid_width, grid_width);
  // head_y = fmod(head_y + grid_height, grid_height);

  /* limit snake active range, once snake head is beyond range, set alive to false
     when x or y greater than 32.0, set it to 31.. for rendering */

  if (head_x < 0.0f || head_y < 0.0f || head_x >= 32.0f || head_y >= 32.0f)
  {
    alive = false;
    if (head_x >= 32.0f)
      head_x = 31.99;
    else if(head_y >= 32.0f)
      head_y = 31.99;
  }
  
  //std::cout << "after cmath head_y:" << head_y <<std::endl;
}

void Snake::UpdateBody(const SDL_Point *current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing)
  {
    // Remove the tail from the vector.
    //body.erase(body.begin());
    body.pop_front();
  }
  else
  {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body)
{
    if (current_head_cell->x == item.x && current_head_cell->y == item.y)
    {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
     {
      return true;
    }
  }
  return false;
}

bool Snake::GetFood(SDL_Point food)
{ 
  bool get_food = false;
  int new_x = static_cast<int>(head_x);
  int new_y = static_cast<int>(head_y);

  if (food.x == new_x && food.y == new_y)
  {
    get_food = true;
    // Grow snake and increase speed.
    score++;
    GrowBody();
    speed += 0.02;
  }

  return get_food;
}