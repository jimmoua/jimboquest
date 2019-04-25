#include "asset.hpp"

namespace {
  // Create a map container that contains string to path of images
  static std::map<game::asset::img, std::string> _imgLoc;
  static sf::Font _font;

  // Map container for strings to path of maps
  static std::map<game::asset::MAP, std::string> _mapLoc;

  /* Game texture for map */
  static sf::Texture _mapTexture;

  /* Actor sprite textures */
  static sf::Texture _actorTexture;

  /* Sounds */
  static std::map<game::asset::snd, sf::Sound> _gameSound;
}

void game::asset::init() {

  /* Font location. I am only using 1 font for my game, so no need for maps */
  _font.loadFromFile("data/font/oldschooladventures.ttf");
  /* In this function, init the assets. This means get the string locs for
   * assets and other useful things... */
  _imgLoc[asset::img::TS_BG] = "data/bg/titlescreen.png";
  _imgLoc[asset::img::ACTOR_PNG] = "data/entity/actor/actorSheet.png";

  /* Game map locations */
  _mapLoc[MAP::TEST_MAP00] = "data/map/testMap00.txt";
  _mapLoc[MAP::TEST_MAP01] = "data/map/testMap01.txt";
  _mapLoc[MAP::TEST_MAP02] = "data/map/testMap02.txt";

  /* Game textures load from file */
  _mapTexture.loadFromFile("data/tileset/jimboTiles/jimboTiles.png");
  _actorTexture.loadFromFile(_imgLoc[asset::img::ACTOR_PNG]);

  /* Sound buffers for the game */
  static sf::SoundBuffer SB_menuHover;
  static sf::SoundBuffer SB_menuSubmit;


  SB_menuHover.loadFromFile("data/sound/sound_menu_hover.ogg");
  SB_menuSubmit.loadFromFile("data/sound/sound_menu_submit.ogg");

  _gameSound[snd::MENU_HOVER].setBuffer(SB_menuHover);
  _gameSound[snd::MENU_SUBMIT].setBuffer(SB_menuSubmit);

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

sf::Texture& game::asset::mapTexture() {
  return _mapTexture;
}

sf::Texture& game::asset::actorTexture() {
  return _actorTexture;
}

const std::string game::asset::getMapName(const game::asset::MAP& ID) {
  return _mapLoc[ID];
}

sf::Sound& game::asset::getSound(const game::asset::snd& se) {
  return _gameSound[se];
}
