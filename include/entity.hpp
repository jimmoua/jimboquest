#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "asset.hpp"
#include "map.hpp"
#include <vector>

namespace game {

  namespace entity {

    enum class _facedirection_ {
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
               const int&);           // Int

        sf::Sprite m_enSprite;

        /* Modders */
        void f_modHealth(const int x) { this->m_Health+=x; }
        void f_modMana(const int x)   { this->m_Mana+=x;   }
        void f_modStr(const int x)    { this->m_Str+=x;    }
        void f_modDex(const int x)    { this->m_Dex+=x;    }
        void f_modInt(const int x)    { this->m_Int+=x;    }
        void f_modGold(const int x)   { this->m_Gold+=x;   }
        void f_modLevel(const int x)  { this->m_Level+=x;  }
        void f_modMaxHealth( const int x ) { this->m_maxHealth+=x; }
        void f_modMaxMana( const int x ) { this->m_maxMana+=x; }
        void f_modDef(const int x) { this->m_def += x; }
        void f_modLuck(const int x) { this->m_luck += x; }
        void f_modAgil(const int x) { this->m_luck += x; }
        void f_set_ttlBattles(const int x) { this->m_ttlBattles += x; }
        void f_set_ttlExp(const int x) { this->m_ttlExp += x; }
        void f_set_ttlMonKill(const int x) { this->m_ttlMonstersKilled += x; }

        /* Setters */
        void f_setHealth(const int x) { this->m_Health = x; }
        void f_setMana(const int x)   { this->m_Mana = x;   }
        void f_setStr(const int x)    { this->m_Str = x;    }
        void f_setDex(const int x)    { this->m_Dex = x;    }
        void f_setInt(const int x)    { this->m_Int = x;    }
        void f_setGold(const int x)   { this->m_Gold = x;   }
        void f_setLevel(const int x)  { this->m_Level = x;  }
        void f_setMaxHealth(const int x) { this->m_maxHealth = x; }
        void f_setMaxMana(const int x) { this->m_maxMana = x; }
        void f_setDef(const int x) { this->m_def = x; }
        void f_setLuck(const int x) { this->m_luck = x; }
        void f_setAgil(const int x) { this->m_luck = x; }
        void f_get_ttlBattles(const int x) { this->m_ttlBattles = x; }
        void f_get_ttlExp(const int x) { this->m_ttlExp = x; }
        void f_get_ttlMonKill(const int x) { this->m_ttlMonstersKilled = x; }
        void f_setFaceDir(const _facedirection_& id) { this->m_CurrentFaceDir = id; }

        void f_SetName(const std::string n) { this->m_Name = n; }
        void f_setRace(const asset::entity::RACE r) { this->m_Race = r; }
        void f_setJobClass(const asset::entity::BASE_CLASS c) {
          this->m_JobClass = c;
        }
        
        /* Getters */
        std::string f_getName() const { return this->m_Name; }
        int f_getHealth() { return this->m_Health; }
        int f_getMana()   { return this->m_Mana;   }
        int f_getStr()    { return this->m_Str;    }
        int f_getDex()    { return this->m_Dex;    }
        int f_getInt()    { return this->m_Int;    }
        int f_getGold()   { return this->m_Gold;   }
        int f_getLevel()  { return this->m_Level;  }
        int f_getMaxHealth()  { return this->m_maxHealth;  }
        int f_getMaxMana()  { return this->m_maxMana;  }
        int f_getDef() { return this->m_def; }
        int f_getLuck() { return this->m_luck; }
        int f_getAgil() { return this->m_agil; }
        int f_get_ttlBattles() { return this->m_ttlBattles; }
        int f_get_ttlExp() { return this->m_ttlExp; }
        int f_get_ttlMonKill() { return this->m_ttlMonstersKilled; }
        _facedirection_ f_getFaceDir() { return this->m_CurrentFaceDir; }

      private:
        std::string m_Name;
        int m_Health = 0;
        int m_Mana = 0;
        int m_Str = 0;
        int m_Dex = 0;
        int m_Int = 0;
        int m_Gold = 0;
        int m_Level = 1;
        int m_maxHealth = 100;
        int m_maxMana = 100;
        int m_def = 10;
        int m_luck = 5;   // for crit + gold drop
        int m_agil = 10;  // for dodge chance

        int m_ttlBattles = 0;
        int m_ttlMonstersKilled = 0;
        int m_ttlExp = 0;

        game::asset::entity::RACE       m_Race;
        game::asset::entity::BASE_CLASS m_JobClass;
        _facedirection_ m_CurrentFaceDir = _facedirection_::DOWN;
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
