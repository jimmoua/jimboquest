#include "asset.hpp"

namespace {
  // Create a map container that contains string to path of images
  static std::map<game::asset::img, std::string> _imgLoc;
  static sf::Font _font;
}

void game::asset::init() {
  /* In this function, init the assets. This means get the string locs for
   * assets and other useful things... */
  _imgLoc[asset::img::TS_BG] = "data/bg/titlescreen.png";
  _font.loadFromFile("data/font/oldschooladventures.ttf");
}

sf::Text game::asset::createString(const std::string s,
                                   const ushort ts,
                                   const sf::Color fc,
                                   const sf::Color oc,
                                   const float ot)
{
  sf::Text t;
  t.setFont(_font);
  t.setString(s);
  t.setCharacterSize(ts);
  t.setFillColor(fc);
  t.setOutlineColor(oc);
  t.setOutlineThickness(ot);
  return t;
}

void game::asset::setTxtOriginCenter(sf::Text& t) {
  t.setOrigin(t.getGlobalBounds().left + t.getGlobalBounds().width/2,
              t.getGlobalBounds().top + t.getGlobalBounds().height/2);
}
