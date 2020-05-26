#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
 #ifdef PLAYER
  void HandleInput(bool &running, Snake &snake) const;
#else
  void HandleInput_for_test(bool &running) const;
#endif
 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

};

#endif