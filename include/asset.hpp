#ifndef ASSET_HPP
#define ASSET_HPP
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <map>
#include <string>

using ushort = unsigned short int;

namespace game {

  namespace asset {
    /* GS = Game states */
    enum class GS {
      DEBUG,
      NONE, // for when exit
      TITLE,
    };

    enum class MAP {
      NONE,
      TEST_MAP00,
      TEST_MAP01,
      TEST_MAP02,
    };

    /* use these for std::map for img path */
    enum class img {
      TS_BG,
      ACTOR_PNG,
    };

    /* use these for sound effects */
    enum class snd {
      MENU_HOVER,
      MENU_SUBMIT,
      MENU_CANCEL,
      MENU_APPEAR,
      MENU_DISAPPEAR,
      FOOTSTEPS_GRASS,
    };

    enum class MUSIC {
      TITLESCREEN,
      AMBI_WIND,
    };

    enum class ENTITY_FACE {
      PLAYER,
    };

    void init();

    sf::Text createString(const std::string, const float); // string name

    sf::Text createString(const std::string); // string name

    sf::Text createString(const std::string,  // string name
                          const ushort,       // text size
                          const sf::Color,    // fill color
                          const sf::Color,    // outline color
                          const float);       // outline thickness

    /* Sets the origin of the image to the center */
    template<typename SFML_T>
      void setOriginCenter(SFML_T& t) {
        t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2,
                    t.getGlobalBounds().top + t.getGlobalBounds().height/2);
      }

    sf::Texture& mapTexture();
    sf::Texture& actorTexture();

    namespace entity {
      enum class RACE {
        HUMAN,
        ELF,
        GIANT,
        MONSTER,
      };
      enum class BASE_CLASS {
        WARRIOR,
        ROGUE,
        ARCHER,
        MAGE,
      };
    }

    const std::string getMapName(const game::asset::MAP&);

    sf::Sound& getSound(const snd&);

    sf::Music& getMusic(const MUSIC&);

    void MusicClean();

    sf::Sprite& getFaceSprite(const ENTITY_FACE&);

    namespace monster {
      /* This init will load all the monster sprite locations */
      void init();
      sf::Texture& getTexture_Slimes();
    }

  } // end of asset namespace

}

#endif
