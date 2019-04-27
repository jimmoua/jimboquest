#include "window.hpp"

namespace {
  static sf::RenderWindow _win;
  static sf::Event _eve;
  constexpr unsigned short int res_x = 1600;
  constexpr unsigned short int res_y = 900;
  static sf::RectangleShape r;
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
  
  /* Set window position to the top left of the screen */
  _win.setPosition(sf::Vector2i(100,100));
  //_win.setPosition(sf::Vector2i(0,0));

}

sf::RenderWindow& game::win::getWin() {
  return _win;
}

sf::Event& game::win::getEv() { return _eve; }

void game::win::fadeOut() {
  static sf::Clock fadeClock;
  r.setPosition(_win.getView().getCenter().x-res_x/2, _win.getView().getCenter().y-res_y/2);
  r.setSize(sf::Vector2f(res_x, res_y));
  sf::Clock c;
  fadeClock.restart();
  for(float alpha = 0.f; alpha <= 100;)
  {
    if(fadeClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(30).asMilliseconds())
    {
      fadeClock.restart();
      alpha+=3.f;
      r.setFillColor(sf::Color(0, 0, 0, alpha));
      _win.draw(r);
      _win.display();
    }
  }
}
