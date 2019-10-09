#include "asset.hpp"
#include "animations.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "battle.hpp"
#include "ui.hpp"
#include "game.hpp"

namespace {

  /* The battle data. Here will contain sprites, vectors, etc to properly
   * display and handle logics of battle */
  namespace _battleData {
    /* Monster list vector
     * For now, let's keep the list simple and only set singleton sets of
     *   common enemy monsters. */
    static std::vector<game::entity::Entity> _monsterList;

    /* This will be the monster sprites vector to draw on the screen */
    static std::vector<sf::Sprite> _monsterSprites;

  }


  /* Define some groups of possible monsters*/
  void _createSlimeGroup_3() {
    if(!_battleData::_monsterList.empty() && !_battleData::_monsterSprites.empty()) {
    }
    for(unsigned int i = 0; i < 3; i++ ) {
      _battleData::_monsterSprites.push_back(game::entity::sprite::sprite_slime());
      _battleData::_monsterList.push_back(game::entity::createSlime());
    }
  };

}

void game::initBattle() {

  /* The RNG battles are going to be based off the player's level
   *   1-4    EASY
   *   5-9    MEDIUM
   *   10-14  HARD
   *   15-19  EXTREME
   *   20-24  SAVAGE
   *   25+    LEGENDARY   */

  /* Below is the battle window where all monster sprites will be drawn */
  /* Got the battle window working. DO NOT TOUCH! */
  sf::RectangleShape l_battleWindow[2];
  sf::RectangleShape l_battleWindow_Choices[2];

  l_battleWindow[0].setSize(sf::Vector2f(700, 500));
  l_battleWindow[1].setSize(sf::Vector2f(680, 480));
  for(auto& i : l_battleWindow) {
    i.setFillColor(sf::Color::Black);
    i.setOutlineThickness(3);
    i.setOutlineColor(sf::Color::White);
    game::asset::setOriginCenter(i);
    sf::View v = game::win::getWin().getView();
    i.setPosition(v.getCenter());
    i.move(0, -100);
  }
  /* ------------DO-NOT-MODIFY-ABOVE------------- */

   /* Players will fight monsters depending on what their levels are. */
   if(game::entity::getPl().f_getLevel() < 5) {
     /* EASY LEVELED MONSTERS */
     std::cout << "Player level is less than 5, initiating easy leveled monsters\n";
     _createSlimeGroup_3();
     std::cout << "Created slime group x3\n";
   }
   else if(game::entity::getPl().f_getLevel() >= 5) {
     /* MEDIUM LEVELED MONSTERS */
     std::cout << "Player level is geq than 5, initiating medium-leveled monsters\n";
   }
   else if(game::entity::getPl().f_getLevel() >= 10) {
     /* HARD LEVELED MONSTERS */
     std::cout << "Player level is geq than 10, initiating hard-leveled mosnters.\n";
   }
   else if(game::entity::getPl().f_getLevel() >= 15) {
     /* EXTREME LEVELED MONSTERS */
     std::cout << "Player level is geq than 15, initiating extreme-leveled monsters.\n";
   }
   else if(game::entity::getPl().f_getLevel() >= 20) {
     /* SAVAGE LEVELED MONSTERS */
     std::cout << "Player level is geq than 15, initiating savage-leveled monsters.\n";
   }
   else if(game::entity::getPl().f_getLevel() >= 25) {
     /* LEGENDARY LEVELED MONSTERS */
     std::cout << "Player level is geq than 25, initiating legendary-leveled monsters.\n";
   }

   /* While there are monsters, keep the fight going. The condition will be
    * something like 
    *
    *   while(!monsters.empty())
    *     ...
    *
    * */

   /* Get the view for the window so we can use it when displaying monsters. We
    * will then need an offset, since l_battleWindow is not the same as as the
    * view size */
   sf::View v = win::getWin().getView();
   const auto offset = (v.getSize().x - l_battleWindow[0].getSize().x)/2;
   for(unsigned int i = 0; i < _battleData::_monsterSprites.size(); i++) {
     _battleData::_monsterSprites[i].setPosition(v.getCenter());
   }
   while(true) {
     while(game::win::getWin().pollEvent(game::win::getEv())) {
       if(game::win::getEv().key.code == sf::Keyboard::Escape) {
         return;
       }
     }
     game::win::getWin().draw(l_battleWindow[0]);
     game::win::getWin().draw(l_battleWindow[1]);
     /* Set the monster positions relative to the window */
     for(auto& i : _battleData::_monsterSprites) {
       game::win::getWin().draw(i);
     }
     game::win::getWin().display();
   }


  /* end of battle */
}
