#include "game.hpp"

int main() {
  game::init();
  game::run();
  /* If we have threads going on, wait for them before closing the game */
  for(auto& i : game::thread_vector()) {
    if(i.joinable()) {
      i.join();
    }
  }
  game::asset::MusicClean();
  return 0;
}
