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
        growing = true; /* KuanH remember to delete after test */
        UpdateBody(&current_cell, prev_cell);
        set_map_self(body, grid);
    }

    for (auto row : grid)
    {
        for (auto i : row)
            std::cout << i << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Auto_snake::set_map_self(const std::deque<SDL_Point> &body, std::vector<std::vector<int>> &grid_name)
{
    if (body.empty() != true)
    {
        for (const auto &i : body)
        {
            grid_name[i.x][i.y] = 1;
        }
    }
}
