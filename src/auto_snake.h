#include "snake.h"
#include <iostream>
#include <vector>

class Auto_snake : public Snake
{
    public: 
    Auto_snake(int grid_width, int grid_height, int num):Snake(grid_width, grid_height, num)
    {
        std::cout << "Build auto snke" << std::endl;
    }

    void Update();

    private:

     typedef struct
    {
        int x;
        int y;
        Direction action;
    } Delta;

    template <typename T>
    void vector_init(T default_val, std::vector<std::vector<T> > &grid_name, int width, int height);   

    void set_map_self(const std::deque<SDL_Point> &body , std::vector<std::vector<int> > &grid_name); /* catch env set play and self as obstacle */

    std::vector<std::vector<int> > grid;
    std::vector<std::vector<int> > value;
    std::vector<std::vector<Direction> > direction_arr;
    std::vector<Delta> delta_list = {{-1, 0, kUp}, {1, 0, kDown }, {0, -1, kLeft}, {0, 1, kRight}}; /*move: up, down, left, right */

};

template <typename T>
void Auto_snake::vector_init(T default_val, std::vector<std::vector<T> > &grid_name, int width, int height)
{
    std::vector<T> row(width,default_val);
    for (int index = 0; index < height;  ++index)
    {
        grid_name.push_back(row);
    }
}