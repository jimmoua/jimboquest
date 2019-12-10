#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "asset.hpp"
#include "map.hpp"
#include <vector>

namespace game {

  namespace entity {

    enum class FaceDirection {
      UP,DOWN,RIGHT,LEFT
    };

    class Entity {
      public:

        /* Constructors */
        Entity();
        Entity(const std::string&,    // Name
               const int&,            // Health
               const int&,            // Mana
               const int&,            // Str
               const int&,            // Dex
               const int&,            // Int
               const int&);           // EXP

        sf::Sprite m_enSprite;

        // Monster Attributes
        std::string m_Name;
        int m_maxHealth = 100;
        int m_maxMana = 100;
        int m_Health = m_maxHealth;
        int m_Mana = m_maxMana;
        int m_Str = 0;
        int m_Dex = 0;
        int m_Int = 0;
        int m_Gold = 0;
        int m_Level = 1;
        int m_def = 10;
        int m_luck = 5;   // for crit + gold drop
        int m_agil = 10;  // for dodge chance

        int m_ttlBattles = 0;
        int m_ttlMonstersKilled = 0;
        int m_ttlExp = 0;

        FaceDirection m_CurrentFaceDir = FaceDirection::DOWN;
    };

    class Player : public Entity {
      public:
        Player();
        Player(const std::string&,
               const int&,
               const int&,
               const int&,
               const int&,
               const int&);

        void handleMove();
      private:
    };

    /* Returns the player data. Use this to manipulate player data as well. */
    Player& getPl();


    /* Monster data */
    Entity createSlime();

    void init();

    namespace sprite {
      sf::Sprite sprite_slime();
    }

  }


}

#endif
