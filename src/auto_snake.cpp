#include "auto_snake.h"

void Auto_snake::Update()
{    
    SDL_Point prev_cell
    {
        static_cast<int>(head_x),
        static_cast<int>(head_y)
    }; // We first capture the head's cell before updating.

    head_y -= speed;    

    SDL_Point current_cell
    {
        static_cast<int>(head_x),
        static_cast<int>(head_y)
    }; // Capture the head's cell after updating.

    //Update all of the body vector items if the snake head has moved to a new cell
    
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
    {        
        UpdateBody(&current_cell, prev_cell);
    }
        
}

void Auto_snake::UpdateBody(const SDL_Point *current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);
  grid[prev_head_cell.x][prev_head_cell.y] = 1; /*add snake body into grid */

  if (!growing)
  {
    // Remove the tail from the vector.
    grid[body[0].x][body[0].y] = 0; /*remove from grid */
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

