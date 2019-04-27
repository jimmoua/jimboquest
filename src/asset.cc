#include "asset.hpp"
#include <iostream>

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

  /* musics */
  static std::map<game::asset::MUSIC, sf::Music*> _gameMusic;

  /* Sounds */
  static std::map<game::asset::snd, sf::Sound> _gameSound;

}

void game::asset::init() {

  auto lamda_CreateMus = [](const MUSIC& id, const std::string& s) {
    sf::Music *t = new sf::Music;
    if(!t->openFromFile(s)) {
      delete t;
      std::cerr << "Unable to create music from path: " << s << std::endl;
      exit(1);
    }
    else
      _gameMusic.insert(std::pair<MUSIC, sf::Music*>(id, t));
  };

  /* Font location. I am only using 1 font for my game, so no need for maps */
  _font.loadFromFile("data/font/oldschooladventures.ttf");
  /* In this function, init the assets. This means get the string locs for
   * assets and other useful things... */
  _imgLoc[asset::img::TS_BG] = "data/bg/titlescreen.png";
  _imgLoc[asset::img::ACTOR_PNG] = "data/entity/actor/DQ_CharacterSet.png";

  /* Game map locations */
  _mapLoc[MAP::TEST_MAP00] = "data/map/testMap00.txt";
  _mapLoc[MAP::TEST_MAP01] = "data/map/testMap01.txt";
  _mapLoc[MAP::TEST_MAP02] = "data/map/testMap02.txt";

  /* Game textures load from file */
  _mapTexture.loadFromFile("data/tileset/DQ_Tileset.png");

  static sf::Image actorImage;
  actorImage.loadFromFile(_imgLoc[asset::img::ACTOR_PNG]);
  actorImage.createMaskFromColor(sf::Color::Magenta);
  _actorTexture.loadFromImage(actorImage);

  /* musics for the game */

  lamda_CreateMus(MUSIC::AMBI_WIND, "data/music/AMB_wind.ogg");
  lamda_CreateMus(MUSIC::TITLESCREEN, "data/music/BetweenWorlds.ogg");

  /* Sound buffers for the game */
  static sf::SoundBuffer SB_menuHover;
  static sf::SoundBuffer SB_menuSubmit;
  static sf::SoundBuffer SB_menuCancel;
  static sf::SoundBuffer SB_menuAppear;
  static sf::SoundBuffer SB_menuDisappear;

  /* Sounds for environment */
  static sf::SoundBuffer SB_env_ft_grass;


  SB_menuHover.loadFromFile("data/sound/sound_menu_hover.ogg");
  SB_menuSubmit.loadFromFile("data/sound/sound_menu_submit.ogg");
  SB_menuCancel.loadFromFile("data/sound/sound_menu_cancle.ogg");
  SB_menuAppear.loadFromFile("data/sound/sound_menu_appear.ogg");
  SB_menuDisappear.loadFromFile("data/sound/sound_menu_blocked.ogg");

  SB_env_ft_grass.loadFromFile("data/sound/env/ft_grass.ogg");

  _gameSound[snd::MENU_HOVER].setBuffer(SB_menuHover);
  _gameSound[snd::MENU_SUBMIT].setBuffer(SB_menuSubmit);
  _gameSound[snd::MENU_CANCEL].setBuffer(SB_menuCancel);
  _gameSound[snd::MENU_APPEAR].setBuffer(SB_menuAppear);
  _gameSound[snd::MENU_DISAPPEAR].setBuffer(SB_menuDisappear);
  _gameSound[snd::FOOTSTEPS_GRASS].setBuffer(SB_env_ft_grass);

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

sf::Text game::asset::createString(const std::string s)
{
  sf::Text t;
  t.setFont(_font);
  t.setString(s);
  t.setCharacterSize(36);
  t.setFillColor(sf::Color::White);
  t.setOutlineColor(sf::Color::Black);
  t.setOutlineThickness(3.f);
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

sf::Sound& game::asset::getSound(const game::asset::snd& id) {
  return _gameSound[id];
}

sf::Music& game::asset::getMusic(const game::asset::MUSIC& id) {
  return *_gameMusic[id];
}

void game::asset::MusicClean() {
  for(auto iter = _gameMusic.begin(); iter!= _gameMusic.end();iter++)
  {
    delete iter->second;
  }
}
