#include "asset.hpp"
#include "animations.hpp"
#include "entity.hpp"
#include "window.hpp"
#include "battle.hpp"
#include "ui.hpp"
#include "game.hpp"
#include <SFML/Graphics.hpp>

namespace {

  ////////////////////////////////////////////////// 
  // Battle Data Namespace
  //
  // Contains monster list and monster sprite
  // vectors, and pretty much anything that displays
  // when a battle is initialized.
  ////////////////////////////////////////////////// 
  namespace battleData {
    // Monster list vector.
    //
    // For now, let's keep the list simple and only set singleton sets of
    // common enemy monsters.
    static std::vector<game::entity::Entity> monsterList;

    // This will be the monster sprites vector to draw on the screen
    static std::vector<sf::Sprite> monsterSprites;

  }


  ////////////////////////////////////////////////// 
  //              MONSTER GROUPS
  ////////////////////////////////////////////////// 
  void createSlimeGroup_3() {
    battleData::monsterList.clear();
    battleData::monsterSprites.clear();
    game::entity::Entity slimeA = game::entity::createSlime();
    game::entity::Entity slimeB = game::entity::createSlime();
    game::entity::Entity slimeC = game::entity::createSlime();
    slimeA.m_Name.append(" A");
    slimeB.m_Name.append(" B");
    slimeC.m_Name.append(" C");
    battleData::monsterSprites.push_back(game::entity::sprite::sprite_slime());
    battleData::monsterSprites.push_back(game::entity::sprite::sprite_slime());
    battleData::monsterSprites.push_back(game::entity::sprite::sprite_slime());
    battleData::monsterList.push_back(slimeA);
    battleData::monsterList.push_back(slimeB);
    battleData::monsterList.push_back(slimeC);
  };

}
/* FUNCTION: initBattle()
 * This inits the battle everytime there is an encounter. Sets up and populates
 * the monster vectors */
void game::initBattle() {

  // enum data types for battle choice
  enum class battle_choice {
    NONE,FIGHT,ABILITY,FLEE
  };

  battle_choice selected_choice = battle_choice::NONE;
  // Counter for battle choices
  int choice_counter = static_cast<int>(battle_choice::FIGHT);;


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
  l_battleWindow[1].setSize(sf::Vector2f(l_battleWindow[0].getSize().x-game::ui::ui_SF_x, l_battleWindow[0].getSize().y-game::ui::ui_SF_y));
  for(auto& i : l_battleWindow) {
    i.setFillColor(sf::Color::Black);
    i.setOutlineThickness(3);
    i.setOutlineColor(sf::Color::White);
    game::asset::setOriginCenter(i);
    sf::View v = game::win::getWin().getView();
    i.setPosition(v.getCenter());
    i.move(0, -100);
  }
  if(!battleData::monsterSprites.empty()) battleData::monsterSprites.clear();
  if(!battleData::monsterList.empty()) battleData::monsterList.clear();
  /* ------------DO-NOT-MODIFY-ABOVE------------- */

  ////////////////////////////////////////////////// 
  //          Battle Choices UI Creation
  ////////////////////////////////////////////////// 
  l_battleWindow_Choices[0].setSize(sf::Vector2f(game::win::getRes_x()/1.5, game::win::getRes_y()/4));
  l_battleWindow_Choices[1].setSize(sf::Vector2f(l_battleWindow_Choices[0].getSize().x-game::ui::ui_SF_x, l_battleWindow_Choices[0].getSize().y*.9));
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
  if(game::entity::getPl().m_Level < 5) {
    /* EASY LEVELED MONSTERS */
    createSlimeGroup_3();
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
  auto offset = l_battleWindow[1].getSize().x/(battleData::monsterSprites.size()+1);

  // pos is going to be the position of battleWindow[1].
  auto pos = l_battleWindow[1].getPosition(); 

  // Set the initial position to the right of the battle window. We will then
  // add pos.x to it. We do this so there is the correct amount of spacing
  // between the monsters and the window.
  auto initPos = pos.x + offset - l_battleWindow[1].getSize().x/2; 

  // Set the monster locations on the screen
  for(unsigned int i = 0; i < battleData::monsterSprites.size(); i++) {
    battleData::monsterSprites[i].setPosition(initPos + offset*(i), pos.y);
  }

  std::clog << "Monster list size is: " << battleData::monsterList.size() << std::endl;

  // Create some text for the choices that player is allowed to do during a
  // battle. Also define their positions.
  sf::Text text_fight   = game::asset::createString("Fight");
  sf::Text text_flee    = game::asset::createString("Flee");
  sf::Text text_ability = game::asset::createString("Abilities");
  text_fight.setPosition(game::win::getWin().getView().getCenter().x, game::win::getWin().getView().getCenter().y);
  text_flee.setPosition(game::win::getWin().getView().getCenter().x, game::win::getWin().getView().getCenter().y);
  text_ability.setPosition(game::win::getWin().getView().getCenter().x, game::win::getWin().getView().getCenter().y);
  // Moving the Y by increments of 50 seem to work OK. Unless I change the
  // resolution of the game again, I should not have to modify these values.
  text_fight.move(-290,150);
  text_ability.move(-290,200);
  text_flee.move(-290,250);

  // First  = monster data that cursor points to
  // Second = monster sprite that cursor points to
  std::pair<std::vector<game::entity::Entity>::iterator,std::vector<sf::Sprite>::iterator> monsterCursorData;
  sf::CircleShape monsterCursor;
  monsterCursor.setFillColor(sf::Color::Red);
  monsterCursor.setRadius(10);
  game::asset::setOriginCenter(monsterCursor);
  monsterCursorData.first = battleData::monsterList.begin();
  monsterCursorData.second = battleData::monsterSprites.begin();

  // While there are monsters in the list, keep looping the battle. Monsters
  // will only be removed from the list when they die.
  while(!battleData::monsterList.empty()) {
    bool fight = false;
    monsterCursor.setPosition(monsterCursorData.second->getPosition().x, monsterCursorData.second->getGlobalBounds().top);
    monsterCursor.move(0,-30);

    // Poll the window
    if(selected_choice == battle_choice::NONE) {
      while(game::win::getWin().pollEvent(game::win::getEv())) {
        if(game::win::getEv().type == sf::Event::KeyPressed) {
          if(game::win::getEv().type == sf::Event::KeyPressed) {
            if(game::win::getEv().key.code == sf::Keyboard::W) {
              choice_counter--;
              if(choice_counter < static_cast<int>(battle_choice::FIGHT))
                choice_counter = static_cast<int>(battle_choice::FLEE);
            }
            else if(game::win::getEv().key.code == sf::Keyboard::S) {
              choice_counter++;
              if(choice_counter > static_cast<int>(battle_choice::FLEE))
                choice_counter = static_cast<int>(battle_choice::FIGHT);
            }
            // When J is pressed, set the current counter as the selected.
            else if(game::win::getEv().key.code == sf::Keyboard::J) {
              selected_choice = static_cast<battle_choice>(choice_counter);
              game::win::getEv().key.code = sf::Keyboard::Unknown;
            }
            // Process selected battle choice
            switch(choice_counter) {
              case static_cast<int>(battle_choice::FIGHT):
                text_fight.setFillColor(sf::Color::Yellow);
                text_flee.setFillColor(sf::Color::White);
                text_ability.setFillColor(sf::Color::White);
                break;
              case static_cast<int>(battle_choice::ABILITY):
                text_fight.setFillColor(sf::Color::White);
                text_flee.setFillColor(sf::Color::White);
                text_ability.setFillColor(sf::Color::Yellow);
                break;
              case static_cast<int>(battle_choice::FLEE):
                text_fight.setFillColor(sf::Color::White);
                text_flee.setFillColor(sf::Color::Yellow);
                text_ability.setFillColor(sf::Color::White);
                break;
              default:
                break;
            }
          }
          break;
        }
        else if(game::win::getEv().type == sf::Event::Closed) {
          game::setGS(game::asset::GS::NONE);
          return;
        }
      }
    }
    else if(selected_choice == battle_choice::FIGHT) {
      while(game::win::getWin().pollEvent(game::win::getEv())) {
        if(game::win::getEv().type == sf::Event::KeyPressed) {
          if(game::win::getEv().key.code == sf::Keyboard::Escape) {
            selected_choice = battle_choice::NONE;
            choice_counter = static_cast<int>(battle_choice::FIGHT);
          }
          else if(game::win::getEv().key.code == sf::Keyboard::A) {
            if(monsterCursorData.second != battleData::monsterSprites.begin()) {
              monsterCursorData.second--;
              monsterCursorData.first--;
            }
            else {
              monsterCursorData.second = battleData::monsterSprites.end()-1;
              monsterCursorData.first = battleData::monsterList.end()-1;
            }
          }
          else if(game::win::getEv().key.code == sf::Keyboard::D) {
            if(monsterCursorData.second != battleData::monsterSprites.end()-1) {
              monsterCursorData.second++;
              monsterCursorData.first++;
            }
            else {
              monsterCursorData.second = battleData::monsterSprites.begin();
              monsterCursorData.first = battleData::monsterList.begin();
            }
          }
          else if(game::win::getEv().key.code == sf::Keyboard::J) {
            fight = true;
          }
          break;
        }
      }
    }
    else if(selected_choice == battle_choice::ABILITY) {
      // TODO: Show abilities Erdrick can use
      while(game::win::getWin().pollEvent(game::win::getEv())) {
        if(game::win::getEv().type == sf::Event::KeyPressed) {
          if(game::win::getEv().key.code == sf::Keyboard::Escape) {
            selected_choice = battle_choice::NONE;
            choice_counter = static_cast<int>(battle_choice::ABILITY);
          }
          break;
        }
        else if(game::win::getEv().type == sf::Event::Closed) {
          game::setGS(game::asset::GS::NONE);
          return;
        }
      }
    }
    else if(selected_choice == battle_choice::FLEE) {
      std::clog << "Fleeing\n";
      return;
    }

    if(fight) {
      // TODO: Correctly display and word-wrap the strings that need to
      // be word wrapped so they can be displayed properly.
      //
      // Clear the area for the text window and show some text about the
      // current fight.
      int damage = game::entity::getPl().m_Str / game::genRand(3,4);
      sf::Text playerDamagesMonsterText = game::asset::createString("You deal "+std::to_string(damage)+" points to "+monsterCursorData.first->m_Name);
      std::clog << "Length of the string is: " << playerDamagesMonsterText.getString().getSize() << std::endl;
      playerDamagesMonsterText.setPosition(l_battleWindow_Choices[1].getGlobalBounds().left+l_battleWindow_Choices[1].getOutlineThickness()+margins,
          l_battleWindow_Choices[1].getGlobalBounds().top+l_battleWindow_Choices[1].getOutlineThickness()+margins);
      game::win::getWin().draw(l_battleWindow_Choices[1]);
      game::win::getWin().draw(playerDamagesMonsterText);
      game::win::display();
      sf::sleep(sf::seconds(1));
      monsterCursorData.first->m_Health -= damage;
      std::clog << "Damage is: " << damage << "\n";
      std::clog << monsterCursorData.first->m_Name << " health is: " << monsterCursorData.first->m_Health << "\n";
      if(monsterCursorData.first->m_Health <= 0) {
        game::win::getWin().draw(l_battleWindow_Choices[1]);
        sf::Text defeatedString = game::asset::createString(monsterCursorData.first->m_Name+" is defeated!");
        defeatedString.setPosition(l_battleWindow_Choices[1].getGlobalBounds().left+l_battleWindow_Choices[1].getOutlineThickness()+margins,
                                   l_battleWindow_Choices[1].getGlobalBounds().top+l_battleWindow_Choices[1].getOutlineThickness()+margins);
        game::win::getWin().draw(defeatedString);
        game::win::getWin().display();
        battleData::monsterList.erase(monsterCursorData.first);
        battleData::monsterSprites.erase(monsterCursorData.second);
        monsterCursorData.first = battleData::monsterList.begin();
        monsterCursorData.second = battleData::monsterSprites.begin();
        game::entity::getPl().m_ttlExp+=monsterCursorData.first->m_ttlExp;
        sf::sleep(sf::seconds(1));
      }
      selected_choice = battle_choice::NONE;
    }

    // First draw the battle windows
    game::win::getWin().draw(l_battleWindow[0]);
    game::win::getWin().draw(l_battleWindow[1]);

    // Then draw the choices UI
    game::win::getWin().draw(l_battleWindow_Choices[0]);
    game::win::getWin().draw(l_battleWindow_Choices[1]);


    // Draw the monsters
    for(auto& i : battleData::monsterSprites) {
      game::win::getWin().draw(i);
    }

    // Draw cursors (if in correct state)
    if(selected_choice == battle_choice::FIGHT) {
      game::win::getWin().draw(monsterCursor);
      // Monster Name
      sf::Text monsterName = game::asset::createString(monsterCursorData.first->m_Name);
      sf::Text monsterHealth = game::asset::createString("HP: "+std::to_string(monsterCursorData.first->m_Health)+"/"+std::to_string(monsterCursorData.first->m_maxHealth));
      game::asset::setOriginCenter(monsterName);
      game::asset::setOriginCenter(monsterHealth);
      monsterName.setPosition(l_battleWindow_Choices[1].getPosition().x, l_battleWindow_Choices[1].getPosition().y-30);
      monsterHealth.setPosition(l_battleWindow_Choices[1].getPosition().x, l_battleWindow_Choices[1].getPosition().y+30);
      game::win::getWin().draw(monsterName);
      game::win::getWin().draw(monsterHealth);
    }

    if(battleData::monsterList.empty()) {
      // If the monster list is empty, that means the player has defeated all
      // monsters. Update battles fought + ETC
      sf::Text victoryText = game::asset::createString("You have defeated all\nmonsters!");
      victoryText.setPosition(l_battleWindow_Choices[1].getGlobalBounds().left+margins,
                              l_battleWindow_Choices[1].getGlobalBounds().top+margins);
      game::win::getWin().draw(l_battleWindow_Choices[1]);
      game::win::getWin().draw(victoryText);
      game::win::getWin().display();
      sf::sleep(sf::seconds(2));
      game::entity::getPl().m_ttlBattles++;
      return;
    }

    if(selected_choice == battle_choice::NONE) {
      // Draw the battle texts
      game::win::getWin().draw(text_fight);
      game::win::getWin().draw(text_flee);
      game::win::getWin().draw(text_ability);
    }

    game::win::getWin().display();
  }
}
