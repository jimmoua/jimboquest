#pragma once
#include <SFML/Graphics.hpp>
#include "asset.hpp"
#include "window.hpp"
#include "game.hpp"

namespace game {

  namespace entity {

    class Entity {
      public:

        /* Constructors */
        Entity();
        Entity(const std::string&,    // Name
               const int&,            // Health
               const int&,            // Mana
               const int&,            // Str
               const int&,            // Dex
               const int&);           // Int

        sf::Sprite m_enSprite;

        void f_modHealth(const int x) { this->m_Health+=x; }
        void f_modMana(const int x)   { this->m_Mana+=x;   }
        void f_modStr(const int x)    { this->m_Str+=x;    }
        void f_modDex(const int x)    { this->m_Dex+=x;    }
        void f_modInt(const int x)    { this->m_Int+=x;    }

        void f_setHealth(const int x) { this->m_Health = x; }
        void f_setMana(const int x)   { this->m_Mana = x;   }
        void f_setStr(const int x)    { this->m_Str = x;    }
        void f_setDex(const int x)    { this->m_Dex = x;    }
        void f_setInt(const int x)    { this->m_Int = x;    }

        void f_SetName(const std::string n) { this->m_Name = n; }
        void f_setRace(const asset::entity::RACE r) { this->m_Race = r; }
        void f_setJobClass(const asset::entity::BASE_CLASS c) {
          this->m_JobClass = c;
        }

      private:
        std::string m_Name;
        int m_Health;
        int m_Mana;
        int m_Str;
        int m_Dex;
        int m_Int;
        game::asset::entity::RACE       m_Race;
        game::asset::entity::BASE_CLASS m_JobClass;
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
        void handleMove(std::vector< std::vector<sf::Sprite> >&);
      private:
    };

    Player*& getPl();

  }


}
