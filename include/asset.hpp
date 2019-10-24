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
    ////////////////////////////////////////////////// 
    //                GAME STATES
    ////////////////////////////////////////////////// 
    enum class GS {
      DEBUG,
      NONE, // for when exit
      TITLE,
    };

    ////////////////////////////////////////////////// 
    //                 MAP ENUMS
    ////////////////////////////////////////////////// 
    enum class MAP {
      NONE,
      TEST_MAP00,
      TEST_MAP01,
      TEST_MAP02,
    };

    ////////////////////////////////////////////////// 
    //      ENUMS FOR IMAGE PATH FOR std::map
    ////////////////////////////////////////////////// 
    enum class img {
      TS_BG,
      ACTOR_PNG,
    };

    ////////////////////////////////////////////////// 
    //   SOUND EFFECTS ENUM FOR USE WITH std::map
    ////////////////////////////////////////////////// 
    enum class snd {
      MENU_HOVER,
      MENU_SUBMIT,
      MENU_CANCEL,
      MENU_APPEAR,
      MENU_DISAPPEAR,
      FOOTSTEPS_GRASS,
    };

    ////////////////////////////////////////////////// 
    //       MUSIC ENUM FOR USE WITH std::map
    ////////////////////////////////////////////////// 
    enum class MUSIC {
      TITLESCREEN,
      AMBI_WIND,
    };

    ////////////////////////////////////////////////// 
    //            FACE IMAGE FOR ACTORS
    ////////////////////////////////////////////////// 
    enum class ENTITY_FACE {
      PLAYER,
    };

    ////////////////////////////////////////////////// 
    //            INITIALIZER FUNCTION
    ////////////////////////////////////////////////// 
    void init();

    ////////////////////////////////////////////////// 
    // Function Description
    // Returns an sf::Text that matches the parameters.
    //
    // The second parameter is text size.
    ////////////////////////////////////////////////// 
    sf::Text createString(const std::string, const float); // string name

    ////////////////////////////////////////////////// 
    // Function Description
    // Returns sf::Text with string. Creates the text
    // with whatever default defined value for the size
    // the text is.
    //
    // Check the function in the implementation file
    // to see the default text size.
    ////////////////////////////////////////////////// 
    sf::Text createString(const std::string);

    ////////////////////////////////////////////////// 
    // Function Description
    // Returns sf::Text of string with parameters
    // matching the below (read it).
    ////////////////////////////////////////////////// 
    sf::Text createString(const std::string,  // string name
                          const ushort,       // text size
                          const sf::Color,    // fill color
                          const sf::Color,    // outline color
                          const float);       // outline thickness

    ////////////////////////////////////////////////// 
    // Function Description
    // Sets whatever sf::Shape origin to its center
    ////////////////////////////////////////////////// 
    template<typename SFML_T>
      void setOriginCenter(SFML_T& t) {
        t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2,
                    t.getGlobalBounds().top + t.getGlobalBounds().height/2);
      }

    ////////////////////////////////////////////////// 
    // Returns a map texture.
    ////////////////////////////////////////////////// 
    sf::Texture& mapTexture();

    ////////////////////////////////////////////////// 
    // Returns an actor texture.
    ////////////////////////////////////////////////// 
    sf::Texture& actorTexture();

    namespace entity {
    }

    ////////////////////////////////////////////////// 
    // Returns a map name from an std::map given an
    // ENUM key
    ////////////////////////////////////////////////// 
    const std::string getMapName(const game::asset::MAP&);

    ////////////////////////////////////////////////// 
    // Returns a sound given a snd ENUM
    ////////////////////////////////////////////////// 
    sf::Sound& getSound(const snd&);

    ////////////////////////////////////////////////// 
    // Returns music given MUSIC ENUM
    ////////////////////////////////////////////////// 
    sf::Music& getMusic(const MUSIC&);

    ////////////////////////////////////////////////// 
    // Destroys the music that was dynamically loaded.
    ////////////////////////////////////////////////// 
    void MusicClean();

    sf::Sprite& getFaceSprite(const ENTITY_FACE&);

    namespace monster {
      ////////////////////////////////////////////////// 
      // Init function loads all the monster sprites
      // and textures.
      ////////////////////////////////////////////////// 
      void init();
      sf::Texture& getTexture_Slimes();
    }

  } // end of asset namespace

}

#endif
