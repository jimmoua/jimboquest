#include "entity.hpp"
#include "game.hpp"

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

void game::entity::Player::handleMove(std::vector< std::vector<sf::Sprite> >&v,
                                      std::vector< std::vector<map_ns::mapEvStruct> >& d)
{
  /* v = collisions vector
   * d = portals vector
   *
   * Because I shall not violate the 79/80 character limit */

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
  auto pSpri = m_enSprite.getGlobalBounds();
  sf::FloatRect p = pSpri;
  p.height-=_SS*2;
  p.top+=_SS*2;
  for(const auto& i : v) {
    for(const auto& j : i) {
      if(p.intersects(j.getGlobalBounds())) {
        this->m_enSprite.setPosition(good.x, good.y);
      }
    }
  }
  /* Now check for portal interaction */
  for(const auto& i : d) {
    for(const auto& j : i) {
      if(p.intersects(j._mapEv_Sp.getGlobalBounds())) {
        std::cout << "PORTAL INTERATION\n";
      }
    }
  }
}
