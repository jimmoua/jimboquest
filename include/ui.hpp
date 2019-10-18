#ifndef UI_HPP
#define UI_HPP
#include "asset.hpp"
#include "window.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>

namespace game {
  namespace ui {

    /* Title: sprite_menu creations
     * There are two sprite_menu that are very important when considering that
     * blue UI. Or whatever color I may change it to in the future. It is that
     * when we make our sprites, the second sprite_menu in the vector is a
     * little smaller so that we can create a border effect. In order to do
     * this, multiple in the parameter by the ui_SF_* in order to set the size properly.
     * 
     *   someUI.sprite_menu[0].setSize(game::win::getRes_X, game::win::getRex_Y);
     *   someUI.sprite_menu[1].setSize(someUI.sprite_menu[0].getSize().x*ui_SF_x, someUI.sprite_menu[0].getSize().y*ui_SF_y);
     */
    static constexpr float ui_SF_x = 0.95;
    static constexpr float ui_SF_y = 0.93;

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
        /* The default ctor will create the UI. It does not specify the size, so
         * when creating UI, we must specify the size of the UI window. */
        this->menu_sprite.resize(2);
        for(auto& i : this->menu_sprite) {
          i.setFillColor(sf::Color::Blue);
          i.setOutlineColor(sf::Color::White);
          i.setOutlineThickness(3.f);
        }
      }
      
      void anotherOne() {
        sf::RectangleShape t;
        t.setFillColor(sf::Color::Blue);
        t.setOutlineColor(sf::Color::White);
        t.setOutlineThickness(3.f);
        this->menu_sprite.push_back(t);
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


namespace game {
  namespace entity {
    void updatePlayerStatusUI();
  }
}


#endif /* UI_HPP */
