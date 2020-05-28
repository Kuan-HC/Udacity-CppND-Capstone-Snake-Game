#include "snake.h"
#include <iostream>
#include <vector>

class Auto_snake : public Snake
{
public:
    void Update() override;
    Auto_snake(int grid_width, int grid_height, int num) : Snake(grid_width, grid_height, num)
    {
        std::cout << "Build auto snke" << std::endl;
        speed = 0.15f;
    }

    void record_food(const SDL_Point &position);
    bool update_path{false};

private:
    Direction _last_direction_state{unknown};
    SDL_Point _food{0, 0};
    /*
    template <typename T>
    void vector_init(T default_val, std::vector<std::vector<T> > &grid_name, int width, int height);   
    */
    bool path_search(std::vector<std::vector<Direction>> &direction_arr, const SDL_Point &food, const SDL_Point &head, int &&grid_width, int &&grid_height);

    struct Delta
    {
        int x;
        int y;
        Direction action;
    };

    struct Search_Pt
    {
    public:
        Search_Pt() : x(-1), y(-1){};
        Search_Pt(int current_x, int current_y) : x(current_x), y(current_y){};
        /*member*/
        int x;
        int y;
        int cost{0};
        bool visited{false};
        Direction action{unknown};
        SDL_Point parent{-1, -1};
        /* member function */
        bool operator<(Search_Pt const &a) const
        {
            return (cost > a.cost) ? true : false;
        }
    };

    std::vector<Delta> delta_list = {{0, -1, kUp}, {0, 1, kDown}, {-1, 0, kLeft}, {1, 0, kRight}}; /*move: up, down, left, right */
};

/*
template <typename T>
void Auto_snake::vector_init(T default_val, std::vector<std::vector<T> > &grid_name, int width, int height)
{
    std::vector<T> row(width,default_val);
    for (int index = 0; index < height;  ++index)
    {
        grid_name.push_back(row);
    }
}
*/