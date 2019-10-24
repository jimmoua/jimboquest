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
    _battleData::_monsterList.clear();
    _battleData::_monsterSprites.clear();
    for(unsigned int i = 0; i < 3; i++ ) {
      _battleData::_monsterSprites.push_back(game::entity::sprite::sprite_slime());
      _battleData::_monsterList.push_back(game::entity::createSlime());
    }
  };

}
/* FUNCTION: initBattle()
 * This inits the battle everytime there is an encounter. Sets up and populates
 * the monster vectors */
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

  l_battleWindow[0].setSize(sf::Vector2f(game::win::getRes_x()/1.5, game::win::getRes_y()/1.7));
  l_battleWindow[1].setSize(sf::Vector2f(l_battleWindow[0].getSize().x*game::ui::ui_SF_x, l_battleWindow[0].getSize().y*game::ui::ui_SF_y));
  for(auto& i : l_battleWindow) {
    i.setFillColor(sf::Color::Black);
    i.setOutlineThickness(3);
    i.setOutlineColor(sf::Color::White);
    game::asset::setOriginCenter(i);
    sf::View v = game::win::getWin().getView();
    i.setPosition(v.getCenter());
    i.move(0, -100);
  }
  if(!_battleData::_monsterSprites.empty()) _battleData::_monsterSprites.clear();
  if(!_battleData::_monsterList.empty()) _battleData::_monsterList.clear();
  /* ------------DO-NOT-MODIFY-ABOVE------------- */

  ////////////////////////////////////////////////// 
  //          Battle Choices UI Creation
  ////////////////////////////////////////////////// 
  l_battleWindow_Choices[0].setSize(sf::Vector2f(game::win::getRes_x()/1.5, game::win::getRes_y()/4));
  // Did not multiply by ui_SF_y because it makes the border to small
  l_battleWindow_Choices[1].setSize(sf::Vector2f(l_battleWindow_Choices[0].getSize().x*game::ui::ui_SF_x, l_battleWindow_Choices[0].getSize().y*.9));
  for(auto& i : l_battleWindow_Choices) {
    i.setFillColor(sf::Color::Black);
    i.setOutlineThickness(3);
    i.setOutlineColor(sf::Color::White);
    game::asset::setOriginCenter(i);
    sf::View v = game::win::getWin().getView();
    i.setPosition(v.getCenter());
    i.move(0, 220);
  }

  ////////////////////////////////////////////////// 
  // Generate the monsters to fight based on the
  // player's level
  ////////////////////////////////////////////////// 
  if(game::entity::getPl().f_getLevel() < 5) {
    /* EASY LEVELED MONSTERS */
    _createSlimeGroup_3();
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

  // offset is going to be the amount of times we will move each sprite for
  // every monster we have in the list. offset is important because it will be
  // the spacing between each monster.
  auto offset = l_battleWindow[1].getSize().x/(_battleData::_monsterSprites.size()+1);

  // pos is going to be the position of battleWindow[1].
  auto pos = l_battleWindow[1].getPosition(); 

  // Set the initial position to the right of the battle window. We will then
  // add pos.x to it. We do this so there is the correct amount of spacing
  // between the monsters and the window.
  auto initPos = pos.x + offset - l_battleWindow[1].getSize().x/2; 

  // Set the monster locations on the screen
  for(unsigned int i = 0; i < _battleData::_monsterSprites.size(); i++) {
    _battleData::_monsterSprites[i].setPosition(initPos + offset*(i), pos.y);
  }
  printf("The size is: ");
  std::cout << _battleData::_monsterSprites.size() << std::endl;

  while(true) {
    while(game::win::getWin().pollEvent(game::win::getEv())) {
      if(game::win::getEv().key.code == sf::Keyboard::Escape) {
        return;
      }
    }
    game::win::getWin().draw(l_battleWindow[0]);
    game::win::getWin().draw(l_battleWindow[1]);
    game::win::getWin().draw(l_battleWindow_Choices[0]);
    game::win::getWin().draw(l_battleWindow_Choices[1]);
    /* Set the monster positions relative to the window */
    for(auto& i : _battleData::_monsterSprites) {
      game::win::getWin().draw(i);
    }
    game::win::getWin().display();
  }


  /* end of battle */
}
