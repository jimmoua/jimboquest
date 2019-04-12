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
      TITLE,
      NONE // for when exit
    };

    enum class MAP {
      TEST_MAP00,
      TEST_MAP01,
      TEST_MAP02,
    };

    /* use these for std::map for img path */
    enum class img {
      TS_BG
    };

    void init();

    sf::Text createString(const std::string,  // string name
                          const ushort,       // text size
                          const sf::Color,    // fill color
                          const sf::Color,    // outline color
                          const float);       // outline thickness

    void setTxtOriginCenter(sf::Text&);
  }
}
