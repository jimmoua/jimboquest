#include "asset.hpp"

namespace {
  // Create a map container that contains string to path of images
  static std::map<game::asset::img, std::string> _imgLoc;
  static sf::Font _font;

  // Map container for strings to path of maps
  static std::map<game::asset::MAP, std::string> _mapLoc;

  /* Game texture for map */
  static sf::Texture _mapTexture;
}

void game::asset::init() {

  /* Font location. I am only using 1 font for my game, so no need for maps */
  _font.loadFromFile("data/font/oldschooladventures.ttf");
  /* In this function, init the assets. This means get the string locs for
   * assets and other useful things... */
  _imgLoc[asset::img::TS_BG] = "data/bg/titlescreen.png";

  /* Game map locations */
  _mapLoc[MAP::TEST_MAP00] = "data/map/testMap00.txt";
  _mapLoc[MAP::TEST_MAP01] = "data/map/testMap01.txt";
  _mapLoc[MAP::TEST_MAP02] = "data/map/testMap02.txt";

  _mapTexture.loadFromFile("data/tileset/jimboTiles/jimboTiles.png");

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

sf::Texture* game::asset::mapTexture() {
  return &_mapTexture;
}
