#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

namespace game {
  namespace win {
    void init();
    sf::RenderWindow& getWin();
    sf::Event& getEv();
    void display();
    const unsigned short int& getRes_x();
    const unsigned short int& getRes_y();
  }

  namespace ani {
    void fadeIn();
  }

}
#endif
