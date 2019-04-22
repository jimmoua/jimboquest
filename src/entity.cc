#include "entity.hpp"

namespace {
  static game::entity::Player* _Player = nullptr;
}

game::entity::Player*& game::entity::getPl() {
  return _Player;
}

game::entity::Entity::Entity() { }

/* User defined ctor for class Entity */
game::entity::Entity::Entity(const std::string& s,
                             const int& h,
                             const int& m,
                             const int& str,
                             const int& dex,
                             const int& _int)
{
  this->m_Name = s;
  this->m_Health = h;
  this->m_Mana = m;
  this->m_Str = str;
  this->m_Dex = dex;
  this->m_Int = _int;
  this->m_enSprite.setTexture(game::asset::actorTexture());
}

game::entity::Player::Player() { }

game::entity::Player::Player(const std::string& n,
                             const int& h,
                             const int& m,
                             const int& str,
                             const int& dex,
                             const int& _int)
{
  Entity(n, h, m, str, dex, _int);
  this->m_enSprite.setTexture(game::asset::actorTexture());
  this->m_enSprite.setTextureRect(sf::IntRect(00,00,16,16));
  this->m_enSprite.scale(SPRITE_SCALE-2, SPRITE_SCALE-2);
}

void game::entity::Player::handleMove(std::vector<std::vector<sf::Sprite>>&v) {
  /* Because I hit the character limit above, v stands for the collision
   * sprites that are not seeable. I need this sprite so I can check if the
   * character has hit a collision after the character has been moved. */
  constexpr float ms = 3;
  const sf::Vector2f good = this->m_enSprite.getPosition();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    this->m_enSprite.move(0, -ms);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    this->m_enSprite.move(0, ms);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->m_enSprite.move(-ms, 0);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    this->m_enSprite.move(ms, 0);
  }
  for(const auto& i : v) {
    for(const auto& j : i) {
      if(m_enSprite.getGlobalBounds().intersects(j.getGlobalBounds())) {
        this->m_enSprite.setPosition(good.x, good.y);
        std::cout << "Intersects!\n";
      }
    }
  }
}
