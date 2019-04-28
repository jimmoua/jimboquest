#ifndef UI_HPP
#define UI_HPP
#include "asset.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace game {
  namespace ui {

    /* enum class of UI */
    enum class ENUM_UI {
      TITLESCREEN,
      IN_GAME,
      IN_GAME_PLAYER_STATUS,
    };

    void init();

    /* When in game, we will want to press escape key to access menu and see
     * pretty things */

    /* When dealing with menus, often, we will "chain" menus together. One
     * menu can lead to another menu, and stepping out of a menu can go to
     * previous menus and yada yada. */
    struct UI {

      std::vector<sf::RectangleShape> menu_sprite;  // The sprite behind text
      std::vector<sf::Text>   ui_texts;

      UI() {
        /* The default ctor will create the UI */
        this->menu_sprite.resize(2);
        for(auto& i : this->menu_sprite) {
          i.setFillColor(sf::Color::Blue);
          i.setOutlineColor(sf::Color::White);
          i.setOutlineThickness(3.f);
        }
      }

      void set_menuSpritesOrigin() {
        for(auto& i : this->menu_sprite) {
          asset::setOriginCenter(i);
        }
      }
      void set_menuTextsOrigin();
      void set_menuTextsCenterOfUI();
      void set_menuPositionToCen();
      void drawUIsprites();
      void drawUItexts();

    }; // of struct

    UI& getUI(const ENUM_UI&);

  } // end of namespace ui
}

#endif /* UI_HPP */
