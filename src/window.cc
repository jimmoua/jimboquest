#include "window.hpp"
#include <thread>
#include "game.hpp"

namespace {
  static sf::RenderWindow _win;
  static sf::Event _eve;
  constexpr unsigned short int res_x = 1600;
  constexpr unsigned short int res_y = 900;

  /* The rectangle shape used for fade in effects. This animation effect is
   * special, so It will stay inside the scope of the window source file. */
  static sf::RectangleShape r;
  static sf::Clock fadeClock;

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
  _win.clear(sf::Color::Black);
  _win.display();

}

sf::RenderWindow& game::win::getWin() {
  return _win;
}

sf::Event& game::win::getEv() { return _eve; }

void game::win::display() {
  _win.draw(r);
  _win.display();
}

namespace {
  void __FADE_IN_FUNCTION__() {
    r.setPosition(_win.getView().getCenter().x-res_x/2, _win.getView().getCenter().y-res_y/2);
    r.setSize(sf::Vector2f(_win.getSize().x+40, _win.getSize().y+40));
    fadeClock.restart();
    for(float alpha = 255.f; alpha >= 0;)
    {
      if(fadeClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(10).asMilliseconds())
      {
        fadeClock.restart();
        alpha-=3.f;
        r.setFillColor(sf::Color(0, 0, 0, alpha));
      }
      if( alpha < 10 ) break;
    }
    r.setFillColor(sf::Color(0,0,0,0));
  }
}

void game::ani::fadeIn() {
  /* Delay the screen just a little before fading in */
  r.setFillColor(sf::Color::Black);
  _win.display();
  sf::sleep(sf::milliseconds(50));
  game::thread_vector().push_back(std::thread( __FADE_IN_FUNCTION__ ));
}
