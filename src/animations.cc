#include "animations.hpp"
#include "game.hpp"
#include "window.hpp"
#include "asset.hpp"
#include "map.hpp"
#include "entity.hpp"
#include "animations.hpp"
#include <random>

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

void game::ani::particleEffect() {
  /* This function is going to generate a particle effect. The reason for this
   * function is because I want to have some particles floating about in the
   * title screen to make it look less boring */

  /* Lambda that will create particles */
  auto createParticle = []() -> sf::CircleShape {
    sf::CircleShape c;
    c.setFillColor(sf::Color::Yellow);
    c.setRadius(2.0f);
    /* Place the particles at the bottom right of the screen. We will then move
     * in directions to simulate a float effect */
    c.setPosition(win::getWin().getSize().x, win::getWin().getSize().y);
    return c;
  };

  static std::vector<sf::CircleShape> particles;
  constexpr size_t maxParticles = 500;
  if(particles.capacity() != maxParticles) {
    particles.resize(maxParticles);
  }
  if(particles.size() != maxParticles) {
    for(size_t i = particles.size(); i < maxParticles; i++) {
      particles.push_back(createParticle());
    }
  }

  /* 1 = up left
   * 2 = straight up
   * 3 = up right */
  
  /* Move the particles */
  for(auto& iter : particles) {
    static std::random_device rd;
    std::mt19937 seed(rd());
    std::uniform_int_distribution<> rand(1, 2);
    auto dir = rand(seed);
    if(dir == 1) {
      iter.move(-1,-1);
    }
    else if(dir == 2) {
      iter.move(0, -.5);
    }
    else if(dir == 3) {
      iter.move(1, -1);
    }
  }

  for(auto iter = particles.begin(); iter!= particles.end(); iter++) {
    #define pos iter->getPosition()
    if(pos.x < 0 || pos.x > win::getRes_x() || pos.y < 0 || pos.y > win::getRes_y()) {
      particles.erase(iter);
    }
    #undef pos
  }

  /* Draw the particles on the screen */
  for(auto& i : particles) {
    win::getWin().draw(i);
  }


  /* After generating the particles, we will draw them */
  win::display();
}
