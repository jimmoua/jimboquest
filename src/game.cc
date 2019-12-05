#include "game.hpp"
#include "title.hpp"
#include "debug.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "ui.hpp"
#include "animations.hpp"
#include <thread>

namespace {
  // By default, state is in title screen
  static game::asset::GS _currentGS = game::asset::GS::TITLE;
  static std::vector<std::thread> __thread_vector__;
}

void game::init() {
  // Init everything that needs to be init here
  game::win::init();
  game::asset::init();
  game::ui::init();
  game::map_ns::init();
  game::entity::init();
}

void game::run() {
  while(win::getWin().isOpen()) {

    /* Handle some game states here */
    switch(_currentGS) {
      case game::asset::GS::TITLE:
      {
        game::title::init();
        break;
      }
      case game::asset::GS::NONE:
      {
        ani::fadeOut();
        if(game::win::getWin().isOpen()) {
          game::win::getWin().close();
        }
        break;
      }
      case game::asset::GS::DEBUG:
      {
        debug::run();
        break;
      }
    }
  }
}

const game::asset::GS& game::getGS() {
  return _currentGS;
}

void game::setGS(const game::asset::GS g) {
  _currentGS = g;
}

std::vector<std::thread>& game::thread_vector() {
  return __thread_vector__;
}

//int game::genRand(int min, int max) {
  //std::random_device rd;
  //std::mt19937 seed(rd());
  //std::uniform_int_distribution<> rand(min, max);
  //return static_cast<int>(rand(seed));
//}
