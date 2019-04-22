#pragma once
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
      TEST_MAP00,
      TEST_MAP01,
      TEST_MAP02,
    };

    /* use these for std::map for img path */
    enum class img {
      TS_BG,
      ACTOR_PNG,
    };

    void init();

    sf::Text createString(const std::string,  // string name
                          const ushort,       // text size
                          const sf::Color,    // fill color
                          const sf::Color,    // outline color
                          const float);       // outline thickness

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

  }

}
