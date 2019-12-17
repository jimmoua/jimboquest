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

  /* Monster textures */
  static sf::Texture _monster_slimeTexture;

  /* musics */
  static std::map<game::asset::MUSIC, sf::Music*> _gameMusic;

  /* Sounds */
  static std::map<game::asset::snd, sf::Sound> _gameSound;

  /* Face data */
  static std::map<game::asset::ENTITY_FACE, sf::Sprite> _entityFaceSprite;

}

////////////////////////////////////////////////////////////////////////////////
// INITIALIZER FUNCTION FOR game::asset
////////////////////////////////////////////////////////////////////////////////
void game::asset::init() {

  ////////////////////////////////////////////////// 
  // Load Music Lambda Function
  ////////////////////////////////////////////////// 
  auto lambda_CreateMus = [](const MUSIC& id, const std::string& s) {
    _gameMusic[id] = new sf::Music;
    if(!_gameMusic[id]->openFromFile(s)) {
      delete _gameMusic[id];
      std::cerr << "Unable to create music from path: " << s << std::endl;
      exit(1);
    }
  };

  ////////////////////////////////////////////////// 
  // GAME FONT
  ////////////////////////////////////////////////// 
  _font.loadFromFile("data/font/oldschooladventures.ttf");

  ////////////////////////////////////////////////// 
  // IMAGES
  // Load images for scenenic purposes.
  // These may include faces (may need seperation
  // layer on), backgrounds, parallaxes, etc.
  ////////////////////////////////////////////////// 
  _imgLoc[asset::img::TS_BG] = "data/bg/titlescreen.png";
  _imgLoc[asset::img::ACTOR_PNG] = "data/entity/actor/DQ_CharacterSet.png";

  ////////////////////////////////////////////////// 
  // GAME MAP LOCATIONS USING STRINGS
  ////////////////////////////////////////////////// 
  _mapLoc[MAP::TEST_MAP00] = "data/map/testMap00.txt";
  _mapLoc[MAP::TEST_MAP01] = "data/map/testMap01.txt";
  _mapLoc[MAP::TEST_MAP02] = "data/map/testMap02.txt";
  _mapLoc[MAP::TEST_MAP02] = "data/map/testMap02.txt";
  _mapLoc[MAP::TEST_MAP_ALPHA] = "data/map/testMapAlpha.txt";

  ////////////////////////////////////////////////// 
  // GAME TEXTURES
  ////////////////////////////////////////////////// 
  static sf::Image tileSetImage;
  tileSetImage.loadFromFile("data/tileset/DQ_Tileset.png");
  tileSetImage.createMaskFromColor(sf::Color(255,121,155));
  _mapTexture.loadFromImage(tileSetImage);

  static sf::Image actorImage;
  actorImage.loadFromFile(_imgLoc[asset::img::ACTOR_PNG]);
  actorImage.createMaskFromColor(sf::Color::Magenta);
  _actorTexture.loadFromImage(actorImage);

  ////////////////////////////////////////////////// 
  // Music for the game, and definition of lambda
  // function to dynamically load music
  ////////////////////////////////////////////////// 
  lambda_CreateMus(MUSIC::AMBI_WIND,   "data/music/AMB_wind.ogg");
  lambda_CreateMus(MUSIC::TITLESCREEN, "data/music/beauitful_memories.ogg");

  ////////////////////////////////////////////////// 
  // Sound buffers For Environment/Menu/ETC
  ////////////////////////////////////////////////// 
  static sf::SoundBuffer SB_menuHover;
  static sf::SoundBuffer SB_menuSubmit;
  static sf::SoundBuffer SB_menuCancel;
  static sf::SoundBuffer SB_menuAppear;
  static sf::SoundBuffer SB_menuDisappear;
  static sf::SoundBuffer SB_env_ft_grass;

  SB_menuHover.loadFromFile("data/sound/sound_menu_hover.ogg");
  SB_menuSubmit.loadFromFile("data/sound/sound_menu_submit.ogg");
  SB_menuCancel.loadFromFile("data/sound/sound_menu_cancle.ogg");
  SB_menuAppear.loadFromFile("data/sound/sound_menu_appear.ogg");
  SB_menuDisappear.loadFromFile("data/sound/sound_menu_blocked.ogg");
  SB_env_ft_grass.loadFromFile("data/sound/env/ft_grass2.ogg");

  _gameSound[snd::MENU_HOVER].setBuffer(SB_menuHover);
  _gameSound[snd::MENU_SUBMIT].setBuffer(SB_menuSubmit);
  _gameSound[snd::MENU_CANCEL].setBuffer(SB_menuCancel);
  _gameSound[snd::MENU_APPEAR].setBuffer(SB_menuAppear);
  _gameSound[snd::MENU_DISAPPEAR].setBuffer(SB_menuDisappear);
  _gameSound[snd::FOOTSTEPS_GRASS].setBuffer(SB_env_ft_grass);
  _gameSound[snd::FOOTSTEPS_GRASS].setVolume(50);

  ////////////////////////////////////////////////// 
  // Player Face Data
  ////////////////////////////////////////////////// 
  static sf::Image __playerfaceImage__;
  __playerfaceImage__.loadFromFile("data/entity/actor/face/roto.png");
  __playerfaceImage__.createMaskFromColor(sf::Color::Magenta);
  static sf::Texture __playerfaceTexture__;
  __playerfaceTexture__.loadFromImage(__playerfaceImage__);
  _entityFaceSprite[game::asset::ENTITY_FACE::PLAYER].setTexture(__playerfaceTexture__);
  _entityFaceSprite[game::asset::ENTITY_FACE::PLAYER].setScale(0.75, 0.75);

  ////////////////////////////////////////////////// 
  // Load monster images and textures
  ////////////////////////////////////////////////// 
  static sf::Image _monsterImageSlime;
  _monsterImageSlime.loadFromFile("data/entity/monster/slimes.png");
  _monsterImageSlime.createMaskFromColor(sf::Color::Magenta);
  _monster_slimeTexture.loadFromImage(_monsterImageSlime);
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


sf::Text game::asset::createString(const std::string s, const float ts)
{
  sf::Text t;
  t.setFont(_font);
  t.setString(s);
  t.setCharacterSize(ts);
  t.setFillColor(sf::Color::White);
  t.setOutlineColor(sf::Color::Black);
  t.setOutlineThickness(3.f);
  return t;
}

sf::Text game::asset::createString(const std::string s)
{
  sf::Text t;
  t.setFont(_font);
  t.setString(s);
  t.setCharacterSize(32);
  t.setFillColor(sf::Color::White);
  t.setOutlineColor(sf::Color::Black);
  t.setOutlineThickness(2.5f);
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

sf::Sprite& game::asset::getFaceSprite(const game::asset::ENTITY_FACE& id) {
  return _entityFaceSprite[id];
}

sf::Texture& game::asset::monster::getTexture_Slimes() {
  return _monster_slimeTexture;
}
