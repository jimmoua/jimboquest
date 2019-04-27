#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

namespace game {
  namespace win {
    void init();
    sf::RenderWindow& getWin();
    sf::Event& getEv();
    const unsigned short int& getRes_x();
    const unsigned short int& getRes_y();
    void fadeOut();
    void fadeIn();
  }
}
#endif
