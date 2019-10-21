#include "ui.hpp"
#include "entity.hpp"
#include "game.hpp"

namespace {
  /* Need a mapping of UI */
  static std::map<game::ui::ENUM_UI, game::ui::UI*> _ui;

  /* Define objects for UI here */

  /*  For title screen */
  static game::ui::UI titleScreen;

  /* UIs for in game */
  static game::ui::UI inGame;
  static game::ui::UI inGame_PlayerStatus;
}

void game::ui::init() {

  const int mid_x = win::getRes_x()/2;
  const int mid_y = win::getRes_y()/2;

  /* INIT UI */

  /* TITLE SCREEN UI */
  _ui[ENUM_UI::TITLESCREEN] = &titleScreen;
  _ui[ENUM_UI::IN_GAME] = &inGame;
  _ui[ENUM_UI::IN_GAME_PLAYER_STATUS] = &inGame_PlayerStatus;

  // BG where texts rests
  titleScreen.menu_sprite[0].setSize(sf::Vector2f(game::win::getRes_x()/3,game::win::getRes_y()/3));
  titleScreen.menu_sprite[1].setSize(sf::Vector2f(titleScreen.menu_sprite[0].getSize().x*game::ui::ui_SF_x,titleScreen.menu_sprite[0].getSize().y*game::ui::ui_SF_y));
  titleScreen.set_menuSpritesOrigin();
  titleScreen.menu_sprite[0].setPosition(mid_x, mid_y + game::win::getRes_y()/6);
  titleScreen.menu_sprite[1].setPosition(mid_x, mid_y + game::win::getRes_y()/6);

  // Create text and define their properties
  titleScreen.ui_texts.resize(4);
  titleScreen.ui_texts[0] = asset::createString("Start");
  titleScreen.ui_texts[1] = asset::createString("Load");
  titleScreen.ui_texts[2] = asset::createString("Exit");
  titleScreen.ui_texts[3] = asset::createString("Debug");
  titleScreen.set_menuTextsOrigin();

  /* CUSTOM */
  titleScreen.ui_texts[0].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+45);
  titleScreen.ui_texts[1].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+45*2);
  titleScreen.ui_texts[2].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+45*3);
  titleScreen.ui_texts[3].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+45*4);

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
  inGame.menu_sprite[0].setSize(sf::Vector2f(game::win::getRes_x()/2, game::win::getRes_y()/1.7));
  inGame.menu_sprite[1].setSize(sf::Vector2f(inGame.menu_sprite[0].getSize().x*game::ui::ui_SF_x,inGame.menu_sprite[0].getSize().y*game::ui::ui_SF_y));
  inGame.set_menuSpritesOrigin();

  // In-game Player Status UI + Text
  #define p inGame_PlayerStatus
  // Create 14 texts for the UI and then define their default values
  p.ui_texts.resize(14);
  
  p.ui_texts[1] = asset::createString("lvl");    // Level
  p.ui_texts[2] = asset::createString("hp");     // Health
  p.ui_texts[3] = asset::createString("mp");     // Mana
  p.ui_texts[4] = asset::createString("gp");     // Gold

  p.ui_texts[5] = asset::createString("str");    // str
  p.ui_texts[6] = asset::createString("dex");    // dex
  p.ui_texts[7] = asset::createString("int");    // int
  p.ui_texts[8] = asset::createString("def");    // def
  p.ui_texts[9] = asset::createString("luk");    // luk
  p.ui_texts[10] = asset::createString("agi");   // agi

  p.ui_texts[11] = asset::createString("ttl battle");// ttl battles fought
  p.ui_texts[12] = asset::createString("ttl mon");   // ttl monsters slain
  p.ui_texts[13] = asset::createString("ttl exp");   // ttl exp earned

  // Create the status UI and a UI for the Erdrick's face.
  p.anotherOne();
  p.anotherOne();

  // Set the size of the player status UI here
  inGame_PlayerStatus.menu_sprite[0].setSize(sf::Vector2f(game::win::getRes_x()/1.5, game::win::getRes_y()/1.5));
  sf::Vector2f stat = sf::Vector2f(inGame_PlayerStatus.menu_sprite[0].getSize());
  inGame_PlayerStatus.menu_sprite[1].setSize(sf::Vector2f(stat.x*game::ui::ui_SF_x, stat.y*game::ui::ui_SF_y));
  inGame_PlayerStatus.menu_sprite[2].setSize(sf::Vector2f(stat.x*game::ui::ui_SF_x/2, stat.y*game::ui::ui_SF_y/2));
  inGame_PlayerStatus.menu_sprite[3].setSize(sf::Vector2f(stat.x*game::ui::ui_SF_x, stat.y*game::ui::ui_SF_y/2));

  // menu_sprite[0] = border
  // menu_sprite[1] = main
  // menu_sprite[2] = Character name, hp, mp, gold
  // menu_sprite[3] = Character status and battle status
  //inGame_PlayerStatus.menu_sprite[0].setFillColor(sf::Color::Blue);
  //inGame_PlayerStatus.menu_sprite[1].setFillColor(sf::Color::Blue);
  inGame_PlayerStatus.menu_sprite[2].setFillColor(sf::Color::Transparent);
  inGame_PlayerStatus.menu_sprite[3].setFillColor(sf::Color::Transparent);

  inGame_PlayerStatus.set_menuSpritesOrigin();
  #undef p
}

game::ui::UI& game::ui::getUI(const game::ui::ENUM_UI& id) {
  return *_ui[id];
}

void game::ui::UI::drawUIsprites() {
  for(auto& i : this->menu_sprite) {
    win::getWin().draw(i);
  }
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
  const auto c = this->menu_sprite[1];
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

void game::entity::updatePlayerStatusUI() {
  auto statUI = &game::ui::getUI(game::ui::ENUM_UI::IN_GAME_PLAYER_STATUS);
  auto p = game::entity::getPl();
  std::string s[statUI->ui_texts.size()];
  s[0] = "NAME:  " + p.f_getName();
  s[1] = "LVL:  " + std::to_string(p.f_getLevel());
  s[2] = "HP:  " + std::to_string(p.f_getHealth()) + "/" + std::to_string(p.f_getMaxHealth());
  s[3] = "MP:  " + std::to_string(p.f_getMana()) + "/" + std::to_string(p.f_getMaxMana());
  s[4] = "GOLD:  " + std::to_string(p.f_getGold()) + "  G";
  s[5] = "STR:  " + std::to_string(p.f_getStr());
  s[6] = "DEX:  " + std::to_string(p.f_getDex());
  s[7] = "INT:  " + std::to_string(p.f_getInt());
  s[8] = "DEF:  " + std::to_string(p.f_getDef());
  s[9] = "LUK:  " + std::to_string(p.f_getLuck());
  s[10]= "AGI:  " + std::to_string(p.f_getAgil());
  s[11]= "BATTLES  FOUGHT:  " + std::to_string(p.f_get_ttlBattles());
  s[12]= "MONSTERS  SLAIN:  " + std::to_string(p.f_get_ttlMonKill());
  s[13]= "TTL  EXP  EARNED:  " + std::to_string(p.f_get_ttlBattles());

  for(size_t i = 0; i < statUI->ui_texts.size(); i++) {
    statUI->ui_texts[i] = asset::createString(s[i], 20);
    statUI->ui_texts[i].setOutlineThickness(2.f);
  }
}
