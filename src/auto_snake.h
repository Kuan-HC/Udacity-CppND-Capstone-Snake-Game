#include "snake.h"
#include <iostream>
#include <vector>

class Auto_snake : public Snake
{
    public: 
    void Update()override;
    Auto_snake(int grid_width, int grid_height, int num):Snake(grid_width, grid_height, num)
    {
        std::cout << "Build auto snke" << std::endl;
        vector_init<int>(0, grid, grid_width, grid_height);
    }   

    private:
    typedef struct
    {
        int x;
        int y;
        Direction action;
    } Delta;

    template <typename T>
    void vector_init(T default_val, std::vector<std::vector<T> > &grid_name, int width, int height);   

    void UpdateBody(const SDL_Point *current_head_cell, SDL_Point &prev_head_cell)override;

    std::vector<std::vector<int> > grid;
    std::vector<std::vector<int> > value;
    std::vector<std::vector<Direction> > direction_arr;
    std::vector<Delta> delta_list = {{0, -1, kUp}, {0, 1, kDown }, {-1, 0, kLeft}, {1, 0, kRight}}; /*move: up, down, left, right */

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