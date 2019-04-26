#include "ui.hpp"
#include "entity.hpp"
#include "game.hpp"

namespace {
  /* Need a mapping of UI */
  static std::map<game::ui::ENUM_UI, game::ui::UI*> _ui;

  /* Define objects for UI here */
  static game::ui::UI titleScreen;
  static game::ui::UI inGame;
}

void game::ui::init() {

  const static int mid_x = win::getRes_x()/2;
  const static int mid_y = win::getRes_y()/2;

  /* INIT UI */

  /* TITLE SCREEN UI */
  _ui[ENUM_UI::TITLESCREEN] = &titleScreen;
  _ui[ENUM_UI::IN_GAME] = &inGame;

  // BG where texts rests
  titleScreen.menu_sprite[0].setSize(sf::Vector2f(300, 380));
  titleScreen.menu_sprite[1].setSize(sf::Vector2f(280, 360));
  titleScreen.set_menuSpritesOrigin();
  titleScreen.menu_sprite[0].setPosition(mid_x, mid_y+230);
  titleScreen.menu_sprite[1].setPosition(mid_x, mid_y+230);

  // Create text and define their properties
  titleScreen.ui_texts.resize(4);
  titleScreen.ui_texts[0] = asset::createString("Start");
  titleScreen.ui_texts[1] = asset::createString("Load");
  titleScreen.ui_texts[2] = asset::createString("Exit");
  titleScreen.ui_texts[3] = asset::createString("Debug");
  titleScreen.set_menuTextsOrigin();
  titleScreen.ui_texts[0].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+70);
  titleScreen.ui_texts[1].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+70*2);
  titleScreen.ui_texts[2].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+70*3);
  titleScreen.ui_texts[3].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+70*4);

  /* In game UI texts */
  inGame.ui_texts.resize(5);
  inGame.ui_texts[0] = asset::createString("STATUS");
  inGame.ui_texts[1] = asset::createString("INVENTORY");
  inGame.ui_texts[2] = asset::createString("SAVE");
  inGame.ui_texts[3] = asset::createString("LOAD");
  inGame.ui_texts[4] = asset::createString("EXIT");
  inGame.set_menuTextsOrigin();
  inGame.set_menuTextsCenterOfUI();

  /* IN GAME UI menu */
  inGame.menu_sprite[0].setSize(sf::Vector2f(500,460));
  inGame.menu_sprite[1].setSize(sf::Vector2f(480,440));
  //inGame.et_menuTextsOrigin();
  inGame.set_menuSpritesOrigin();
  //inGame.set_menuPositionToCen();
  //inGame.set_menuTextsCenterOfUI();

}

game::ui::UI& game::ui::getUI(const game::ui::ENUM_UI& id) {
  return *_ui[id];
}

void game::ui::UI::drawUIsprites() {
  win::getWin().draw(menu_sprite[0]);
  win::getWin().draw(menu_sprite[1]);
}

void game::ui::UI::drawUItexts() {
  for(auto& i : this->ui_texts) {
    win::getWin().draw(i);
  }
}
void game::ui::UI::set_menuTextsOrigin() {
  for(auto& i : this->ui_texts) {
    game::asset::setOriginCenter(i);
  }
}

void game::ui::UI::set_menuTextsCenterOfUI() {
  auto v = win::getWin().getView();
  static const auto c = this->menu_sprite[1];
  float offset = 70;
  for(auto& i : this->ui_texts) {
    /* Window top is being defined as the origin of the window */
    //i.setPosition(this->menu_sprite[1].getPosition().x, c.top-v.getCenter().y+offset);
    i.setPosition(this->menu_sprite[1].getPosition().x, (v.getCenter().y-200)+offset);
    offset+=70;
  }
}

void game::ui::UI::set_menuPositionToCen() {
  sf::View v = win::getWin().getView();
  //this->menu_sprite[0].setPosition(win::getWin().getView().getCenter());
  //this->menu_sprite[1].setPosition(win::getWin().getView().getCenter());
  for(auto& i : this->menu_sprite) {
    i.setPosition(v.getCenter());
  }
}
