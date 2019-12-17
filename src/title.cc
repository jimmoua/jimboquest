#include "title.hpp"
#include <ui.hpp>
#include <thread>
#include "game.hpp"

namespace {


  enum class choices {
    START,LOAD,EXIT
  };

  // _counter corresponds to integer value of casted choices above
  static int _counter = 0;


  static void _run() {
    auto& UI = game::ui::getUI(game::ui::ENUM_UI::TITLESCREEN);

    UI.ui_texts[static_cast<int>(choices::START)].setFillColor(sf::Color::White);
    UI.ui_texts[static_cast<int>(choices::LOAD)].setFillColor(sf::Color::White);
    UI.ui_texts[static_cast<int>(choices::EXIT)].setFillColor(sf::Color::White);
    UI.ui_texts[_counter].setFillColor(sf::Color::Yellow);

    while(game::win::getWin().pollEvent(game::win::getEv())) {
      if(game::win::getEv().type == sf::Event::Closed) {
        game::setGS(game::asset::GS::NONE);
      }
      if(game::win::getEv().type == sf::Event::KeyPressed) {
        switch(game::win::getEv().key.code) {
          case sf::Keyboard::S:
            game::asset::getSound(game::asset::snd::MENU_HOVER).play();
            _counter++;
            if(_counter > static_cast<int>(choices::EXIT))
              _counter = static_cast<int>(choices::START);
            break;
          case sf::Keyboard::W:
            game::asset::getSound(game::asset::snd::MENU_HOVER).play();
            _counter--;
            if(_counter < static_cast<int>(choices::START))
                _counter = static_cast<int>(choices::EXIT);
            break;
          case sf::Keyboard::J:
            game::asset::getSound(game::asset::snd::MENU_SUBMIT).play();
            if(_counter == static_cast<int>(choices::START)) {
              game::setGS(game::asset::GS::INGAME);
            }
            else if(_counter == static_cast<int>(choices::LOAD)) {
              // load a game file
              std::clog << "Load file not implemented yet!\n";
            }
            else if(_counter == static_cast<int>(choices::EXIT)) {
              // exit game
              game::setGS(game::asset::GS::NONE);
            }
          default: break;
        }
      }
    }
    game::win::getWin().clear(sf::Color::Black);
    game::ani::particleEffect();
    game::ui::getUI(game::ui::ENUM_UI::TITLESCREEN).drawUIsprites();
    for(auto& iter : UI.ui_texts) {
      game::win::getWin().draw(iter);
    }
    game::win::display();
  }

}

void game::title::init() {
  _counter = 0;
  //asset::getMusic(asset::MUSIC::AMBI_WIND).setPlayingOffset(sf::seconds(5));
  //asset::getMusic(asset::MUSIC::AMBI_WIND).setLoop(true);
  //asset::getMusic(asset::MUSIC::AMBI_WIND).setVolume(50);
  //asset::getMusic(asset::MUSIC::TITLESCREEN).setLoop(true);
  //asset::getMusic(asset::MUSIC::AMBI_WIND).play();
  //asset::getMusic(asset::MUSIC::TITLESCREEN).play();
  game::ani::fadeIn();
  while(game::getGS() == asset::GS::TITLE) {
    _run();
  }
}
