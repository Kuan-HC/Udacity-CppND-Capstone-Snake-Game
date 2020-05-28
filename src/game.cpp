#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game(const std::size_t &&grid_width, const std::size_t &&grid_height)

    : auto_snake(grid_width, grid_height, 0U),
#ifdef PLAYER
      snake(grid_width, grid_height, 1U),
#endif
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer, const std::size_t &&target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;
  auto_snake.GrowBody();
  while (running)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    frame_start = SDL_GetTicks();

// Input, Update, Render - the main game loop.
#ifdef PLAYER
    controller.HandleInput(running, snake);
#else
    controller.HandleInput_for_test(running);
#endif

    Update();

#ifdef PLAYER
    renderer.Render(snake, food);
#else
    renderer.Render(auto_snake, food);
#endif
    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
#ifdef PLAYER
      renderer.UpdateWindowTitle(score, frame_count);
#endif
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update()
{

  if (auto_snake.alive == false
#ifdef PLAYER
      || snake.alive == false
#endif
  )
  {
    return;
  }

#ifdef PLAYER
  std::future<void> update_snake = std::async(&Snake::Update, &snake);
  update_snake.wait();
#endif
  /* Auto_snake */
  auto_snake.record_food(food);
  auto_snake.Update();

  // Check if there's food over here
  //auto_snake.update_path = auto_snake.GetFood(food);
  if (auto_snake.GetFood(food) == true)
  {
    auto_snake.new_path();
    PlaceFood();
  }
#ifdef PLAYER
  else if (snake.GetFood(food) == true)
  {
    PlaceFood();
  }
#endif
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (
        !auto_snake.SnakeCell(x, y)
#ifdef PLAYER
        || !snake.SnakeCell(x, y)
#endif
    )
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}
#ifdef PLAYER
int Game::GetScore() const
{
  return score;
}
int Game::GetSize() const { return snake.size; }
#endif
