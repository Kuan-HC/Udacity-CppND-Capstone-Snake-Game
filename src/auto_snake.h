#include "snake.h"
#include <iostream>

class Auto_snake : public Snake
{
    public:
    Auto_snake(int grid_width, int grid_height):Snake(grid_width, grid_height)
    {
        std::cout << "auto snke built" << grid_width << std::endl;
    }
};