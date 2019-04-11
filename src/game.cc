#include "game.hpp"

namespace {
}

void game::init() {
  // Init everything that needs to be init here
  game::win::init();
  game::asset::init();
}

void game::run() {
  while(win::getWin()->isOpen()) {
    /* Handle some game states here */
  }
}
