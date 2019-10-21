#include "debug.hpp"
#include "window.hpp"
#include "asset.hpp"
#include "entity.hpp"
#include "game.hpp"
#include "ui.hpp"
#include <thread>
#include "animations.hpp"

namespace {
  static bool in_uiMenu = false;
  static int menuCounter = 0;

  /* UI that shows up (ingame) when want to exit the game */
  static game::ui::UI exitUI;

  static void init();

  static void handleUI_Menu();
}

void game::debug::run() {

  /* For key presses */
  static sf::Clock keyPressTimer;
  //static int counter = 0;

  /* Create the player object */
  game::entity::getPl() = game::entity::Player("Erdrick",100,100,20,10,30);
  game::entity::updatePlayerStatusUI();
  std::cout << "Created player: " << game::entity::getPl().f_getName() << std::endl;

  /* Load the default map */
  game::map_ns::loadMap(game::asset::MAP::TEST_MAP00, sf::Vector2f(2, 2));

  /* Init the UIs for this game state */
  ::init();

  /* While the game setting is on DEBUG, run the game */
  /* handle view */
  while(game::getGS() == asset::GS::DEBUG) {

    win::getWin().clear(sf::Color::Black);
    game::entity::updatePlayerStatusUI();

    while(game::win::getWin().pollEvent(game::win::getEv())) {
      if(game::win::getEv().type == sf::Event::KeyPressed) {

        if(win::getEv().key.code == sf::Keyboard::Escape) {
          asset::getSound(asset::snd::MENU_APPEAR).play();

          /* By default, the first text will be highlighted */
          ui::getUI(ui::ENUM_UI::IN_GAME).ui_texts[0].setFillColor(sf::Color::Yellow);
          menuCounter = 0;   /* Reset the menu counter so it goes back to the
                                first text */
          in_uiMenu = true;  /* In the game menu */
          //ui::getUI(ui::ENUM_UI::IN_GAME).set_menuTextsOrigin(); // ← creates rendering issues





          /* Disabling this below makes the both text and window change */
          ui::getUI(ui::ENUM_UI::IN_GAME).set_menuPositionToCen();





          /* Disableing this below makes the window stay in the middle of the
           * screen, but the text changes positions...
           *
           * Fri Apr 26 11:32:55 CDT 2019
           * UPDATE: Leaving it here doesn't mess up the window anymore... What
           * keeps changing is the text. */
          ui::getUI(ui::ENUM_UI::IN_GAME).set_menuTextsCenterOfUI();



        } // end of escape key press

      }
      if(game::win::getEv().type == sf::Event::Closed) {
        game::setGS(asset::GS::NONE);
      }
    }

    static sf::View v;
    v.setSize(win::getRes_x(), win::getRes_y());
    v.setCenter(entity::getPl().m_enSprite.getPosition());
    win::getWin().setView(v);

    /* Draw map first layer -> draw character -> draw third layer The
     * second layer will not matter because we can't see it anyways
     * (collision layer) */
    map_ns::displayMap_L1();
    /* Drawing */
    win::getWin().draw(game::entity::getPl().m_enSprite);
    
    /* Handling movement will deal with collisions layer */
    entity::getPl().handleMove();
    while(in_uiMenu && game::getGS() == game::asset::GS::DEBUG) {
      handleUI_Menu();
    }

    win::display();
  }
}

namespace {

  static void handleUI_Menu() {

    static auto renderThings = [](game::ui::UI& UI_MENU, int& counter) {
      game::win::getWin().clear(sf::Color::Black);
      game::map_ns::displayMap_L1();
      game::win::getWin().draw(game::entity::getPl().m_enSprite);
      UI_MENU.game::ui::UI::drawUIsprites();
      /* COLOR TEXT */
      for(auto& i : UI_MENU.ui_texts) {
        i.setFillColor(sf::Color::White);
        if (counter != -1) {
          UI_MENU.ui_texts[counter].setFillColor(sf::Color::Yellow);
        }
      }
      UI_MENU.drawUItexts();
    };

    while(game::win::getWin().pollEvent(game::win::getEv())) {
      if(game::win::getEv().type == sf::Event::KeyPressed) {

        if(game::win::getEv().key.code == sf::Keyboard::Escape) {
          game::asset::getSound(game::asset::snd::MENU_DISAPPEAR).play();
          in_uiMenu = false;
          return;
        }

        /* Handle texts selection */
        if(game::win::getEv().key.code == sf::Keyboard::W) {
          /* There are 5 menu options, we start at 0 */
          game::asset::getSound(game::asset::snd::MENU_HOVER).play();
          if(menuCounter == 0) {
            menuCounter = 4;
            break;
          }
          menuCounter--;
        }
        if(game::win::getEv().key.code == sf::Keyboard::S) {
          game::asset::getSound(game::asset::snd::MENU_HOVER).play();
          if(menuCounter == 4) {
            menuCounter = 0;
            break;
          }
          menuCounter++;
        }
        if(game::win::getEv().key.code == sf::Keyboard::J) {
          game::asset::getSound(game::asset::snd::MENU_SUBMIT).play();
          // Player Status UI
          if(menuCounter == 0) {
            game::ui::updateUI_inGame_Status();
            // While true -> while we are in the status menu
            bool loop = true;
            while(loop) {
              while(game::win::getWin().pollEvent(game::win::getEv())) {
              
                if(game::win::getEv().type == sf::Event::Closed) {
                  game::setGS(game::asset::GS::NONE);
                  return;
                }

                if(game::win::getEv().type == sf::Event::KeyPressed) {
                  switch(game::win::getEv().key.code) {
                    case (sf::Keyboard::Escape):
                      loop = false;
                      break;
                    default: ;
                  }
                }
              }
              static int statusCounter = -1;
              renderThings(game::ui::getUI(game::ui::ENUM_UI::IN_GAME_PLAYER_STATUS), statusCounter);
              game::win::getWin().draw(game::asset::getFaceSprite(game::asset::ENTITY_FACE::PLAYER));
              game::win::display();
            }
          }
          else if(menuCounter == 1) {
            /* Inventory */
          }
          else if(menuCounter == 2) {
            /* Save */
          }
          else if(menuCounter == 3) {
            /* Load */
          }
          else if(menuCounter == 4) {
            /* Exit */
            int menuCounter_exit = 0;
            bool loop = true;
            auto positionExitTexts = []() -> void {
              auto v = game::win::getWin().getView();
              auto c = exitUI.menu_sprite[1];

              exitUI.ui_texts[0].setPosition(c.getPosition().x,(v.getCenter().y-150)+70);
              exitUI.ui_texts[1].setPosition(c.getPosition().x,(v.getCenter().y-150)+70*2);
              exitUI.ui_texts[2].setPosition(c.getPosition().x,(v.getCenter().y-150)+70*3);

            };
            exitUI.set_menuPositionToCen();
            positionExitTexts();
            exitUI.ui_texts[0].setFillColor(sf::Color::Yellow);
            while(loop) {

              while(game::win::getWin().pollEvent(game::win::getEv())) {

                if(game::win::getEv().type == sf::Event::KeyPressed) {

                  if(game::win::getEv().key.code == sf::Keyboard::Escape) {
                    game::asset::getSound(game::asset::snd::MENU_CANCEL).play();
                    loop = false;
                    break;
                  }

                  if(game::win::getEv().key.code == sf::Keyboard::W) {
                    game::asset::getSound(game::asset::snd::MENU_HOVER).play();
                    if(menuCounter_exit == 0) {
                      menuCounter_exit = 2;
                      break;
                    }
                    menuCounter_exit--;
                  }
                  else if(game::win::getEv().key.code == sf::Keyboard::S) {
                    game::asset::getSound(game::asset::snd::MENU_HOVER).play();
                    if(menuCounter_exit == 2) {
                      menuCounter_exit = 0;
                      break;
                    }
                    menuCounter_exit++;
                  }
                  else if(game::win::getEv().key.code == sf::Keyboard::J) {
                    game::asset::getSound(game::asset::snd::MENU_SUBMIT).play();
                    if(menuCounter_exit == 0) {
                      loop = false;
                      break;
                    }
                    else if(menuCounter_exit == 1) {
                      game::setGS(game::asset::GS::TITLE);
                      game::win::getWin().setView(game::win::getWin().getDefaultView());
                      game::ani::fadeOut();
                      return;
                    }
                    else if(menuCounter_exit == 2) {
                      game::setGS(game::asset::GS::NONE);
                      return;
                    }
                  }

                }

                if(game::win::getEv().type == sf::Event::Closed) {
                  game::setGS(game::asset::GS::NONE);
                  return;
                }

              }
              if(!loop) break;
              renderThings(exitUI, menuCounter_exit);
              game::win::display();
            }
          }
        }

      }
      if(game::win::getEv().type == sf::Event::Closed) {
        game::setGS(game::asset::GS::NONE);
      }
    }
    
    renderThings(game::ui::getUI(game::ui::ENUM_UI::IN_GAME) , menuCounter);
    game::win::display();
  } // end of handleUI_Menu function

}

namespace {

  static void init() {
    in_uiMenu = false;
    menuCounter = 0;
    /* For exitUI */
    static bool _init = false;
    // Mon 21 Oct 2019 12:18:51 AM CDT
    // TODO: Move this out of here. exitUI texts should be in ui files, not debug.
    if(!_init) {
      exitUI.ui_texts.resize(3);
      exitUI.ui_texts[0] = game::asset::createString("CANCEL");
      exitUI.ui_texts[1] = game::asset::createString("EXIT TO MENU");
      exitUI.ui_texts[2] = game::asset::createString("EXIT TO DESKTOP");
      exitUI.set_menuTextsOrigin();
      exitUI.set_menuTextsCenterOfUI();
      exitUI.menu_sprite[0].setSize(sf::Vector2f(game::win::getRes_x()/1.5, game::win::getRes_y()/2));
      exitUI.menu_sprite[1].setSize(sf::Vector2f(exitUI.menu_sprite[0].getSize().x*game::ui::ui_SF_x, exitUI.menu_sprite[0].getSize().y*game::ui::ui_SF_y));
      exitUI.set_menuSpritesOrigin();
      exitUI.set_menuTextsCenterOfUI();
      _init = true;
    }
  }

}
