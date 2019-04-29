#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.hpp"
#include "asset.hpp"
#include <thread>
#include <vector>

using ushort = unsigned short int;

/* Scaling the sprite by 6 because  16 pixels are very small on a 1600x900
 * screen. */
constexpr static ushort SPRITE_SCALE = 6;         // Sprite scale
constexpr static ushort _SS = 16;                 // Sprite size 
constexpr static int _SLOC = _SS*SPRITE_SCALE;    // Useful for pos setting
constexpr static int __PORTAL_OFFSET__ = 15;      // For portal offset


namespace game {

  std::vector<std::thread>& thread_vector();

  void init();

  // run the show
  void run();

  // get current game state
  const asset::GS& getGS();

  void setGS(const asset::GS);
}

#endif
