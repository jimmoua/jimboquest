#include "entity.hpp"
#include "game.hpp"
#include "map.hpp"
#include "animations.hpp"
#include <tuple>

namespace {

  static game::entity::Player _Player;

  #define O  4       // The character sprites that I am using have an offset
  #define O2 8
  #define X 24       // The character sprite is 24 px wide
  #define Y 16       // the character sprite is 16 px tall

  static std::map<game::entity::_facedirection_, const sf::IntRect*> _face_map_;

  const static sf::IntRect __PLAYER_UP__ [] = {
    sf::IntRect(X*0+O,Y*1,X-O2,Y),
    sf::IntRect(X*1+O,Y*1,X-O2,Y),
    sf::IntRect(X*2+O,Y*1,X-O2,Y),
  };
  const static sf::IntRect __PLAYER_DOWN__[] = {
    sf::IntRect(X*0+O,Y*5,X-O2,Y),
    sf::IntRect(X*1+O,Y*5,X-O2,Y),
    sf::IntRect(X*2+O,Y*5,X-O2,Y),
  };
  const static sf::IntRect __PLAYER_RIGHT__ [] = {
    sf::IntRect(X*0+O,Y*3,X-O2,Y),
    sf::IntRect(X*1+O,Y*3,X-O2,Y),
    sf::IntRect(X*2+O,Y*3,X-O2,Y),
  };
  const static sf::IntRect __PLAYER_LEFT__ [] = {
    sf::IntRect(X*0+O,Y*7,X-O2,Y),
    sf::IntRect(X*1+O,Y*7,X-O2,Y),
    sf::IntRect(X*2+O,Y*7,X-O2,Y),
  };
  #undef O
  #undef O2
  #undef X
  #undef Y
} // end of anon namespace

game::entity::Player& game::entity::getPl() {
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
                             const int& _int) :

                            Entity(n, h, m, str, dex, _int)
{
  this->m_enSprite.setTexture(game::asset::actorTexture());
  this->m_enSprite.setTextureRect(__PLAYER_DOWN__[0]);
#define SCALE_OFFSET 2
  this->m_enSprite.scale(SPRITE_SCALE-SCALE_OFFSET, SPRITE_SCALE-SCALE_OFFSET);
  this->m_enSprite.setOrigin(this->m_enSprite.getOrigin().x-SCALE_OFFSET,
                             this->m_enSprite.getOrigin().y-SCALE_OFFSET);
#undef SCALE_OFFSET
}

void game::entity::Player::handleMove() {

  static sf::Clock animationClock;

  auto animatePlayer = [this]() -> void {
    if(animationClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(300).asMilliseconds()) {
      this->m_enSprite.setTextureRect(_face_map_[this->f_getFaceDir()][0]);
      if(animationClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(600).asMilliseconds()) {
        this->m_enSprite.setTextureRect(_face_map_[this->f_getFaceDir()][1]);
        if(animationClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(900).asMilliseconds()) {
          this->m_enSprite.setTextureRect(_face_map_[this->f_getFaceDir()][2]);
            if(animationClock.getElapsedTime().asMilliseconds() >= sf::milliseconds(1200).asMilliseconds()) {
              this->m_enSprite.setTextureRect(_face_map_[this->f_getFaceDir()][1]);
              animationClock.restart();
            }
        }
      }
    }
  };

  static sf::Clock keyPressTimer;  // portal timer

  /* cV = collisions vector */
  auto cV = map_ns::getMapObjectByID(map_ns::getCurrentMapID())->_map_lay02_S;

  float ms = 3;
  const sf::Vector2f good = this->m_enSprite.getPosition();
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
    ms+=2; // speed boost
    asset::getSound(asset::snd::FOOTSTEPS_GRASS).setPitch(1.6);
  }
  else {
    asset::getSound(asset::snd::FOOTSTEPS_GRASS).setPitch(1.3);
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    if(asset::getSound(asset::snd::FOOTSTEPS_GRASS).getStatus() != sf::Sound::Status::Playing) {
      asset::getSound(asset::snd::FOOTSTEPS_GRASS).play();
    }
    if(this->f_getFaceDir() != _facedirection_::UP) {
      this->f_setFaceDir( _facedirection_::UP );
      this->m_enSprite.setTextureRect(__PLAYER_UP__[0]);
    }
    this->m_enSprite.move(0, -ms);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
    if(asset::getSound(asset::snd::FOOTSTEPS_GRASS).getStatus() != sf::Sound::Status::Playing) {
      asset::getSound(asset::snd::FOOTSTEPS_GRASS).play();
    }
    if(this->f_getFaceDir() != _facedirection_::DOWN) {
      this->m_enSprite.setTextureRect(__PLAYER_DOWN__[0]);
      this->f_setFaceDir( _facedirection_::DOWN );
    }
    this->m_enSprite.move(0, ms);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
    if(asset::getSound(asset::snd::FOOTSTEPS_GRASS).getStatus() != sf::Sound::Status::Playing) {
      asset::getSound(asset::snd::FOOTSTEPS_GRASS).play();
    }
    if(this->f_getFaceDir() != _facedirection_::LEFT) {
      this->m_enSprite.setTextureRect(__PLAYER_LEFT__[0]);
      this->f_setFaceDir( _facedirection_::LEFT );
    }
    this->m_enSprite.move(-ms, 0);
  }
  else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
    if(asset::getSound(asset::snd::FOOTSTEPS_GRASS).getStatus() != sf::Sound::Status::Playing) {
      asset::getSound(asset::snd::FOOTSTEPS_GRASS).play();
    }
    if(this->f_getFaceDir() != _facedirection_::RIGHT) {
      this->m_enSprite.setTextureRect(__PLAYER_RIGHT__[0]);
      this->f_setFaceDir( _facedirection_::RIGHT );
    }
    this->m_enSprite.move(ms, 0);
  }

  animatePlayer();

  auto pSpriteGB = m_enSprite.getGlobalBounds(); // gb of sprite
  pSpriteGB.height-=_SS*2;
  pSpriteGB.top+=_SS*2;

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
          //ani::fadeOut();
          map_ns::loadMap(evSpInfo[i][j].portalTransportLoc.first, evSpInfo[i][j].portalTransportLoc.second);
          //ani::fadeIn();
          std::cout << "Index: " << i << " " << j << std::endl;
        }
      }

    }
  }


} // end of handleMove function

void game::entity::init() {
  _face_map_[_facedirection_::UP]    = __PLAYER_UP__;
  _face_map_[_facedirection_::DOWN]  = __PLAYER_DOWN__;
  _face_map_[_facedirection_::LEFT]  = __PLAYER_LEFT__;
  _face_map_[_facedirection_::RIGHT] = __PLAYER_RIGHT__;
}
