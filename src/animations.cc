#include "animations.hpp"
#include "game.hpp"
#include "window.hpp"
#include "asset.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "animations.hpp"

namespace {
  static sf::RectangleShape r;
  static sf::Clock fadeClock;
}

void game::ani::fadeOut() {
  r.setPosition(win::getWin().getView().getCenter().x-win::getRes_x()/2, win::getWin().getView().getCenter().y-win::getRes_y()/2);
  r.setSize(sf::Vector2f(win::getWin().getSize().x+40, win::getWin().getSize().y+40));
  fadeClock.restart();
  for(float alpha = 0.f; alpha <= 100;)
  {
    if(fadeClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(10).asMilliseconds())
    {
      fadeClock.restart();
      alpha+=3.f;
      r.setFillColor(sf::Color(0, 0, 0, alpha));
      win::getWin().draw(r);
      win::getWin().display();
    }
  }
  r.setFillColor(sf::Color(0,0,0,0));
}

