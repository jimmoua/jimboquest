#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "window.hpp"
#include "asset.hpp"
#include "title.hpp"
#include "map.hpp"

namespace game {
  void init();

  // run the show
  void run();

  // get current game state
  const asset::GS& getGS();

  void setGS(const asset::GS);
}
