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
     * We have a double vector because we can have something like
     *    3x slimes        2x bodkin archers         1x slime knight
     *    
     *    where each monster represents a group (vector in this case)
     *      and the whole thing can be pushed into double vector */
    static std::vector<std::vector<game::entity::Entity>>* _monsterList;

  }


  /* Define some groups of possible monsters*/
  void _createSlimeGroup_3() {
    std::vector<game::entity::Entity> t;
    for(int i = 0; i < 3; i++) {
      t.push_back(game::entity::createSlime());
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

   /* Initialize the monster list */
  _battleData::_monsterList = new std::vector<std::vector<game::entity::Entity>>;

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

   while(true) {
     while(game::win::getWin().pollEvent(game::win::getEv())) {
       if(game::win::getEv().key.code == sf::Keyboard::Escape) {
         return;
       }
     }
       game::win::getWin().draw(l_battleWindow[0]);
       game::win::getWin().draw(l_battleWindow[1]);
       game::win::getWin().display();
   }

   delete _battleData::_monsterList;

  /* end of battle */
}
