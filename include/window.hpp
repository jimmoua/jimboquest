#pragma once
#include <SFML/Graphics.hpp>

namespace game {
  namespace win {
    void init();
    sf::RenderWindow*& getWin();
    sf::Event& getEv();
    const unsigned short int& getRes_x();
    const unsigned short int& getRes_y();
  }
}
