#include "map.hpp"
#include "game.hpp"

namespace {

  static std::vector< std::vector<size_t> >     _map_lay01;   // Layer 1
  static std::vector< std::vector<sf::Sprite> > _map_lay01_S; // L1 sprites

  static std::vector< std::vector<size_t> >     _map_lay02;   // Layer 2
  static std::vector< std::vector<sf::Sprite> > _map_lay02_S; // L2 sprites

  static std::vector< std::vector<size_t> >     _map_lay03;   // Layer 3
  static std::vector< std::vector<sf::Sprite> > _map_lay03_S; // L3 sprites

  static std::vector< std::vector<size_t> >     _map_EvLay;   // Event layer

  /* Need to make some data structures to define some events */
  static std::vector< std::vector<game::map_ns::mapEvStruct> > _mapEvV;
}

void game::map_ns::loadMap(const std::string& mapName) {

  std::ifstream infile(mapName);
  if(!infile) {
    std::cerr << "Unable to open map: " << mapName << std::endl;
    std::cerr << "Verify the integrity of " << mapName << std::endl;
    exit(1);
  }
  unsigned short int _row, _col;
  /* The first two numbers in the map file are always row and col */
  infile >> _row >> _col;
  const ushort row = _row;
  const ushort col = _col;

  /* Before reading into the vectors, clear them out */
  if(!_map_lay01.empty()) {
    _map_lay01.clear();
  }
  if(!_map_lay02.empty()) {
    _map_lay02.clear();
  }
  if(!_map_lay03.empty()) {
    _map_lay03.clear();
  }

  /* Read in the first layer */
  _map_lay01.resize(row);
  for(auto& i : _map_lay01) {
    i.resize(col);
  }
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_lay01[i][j];
    }
  }

  /* Read in the second layer */
  _map_lay02.resize(row);
  for(auto& i : _map_lay02) {
    i.resize(col);
  }
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_lay02[i][j];
    }
  }

  /* Read in the third layer */
  _map_lay03.resize(row);
  for(auto& i : _map_lay03) {
    i.resize(col);
  }
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_lay03[i][j];
    }
  }

  /* Read in the event layer */
  _map_EvLay.resize(row);
  for(auto& i : _map_EvLay) {
    i.resize(col);
  }
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_EvLay[i][j];
    }
  }

  if(infile.peek() == '\0') {
    std::cerr << "Error: detected extra bits at the end of the map\n";
    infile.close();
    exit(1);
  }
  infile.close();

  /* Now that we have read in the numbers, we have to scale in the sprites.
   * We do this first by clearing out the sprite vectors and then allocating
   * space for them using the resize function. */

  _map_lay01_S.clear();
  _map_lay02_S.clear();
  _map_lay03_S.clear();
  _mapEvV.clear();
  //_map_EvLay_S.clear();

  _map_lay01_S.resize(row);   // Resize first sprite layer
  for(auto& i : _map_lay01_S) {
    i.resize(col);
  }
  _map_lay02_S.resize(row);   // Resize collisions sprite layer
  for(auto& i : _map_lay02_S) {
    i.resize(col);
  }
  _map_lay03_S.resize(row);   // Resize passthrough sprite layer
  for(auto& i : _map_lay03_S) {
    i.resize(col);
  }
  _mapEvV.resize(row);        // Resize the event vector layer
  for(auto& i : _mapEvV) {
    i.resize(col);
  }

  for(auto& i : _map_lay01_S) {
    for(auto& j : i) {
      j.setScale(SPRITE_SCALE, SPRITE_SCALE);
    }
  }
  for(auto& i : _map_lay02_S) {
    for(auto& j : i) {
      j.setScale(SPRITE_SCALE, SPRITE_SCALE);
    }
  }
  for(auto& i : _map_lay03_S) {
    for(auto& j : i) {
      j.setScale(SPRITE_SCALE, SPRITE_SCALE);
    }
  }
  for(auto& i : _mapEvV) {
    for(auto& j : i) {
      j._mapEv_Sp.setScale(SPRITE_SCALE, SPRITE_SCALE);
    }
  }

  /* After allocating space and resizing the sprites, now we set the textures
   * for each of the sprite depending on what the data was for the first layer.
   * */
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      if(_map_lay01[i][j] == 1) {
        _map_lay01_S[i][j].setTexture(game::asset::mapTexture());
        _map_lay01_S[i][j].setTextureRect(sf::IntRect(0,0,_SS,_SS));
      }
      else if(_map_lay01[i][j] == 2) {
        _map_lay01_S[i][j].setTexture(game::asset::mapTexture());
        _map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS,0,_SS,_SS));
      }
      else if(_map_lay01[i][j] == 3) {
        _map_lay01_S[i][j].setTexture(game::asset::mapTexture());
        _map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*2,0,_SS,_SS));
      }
      else if(_map_lay01[i][j] == 4) {
        _map_lay01_S[i][j].setTexture(game::asset::mapTexture());
        _map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*3,0,_SS,_SS));
      }
      else if(_map_lay01[i][j] == 5) {
        _map_lay01_S[i][j].setTexture(game::asset::mapTexture());
        _map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*4,0,_SS,_SS));
      }
      else if(_map_lay01[i][j] == 6) {
        _map_lay01_S[i][j].setTexture(game::asset::mapTexture());
        _map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*5,0,_SS,_SS));
      }
      _map_lay01_S[i][j].setPosition(_SLOC*(row-i-1), _SLOC*(col-j-1));
    }
  }
  /* Now do the same thing for the collisions layer */
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      if(_map_lay02[i][j] == 1) {
        _map_lay02_S[i][j].setTextureRect(sf::IntRect(00,00,_SS,_SS));
        _map_lay02_S[i][j].setPosition(_SLOC*(row-i-1), _SLOC*(col-j-1));
      }
    }
  }
  /* Now do the same thing for the events layer */
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      if(_map_EvLay[i][j] == 1) {
        _mapEvV[i][j]._mapEv_Sp.setTextureRect(sf::IntRect(00,00,_SS,_SS));
        _mapEvV[i][j]._mapEv_Sp.setPosition(_SLOC*(row-i-1), _SLOC*(col-j-1));
        _mapEvV[i][j].ev = game::map_ns::TILE_EV::PORTAL;
      }
      else {
        _mapEvV[i][j].ev = game::map_ns::TILE_EV::NONE;
      }
    }
  }
}

void game::map_ns::displayMap_L1() {

  while(win::getWin().pollEvent(win::getEv())) {

    if(win::getEv().type == sf::Event::Closed) {
      game::setGS(game::asset::GS::NONE);
      return;
    }

  }

  /* Clear the screen black */
  win::getWin().clear(sf::Color::Black);
  for(auto& i : _map_lay01_S) {
    for(auto& j : i) {
      win::getWin().draw(j);
    }
  }

}

std::vector< std::vector<sf::Sprite> >& game::map_ns::getColSpr() {
  return _map_lay02_S;
}

std::vector< std::vector<game::map_ns::mapEvStruct> >& game::map_ns::getEvStructV() {

  /* Returns the map event vector which contains
   *   1. Enumerated data type that indicated the type of event
   *   2. The sprite. */

  return _mapEvV;

}
