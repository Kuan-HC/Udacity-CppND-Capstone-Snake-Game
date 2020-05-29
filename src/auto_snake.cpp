#include "auto_snake.h"

#include "calibration.h"

extern std::mutex mutlock;

void Auto_snake::record_food(const SDL_Point &position)
{
    _food.x = position.x;
    _food.y = position.y;
}

void Auto_snake::Update(const std::deque<SDL_Point> &other_body)
{
    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)}; // We first capture the head's cell before updating.
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)}; // Capture the head's cell after updating.

    //Update all of the body vector items if the snake head has moved to a new cell

    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y || update_path == true)
    {
        update_path = false;
        UpdateBody(&current_cell, prev_cell, other_body);
        /*snake and auto_snake body has record in Snake::grid by function UpdateBody */
        std::vector<std::vector<Direction>> direction_arr(height, std::vector<Direction>(width, unknown));
        bool path_set = false;
        path_set = path_search(direction_arr, _food, current_cell, width, height);
        direction = direction_arr[current_cell.x][current_cell.y];

        if (unknown != direction)
        {
            _last_direction_state = direction;
        }

        /* can't find any path, keep the last meanful direction to suicide */
        if (path_set != true)
        {
            direction = _last_direction_state;
        }
    }
}

bool Auto_snake::path_search(std::vector<std::vector<Direction>> &direction_arr, const SDL_Point &food, const SDL_Point &head, int &&grid_width, int &&grid_height)
{
    /* initialize parameters */
    bool find_path = false;
    std::unique_lock<std::mutex> lock_obj(mutlock);
    std::vector<std::vector<Search_Pt>> close_mtx(grid_height, std::vector<Search_Pt>(grid_width));
    std::vector<Search_Pt> open_list;

    /* set first point*/
    Search_Pt start(head.x, head.y);
    open_list.emplace_back(start);
    close_mtx[head.x][head.y].visited = true;
    /* Following is not necessary but better for debugging */
    close_mtx[head.x][head.y].x = head.x;
    close_mtx[head.x][head.y].y = head.y;

    /* start searching*/
    while (!open_list.empty())
    {
        sort(open_list.begin(), open_list.end());

        Search_Pt P2expand = open_list.back();
        open_list.pop_back();

        if (P2expand.x == food.x && P2expand.y == food.y)
        {
            find_path = true;
            break;
        }
        else
        {

            for (auto &move : delta_list)
            {
                int next_x = P2expand.x + move.x;
                int next_y = P2expand.y + move.y;

                if (next_x >= 0 && next_x < grid_height && next_y >= 0 && next_y < grid_width && Snake::grid[next_x][next_y] != true && close_mtx[next_x][next_y].visited != true)
                {
                    close_mtx[next_x][next_y].cost = P2expand.cost + 1U;
                    close_mtx[next_x][next_y].parent.x = P2expand.x;
                    close_mtx[next_x][next_y].parent.y = P2expand.y;
                    close_mtx[next_x][next_y].action = move.action;
                    close_mtx[next_x][next_y].x = next_x;
                    close_mtx[next_x][next_y].y = next_y;

                    open_list.emplace_back(close_mtx[next_x][next_y]);
                    close_mtx[next_x][next_y].visited = true;
                }
                //lock_obj.unlock();
            }
        }
    }
    if (find_path == true)
    {
        Search_Pt *current = &close_mtx[food.x][food.y];

        while (current->x != start.x || current->y != start.y)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            direction_arr[current->parent.x][current->parent.y] = current->action;
            current = &close_mtx[current->parent.x][current->parent.y];
        }
    }

    return find_path;
}