#include "ui.hpp"
#include "entity.hpp"
#include "game.hpp"
#include <SFML/Graphics/Color.hpp>

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

  //////////////////////////////////////////////////////////// 
  // TITLE SCREEN USER INTERFACE + TEXTS
  //////////////////////////////////////////////////////////// 
  _ui[ENUM_UI::TITLESCREEN] = &titleScreen;
  _ui[ENUM_UI::IN_GAME] = &inGame;
  _ui[ENUM_UI::IN_GAME_PLAYER_STATUS] = &inGame_PlayerStatus;

  // BG where texts rests
  titleScreen.menu_sprite[0].setSize(sf::Vector2f(game::win::getRes_x()/3,game::win::getRes_y()/3));
  titleScreen.menu_sprite[1].setSize(sf::Vector2f(titleScreen.menu_sprite[0].getSize().x-game::ui::ui_SF_x,titleScreen.menu_sprite[0].getSize().y-game::ui::ui_SF_y));
  titleScreen.set_menuSpritesOrigin();
  titleScreen.menu_sprite[0].setPosition(mid_x, mid_y + game::win::getRes_y()/6);
  titleScreen.menu_sprite[1].setPosition(mid_x, mid_y + game::win::getRes_y()/6);

  // Create text and assign string values
  titleScreen.ui_texts.resize(3);
  titleScreen.ui_texts[0] = asset::createString("Start");
  titleScreen.ui_texts[1] = asset::createString("Load");
  titleScreen.ui_texts[2] = asset::createString("Exit");
  titleScreen.set_menuTextsOrigin();

  // Set the positions of the texts
  titleScreen.ui_texts[0].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+55);
  titleScreen.ui_texts[1].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+55*2);
  titleScreen.ui_texts[2].setPosition(mid_x,(titleScreen.menu_sprite[1].getGlobalBounds().top)+55*3);

  //////////////////////////////////////////////////////////// 
  // IN GAME USER INTERFACE + TEXTS
  //////////////////////////////////////////////////////////// 
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
  inGame.menu_sprite[1].setSize(sf::Vector2f(inGame.menu_sprite[0].getSize().x-game::ui::ui_SF_x,inGame.menu_sprite[0].getSize().y-game::ui::ui_SF_y));
  inGame.set_menuSpritesOrigin();

  //////////////////////////////////////////////////////////// 
  // PLAYER STATUS USER INTERFACE + TEXTS
  //////////////////////////////////////////////////////////// 
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

  // Create the status UI and a UI for Erdrick's face.
  p.anotherOne();
  p.anotherOne();

  // Set the size of the player status UI here
  inGame_PlayerStatus.menu_sprite[0].setSize(sf::Vector2f(game::win::getRes_x()/1.5, game::win::getRes_y()/1.5));
  sf::Vector2f stat = sf::Vector2f(inGame_PlayerStatus.menu_sprite[0].getSize());
  inGame_PlayerStatus.menu_sprite[1].setSize(sf::Vector2f(stat.x-game::ui::ui_SF_x, stat.y-game::ui::ui_SF_y));
  inGame_PlayerStatus.menu_sprite[2].setSize(sf::Vector2f((stat.x-game::ui::ui_SF_x)/2, (stat.y-game::ui::ui_SF_y)/2));
  inGame_PlayerStatus.menu_sprite[3].setSize(sf::Vector2f(stat.x-game::ui::ui_SF_x, (stat.y-game::ui::ui_SF_y)/2));

  //inGame_PlayerStatus.menu_sprite[2].setOutlineColor(sf::Color::Transparent);
  //inGame_PlayerStatus.menu_sprite[3].setOutlineColor(sf::Color::Transparent);

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
  s[0] = "NAME:  " + p.m_Name;
  s[1] = "LVL:  " + std::to_string(p.m_Level);
  s[2] = "HP:  " + std::to_string(p.m_Health) + "/" + std::to_string(p.m_maxHealth);
  s[3] = "MP:  " + std::to_string(p.m_Mana) + "/" + std::to_string(p.m_maxMana);
  s[4] = "GOLD:  " + std::to_string(p.m_Gold) + "  G";
  s[5] = "STR:  " + std::to_string(p.m_Str);
  s[6] = "DEX:  " + std::to_string(p.m_Dex);
  s[7] = "INT:  " + std::to_string(p.m_Int);
  s[8] = "DEF:  " + std::to_string(p.m_def);
  s[9] = "LUK:  " + std::to_string(p.m_luck);
  s[10]= "AGI:  " + std::to_string(p.m_agil);
  s[11]= "BATTLES  FOUGHT:  " + std::to_string(p.m_ttlBattles);
  s[12]= "MONSTERS  SLAIN:  " + std::to_string(p.m_ttlMonstersKilled);
  s[13]= "TTL  EXP  EARNED:  " + std::to_string(p.m_ttlExp);

  for(size_t i = 0; i < statUI->ui_texts.size(); i++) {
    statUI->ui_texts[i] = asset::createString(s[i], 20);
    statUI->ui_texts[i].setOutlineThickness(2.f);
  }
}

// Function that updates the in-game status UI menus
void game::ui::updateUI_inGame_Status() {
  // README: The following code was cut from debug.cc and pasted here for
  // refactorign purposes. debug.cc is getting a litle bloated, and things that
  // should not be there are there.

  #define p game::ui::getUI(game::ui::ENUM_UI::IN_GAME_PLAYER_STATUS)
  // Sets all the UI menus to the center. This is fine for the border
  // and the main UI, but other status UI 2 and 3 need to be set to
  // their locations.
  p.set_menuPositionToCen();
  p.menu_sprite[2].move(p.menu_sprite[2].getSize().x/2, -(p.menu_sprite[2].getSize().y/2));
  p.menu_sprite[3].move(0, p.menu_sprite[3].getSize().y/2+3);

  auto m_ui1 = &game::ui::getUI(game::ui::ENUM_UI::IN_GAME_PLAYER_STATUS).menu_sprite[1];
  auto m_ui2 = &game::ui::getUI(game::ui::ENUM_UI::IN_GAME_PLAYER_STATUS).menu_sprite[2];
  auto m_ui3 = &game::ui::getUI(game::ui::ENUM_UI::IN_GAME_PLAYER_STATUS).menu_sprite[3];
  float statusMenuOffset2_x = m_ui2->getSize().x*0.1;
  float statusMenuOffset2_y = m_ui2->getSize().y*0.15;

  // Texts for the menu_ui[2]
  p.ui_texts[0].setPosition(m_ui2->getPosition().x-m_ui2->getSize().x/2+statusMenuOffset2_x, m_ui2->getPosition().y-m_ui2->getSize().y/2+statusMenuOffset2_y*1);
  p.ui_texts[1].setPosition(m_ui2->getPosition().x-m_ui2->getSize().x/2+statusMenuOffset2_x, m_ui2->getPosition().y-m_ui2->getSize().y/2+statusMenuOffset2_y*2);
  p.ui_texts[2].setPosition(m_ui2->getPosition().x-m_ui2->getSize().x/2+statusMenuOffset2_x, m_ui2->getPosition().y-m_ui2->getSize().y/2+statusMenuOffset2_y*3);
  p.ui_texts[3].setPosition(m_ui2->getPosition().x-m_ui2->getSize().x/2+statusMenuOffset2_x, m_ui2->getPosition().y-m_ui2->getSize().y/2+statusMenuOffset2_y*4);
  p.ui_texts[4].setPosition(m_ui2->getPosition().x-m_ui2->getSize().x/2+statusMenuOffset2_x, m_ui2->getPosition().y-m_ui2->getSize().y/2+statusMenuOffset2_y*5);

  // The offsets for the texts of the third status UI menu. This seems
  // to work, although it can be improved. I'd rather not spend too
  // much time trying to figure how which values would work best so
  // that I can just get some texts to look nice.
  float statusMenuOffset3_x = m_ui3->getSize().x*0.05;
  float statusMenuOffset3_y = m_ui3->getSize().y*0.13;

  // Texts for the menu_ui[3]
  p.ui_texts[5].setPosition(m_ui3->getPosition().x-m_ui3->getSize().x/2+statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*1);
  p.ui_texts[6].setPosition(m_ui3->getPosition().x-m_ui3->getSize().x/2+statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*2);
  p.ui_texts[7].setPosition(m_ui3->getPosition().x-m_ui3->getSize().x/2+statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*3);
  p.ui_texts[8].setPosition(m_ui3->getPosition().x-m_ui3->getSize().x/2+statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*4);
  p.ui_texts[9].setPosition(m_ui3->getPosition().x-m_ui3->getSize().x/2+statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*5);
  p.ui_texts[10].setPosition(m_ui3->getPosition().x-m_ui3->getSize().x/2+statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*6);

  // Texts for menu_ui[3], spaced out like this because these aren't
  // really player stats, but more like achievements.
  p.ui_texts[11].setPosition(m_ui3->getPosition().x-3.3*statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*1);
  p.ui_texts[12].setPosition(m_ui3->getPosition().x-3.3*statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*3);
  p.ui_texts[13].setPosition(m_ui3->getPosition().x-3.3*statusMenuOffset3_x, m_ui3->getPosition().y-m_ui3->getSize().y/2+statusMenuOffset3_y*5);


  //game::asset::getFaceSprite(game::asset::ENTITY_FACE::PLAYER).setPosition(c.getPosition().x-350, v.getCenter().y-250);
  game::asset::getFaceSprite(game::asset::ENTITY_FACE::PLAYER).setPosition(sf::Vector2f(m_ui1->getPosition().x-m_ui1->getSize().x/2+statusMenuOffset3_x, m_ui1->getPosition().y-m_ui1->getSize().y/2));
  //game::asset::getFaceSprite(game::asset::ENTITY_FACE::PLAYER).move(p.
  #undef p
}

namespace game {
  namespace ui {
    ////////////////////////////////////////////////// 
    //                  UI STRUCT
    ////////////////////////////////////////////////// 

    // Ctor
    UI::UI() {
      /* The default ctor will create the UI. It does not specify the size, so
       * when creating UI, we must specify the size of the UI window. */
      this->menu_sprite.resize(2);
      for(auto& i : this->menu_sprite) {
        i.setFillColor(sf::Color::Blue);
        i.setOutlineColor(sf::Color::White);
        i.setOutlineThickness(3.f);
      }
    }

    // Funnction that creates another blue UI window
    void UI::anotherOne() {
      sf::RectangleShape t;
      t.setFillColor(sf::Color::Blue);
      t.setOutlineColor(sf::Color::White);
      t.setOutlineThickness(3.f);
      this->menu_sprite.push_back(t);
    }

    // Function to set the menu sprites to their origins
    void UI::set_menuSpritesOrigin() {
      for(auto& i : this->menu_sprite) {
        asset::setOriginCenter(i);
      }
    }

    ////////////////////////////////////////////////// 
    //                  UI STRUCT
    ////////////////////////////////////////////////// 
  }
}
