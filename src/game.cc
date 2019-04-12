#include "game.hpp"

namespace {
  // By default, state is in title screen
  static game::asset::GS _currentGS = game::asset::GS::TITLE;
}

void game::init() {
  // Init everything that needs to be init here
  game::win::init();
  game::asset::init();
}

void game::run() {
  while(win::getWin().isOpen()) {

    /* See if user wants to close game */
    while(win::getWin().pollEvent(win::getEv())) {
      if(win::getEv().type == sf::Event::Closed) {
        win::getWin().close();
      }
    }

    /* Handle some game states here */
    switch(_currentGS) {
      case game::asset::GS::TITLE:
        game::title::init();
        break;
      case game::asset::GS::NONE:
        if(game::win::getWin().isOpen()) {
          game::win::getWin().close();
        }
        break;
      case game::asset::GS::DEBUG:
        game::map::loadMap("data/map/testMap00.txt");
        while(game::getGS() == asset::GS::DEBUG) {
          map::displayMap();
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
