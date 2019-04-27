#include "entity.hpp"
#include "game.hpp"
#include "map.hpp"
#include <tuple>

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

void game::entity::Player::handleMove() {

  static sf::Clock keyPressTimer;  // portal timer

  /* cV = collisions vector */
  auto cV = map_ns::getMapObjectByID(map_ns::getCurrentMapID())->_map_lay02_S;

  constexpr float ms = 3;
  const sf::Vector2f good = this->m_enSprite.getPosition();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    this->m_enSprite.move(0, -ms);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    this->m_enSprite.move(0, ms);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    this->m_enSprite.move(-ms, 0);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    this->m_enSprite.move(ms, 0);
  }

  auto pSpriteGB = m_enSprite.getGlobalBounds(); // gb of sprite
  /* Now check for intersection for collisions layer */

  for(const auto& i : cV) {
    for(const auto& j : i) {
      if(pSpriteGB.intersects(j.getGlobalBounds())) {
        this->m_enSprite.setPosition(good.x, good.y);
        /* need this return statement here or we will go on to check for portal
         * collisions as well, which we do want */
        return;
      }
    }
  }

  /* Check for portal collisiosn */
  auto* mapObj = map_ns::getMapObjectByID(map_ns::getCurrentMapID());
  auto evSp = mapObj->_mapEvV; // Sprites
  auto evSpInfo = mapObj->evV; // Struct info on event sprite (parallel arrays)
  for(int i = 0; i < mapObj->_mapSize.x; i++) {
    for(int j = 0; j < mapObj->_mapSize.y; j++) {

      if(pSpriteGB.intersects(evSp[i][j].getGlobalBounds())) {
        if(evSpInfo[i][j].ev == map_ns::TILE_EV::PORTAL) {
          map_ns::loadMap(evSpInfo[i][j].portalTransportLoc.first, evSpInfo[i][j].portalTransportLoc.second);
          std::cout << "Index: " << i << " " << j << std::endl;
        }
      }

    }
  }


} // end of handleMove function
