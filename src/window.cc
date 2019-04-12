#include "window.hpp"

namespace {
  static sf::RenderWindow _win;
  static sf::Event _eve;
  constexpr unsigned short int res_x = 640;
  constexpr unsigned short int res_y = 480;
}

const unsigned short int& game::win::getRes_x() {
  return res_x;
}

const unsigned short int& game::win::getRes_y() {
  return res_y;
}

void game::win::init() {
  _win.create(sf::VideoMode(res_x, res_y), "Jimbo Quest", sf::Style::Close);
  _win.setFramerateLimit(60u);
}

sf::RenderWindow& game::win::getWin() {
  return _win;
}

sf::Event& game::win::getEv() { return _eve; }
