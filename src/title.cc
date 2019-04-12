#include "title.hpp"

namespace {
  static sf::Text _start = game::asset::createString("Start", 36,
                                                     sf::Color::Yellow,
                                                     sf::Color::Black,
                                                     3.0f);
  static sf::Text _load = game::asset::createString("Load", 36,
                                                     sf::Color::White,
                                                     sf::Color::Black,
                                                     3.0f);
  static sf::Text _exit = game::asset::createString("Exit", 36,
                                                     sf::Color::White,
                                                     sf::Color::Black,
                                                     3.0f);

  static unsigned short int _counter = 0; /* 1 = start
                                             2 = load
                                             3 = exit */


  static void _run() {
    if(_counter == 0) {
      _start.setFillColor(sf::Color::Yellow);
      _load.setFillColor(sf::Color::White);
      _exit.setFillColor(sf::Color::White);
    }
    else if(_counter == 1) {
      _start.setFillColor(sf::Color::White);
      _load.setFillColor(sf::Color::Yellow);
      _exit.setFillColor(sf::Color::White);
    }
    else if(_counter == 2) {
      _start.setFillColor(sf::Color::White);
      _load.setFillColor(sf::Color::White);
      _exit.setFillColor(sf::Color::Yellow);
    }

    while(game::win::getWin().pollEvent(game::win::getEv())) {
      if(game::win::getEv().type == sf::Event::Closed) {
        game::setGS(game::asset::GS::NONE);
      }
      if(game::win::getEv().type == sf::Event::KeyPressed) {
        switch(game::win::getEv().key.code) {
          case sf::Keyboard::S:
            if(_counter == 2) {
              _counter = 0;
            }
            else {
              _counter++;
            }
            break;
          case sf::Keyboard::W:
            if(_counter == 0) {
              _counter = 2;
            }
            else {
              _counter--;
            }
            break;
          case sf::Keyboard::Enter:
            if(_counter == 0) {
              // start game
              std::cout << "Not implemented yet...\n";
            }
            else if(_counter == 1) {
              // load a game file
              std::cout << "Not implemented yet...\n";
            }
            else if(_counter == 2) {
              game::setGS(game::asset::GS::NONE);
            }
          default:
            ;
        }
      }
    }
    game::win::getWin().clear(sf::Color::Black);
    game::win::getWin().draw(_start);
    game::win::getWin().draw(_load);
    game::win::getWin().draw(_exit);
    game::win::getWin().display();
  }

}

void game::title::init() {
  const int mid_x = win::getRes_x()/2;
  const int mid_y = win::getRes_y()/2;
  asset::setTxtOriginCenter(_start);
  asset::setTxtOriginCenter(_load);
  asset::setTxtOriginCenter(_exit);
  _start.setPosition(mid_x, mid_y - 70);
  _load.setPosition(mid_x, mid_y);
  _exit.setPosition(mid_x, mid_y + 70);
  while(game::getGS() == asset::GS::TITLE) {
    _run();
  }
}
