#include "title.hpp"
#include <ui.hpp>

namespace {

  static unsigned short int _counter = 0; /* 1 = start
                                             2 = load
                                             3 = exit
                                             4 = debug */


  static void _run() {
    auto& UI = game::ui::getUI(game::ui::ENUM_UI::TITLESCREEN);
    if(_counter == 0) {
      UI.ui_texts[0].setFillColor(sf::Color::Yellow);
      UI.ui_texts[1].setFillColor(sf::Color::White);
      UI.ui_texts[2].setFillColor(sf::Color::White);
      UI.ui_texts[3].setFillColor(sf::Color::White);
    }
    else if(_counter == 1) {
      UI.ui_texts[0].setFillColor(sf::Color::White);
      UI.ui_texts[1].setFillColor(sf::Color::Yellow);
      UI.ui_texts[2].setFillColor(sf::Color::White);
      UI.ui_texts[3].setFillColor(sf::Color::White);
    }
    else if(_counter == 2) {
      UI.ui_texts[0].setFillColor(sf::Color::White);
      UI.ui_texts[1].setFillColor(sf::Color::White);
      UI.ui_texts[2].setFillColor(sf::Color::Yellow);
      UI.ui_texts[3].setFillColor(sf::Color::White);
    }
    else if(_counter == 3) {
      UI.ui_texts[0].setFillColor(sf::Color::White);
      UI.ui_texts[1].setFillColor(sf::Color::White);
      UI.ui_texts[2].setFillColor(sf::Color::White);
      UI.ui_texts[3].setFillColor(sf::Color::Yellow);
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
    game::ui::getUI(game::ui::ENUM_UI::TITLESCREEN).drawUIsprites();
    for(auto& iter : UI.ui_texts) {
      game::win::getWin().draw(iter);
    }
    game::win::getWin().display();
  }

}

void game::title::init() {
  asset::getMusic(asset::MUSIC::AMBI_WIND).setPlayingOffset(sf::seconds(5));
  asset::getMusic(asset::MUSIC::AMBI_WIND).setLoop(true);
  asset::getMusic(asset::MUSIC::TITLESCREEN).setLoop(true);
  asset::getMusic(asset::MUSIC::AMBI_WIND).play();
  asset::getMusic(asset::MUSIC::TITLESCREEN).play();
  while(game::getGS() == asset::GS::TITLE) {
    _run();
  }
}
