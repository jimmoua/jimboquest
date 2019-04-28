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

void game::ani::fadeInMAP() {
  r.setPosition(win::getWin().getView().getCenter().x-win::getRes_x()/2, win::getWin().getView().getCenter().y-win::getRes_y()/2);
  r.setSize(sf::Vector2f(win::getWin().getSize().x+40, win::getWin().getSize().y+40));
  fadeClock.restart();
  for(float alpha = 255.f; alpha >= 0;)
  {
    /**/
    win::getWin().clear();

    auto drawLayers = [](std::vector<std::vector<sf::Sprite>>& s) -> void{
      for(auto& i : s) {
        for(auto& j : i) {
          win::getWin().draw(j);
        }
      }
    };

    drawLayers(map_ns::getMapObjectByID(map_ns::getCurrentMapID())->_map_lay01_S);
    drawLayers(map_ns::getMapObjectByID(map_ns::getCurrentMapID())->_map_lay02_S);
    drawLayers(map_ns::getMapObjectByID(map_ns::getCurrentMapID())->_map_lay03_S);
    drawLayers(map_ns::getMapObjectByID(map_ns::getCurrentMapID())->_mapEvV);
    sf::View v;
    v.setSize(win::getRes_x(), win::getRes_y());
    v.setCenter(entity::getPl().m_enSprite.getPosition());
    win::getWin().setView(v);
    win::getWin().draw(entity::getPl().m_enSprite);
    /**/
    if(fadeClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(10).asMilliseconds())
    {
      fadeClock.restart();
      alpha-=60.f;
      r.setFillColor(sf::Color(0, 0, 0, alpha));
      win::getWin().draw(r);
      win::getWin().display();
    }
  }
  r.setFillColor(sf::Color(0,0,0,0));
}

void game::ani::fadeIn() {
  r.setPosition(win::getWin().getView().getCenter().x-win::getRes_x()/2, win::getWin().getView().getCenter().y-win::getRes_y()/2);
  r.setSize(sf::Vector2f(win::getWin().getSize().x+40, win::getWin().getSize().y+40));
  fadeClock.restart();
  for(float alpha = 255.f; alpha >= 0;)
  {
    if(fadeClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(10).asMilliseconds())
    {
      fadeClock.restart();
      alpha-=60.f;
      r.setFillColor(sf::Color(0, 0, 0, alpha));
      win::getWin().draw(r);
      win::getWin().display();
    }
  }
  r.setFillColor(sf::Color(0,0,0,0));
}
