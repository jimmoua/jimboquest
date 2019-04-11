#include "game.hpp"

namespace {
}

void game::init() {
  game::win::init();
}

void game::run() {
  while(win::getWin()->isOpen()) {
    /* Handle some game states here */
  }
}
