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


  /* Lambda that will create a particle */
  auto createParticle = []() -> std::pair<sf::CircleShape, float> {
    std::pair<sf::CircleShape, float> c;
    c.first.setFillColor(sf::Color::Yellow);
    c.first.setRadius(game::genRand(1, 3));
    /* Place the particles at the bottom right of the screen. We will then move
     * in directions to simulate a float effect */
    c.first.setPosition(game::genRand(0, win::getRes_x()), win::getRes_y());
    c.second = game::genRand(1,5);
    return c;
  };

  static std::vector<std::pair<sf::CircleShape, float>> particles;
  constexpr size_t maxParticles = 100;
  if(particles.size() < maxParticles) {
    static sf::Clock particleSpawnClock;
    if(particleSpawnClock.getElapsedTime().asMilliseconds() > sf::milliseconds(125).asMilliseconds()) {
      particleSpawnClock.restart();
      particles.push_back(createParticle());
    }
  }
  
  /* Move the particles */
  for(auto& iter : particles) {
    iter.first.move(0, -iter.second);
  }

  /* Create a vector to collect iterators on which particles have left outside
   * the window. */
  std::vector<std::vector<std::pair<sf::CircleShape, float>>::iterator> toDelete;
  for(auto iter = particles.begin(); iter != particles.end(); iter++) {
    if(iter->first.getPosition().y < 0 || iter->first.getPosition().y > win::getRes_y()) {
      toDelete.push_back(iter);
    }
  }

  /* Delete the particles that have gone out of bounds */
  for(auto iter = toDelete.begin(); iter != toDelete.end(); iter++) {
    particles.erase(*iter);
  }

  /* Draw the particles on the screen */
  for(auto& i : particles) {
    win::getWin().draw(i.first);
  }
}
