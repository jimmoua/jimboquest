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
  static sf::Text _debug = game::asset::createString("Debug", 36,
                                                     sf::Color::White,
                                                     sf::Color::Black,
                                                     3.0f);

  static unsigned short int _counter = 0; /* 1 = start
                                             2 = load
                                             3 = exit
                                             4 = debug */


  static void _run() {
    if(_counter == 0) {
      _start.setFillColor(sf::Color::Yellow);
      _load.setFillColor(sf::Color::White);
      _exit.setFillColor(sf::Color::White);
      _debug.setFillColor(sf::Color::White);
    }
    else if(_counter == 1) {
      _start.setFillColor(sf::Color::White);
      _load.setFillColor(sf::Color::Yellow);
      _exit.setFillColor(sf::Color::White);
      _debug.setFillColor(sf::Color::White);
    }
    else if(_counter == 2) {
      _start.setFillColor(sf::Color::White);
      _load.setFillColor(sf::Color::White);
      _exit.setFillColor(sf::Color::Yellow);
      _debug.setFillColor(sf::Color::White);
    }
    else if(_counter == 3) {
      _start.setFillColor(sf::Color::White);
      _load.setFillColor(sf::Color::White);
      _exit.setFillColor(sf::Color::White);
      _debug.setFillColor(sf::Color::Yellow);
    }

    while(game::win::getWin().pollEvent(game::win::getEv())) {
      if(game::win::getEv().type == sf::Event::Closed) {
        game::setGS(game::asset::GS::NONE);
      }
      if(game::win::getEv().type == sf::Event::KeyPressed) {
        switch(game::win::getEv().key.code) {
          case sf::Keyboard::S:
            game::asset::getSound(game::asset::snd::MENU_HOVER).play();
            if(_counter == 3) {
              _counter = 0;
            }
            else {
              _counter++;
            }
            break;
          case sf::Keyboard::W:
            game::asset::getSound(game::asset::snd::MENU_HOVER).play();
            if(_counter == 0) {
              _counter = 3;
            }
            else {
              _counter--;
            }
            break;
          case sf::Keyboard::J:
            game::asset::getSound(game::asset::snd::MENU_SUBMIT).play();
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
            else if(_counter == 3) {
              game::setGS(game::asset::GS::DEBUG);
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
    game::win::getWin().draw(_debug);
    game::win::getWin().display();
  }

}

void game::title::init() {
  const int mid_x = win::getRes_x()/2;
  const int mid_y = win::getRes_y()/2;
  asset::setOriginCenter(_start);
  asset::setOriginCenter(_load);
  asset::setOriginCenter(_exit);
  asset::setOriginCenter(_debug);
  _start.setPosition(mid_x, mid_y - 70);
  _load.setPosition(mid_x, mid_y);
  _exit.setPosition(mid_x, mid_y + 70);
  _debug.setPosition(mid_x, mid_y + 140);
  asset::getMusic(asset::MUSIC::AMBI_WIND).setPlayingOffset(sf::seconds(5));
  asset::getMusic(asset::MUSIC::AMBI_WIND).setLoop(true);
  asset::getMusic(asset::MUSIC::TITLESCREEN).setLoop(true);
  asset::getMusic(asset::MUSIC::AMBI_WIND).play();
  asset::getMusic(asset::MUSIC::TITLESCREEN).play();
  while(game::getGS() == asset::GS::TITLE) {
    _run();
  }
}
