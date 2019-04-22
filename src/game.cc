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
        game::entity::getPl() = new entity::Player("Jimbo",
                                                   100,
                                                   100,
                                                   20,
                                                   10,
                                                   30);
        game::entity::getPl()->m_enSprite.setPosition(_SLOC*2, _SLOC*2);
        while(game::getGS() == asset::GS::DEBUG) {
          /* Draw map first layer -> draw character -> draw third layer
           * The second layer will not matter because we can't see it anyways
           * (collision layer) */
          map::displayMap();
          win::getWin().draw(game::entity::getPl()->m_enSprite);
          entity::getPl()->handleMove(map::getColSpr());
          win::getWin().display();
        }
        delete game::entity::getPl();
    }
  }
}

const game::asset::GS& game::getGS() {
  return _currentGS;
}

void game::setGS(const game::asset::GS g) {
  _currentGS = g;
}
