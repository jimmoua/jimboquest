#include "map.hpp"

namespace {

  /* Scaling the sprite by 6 because  16 pixels are very small on a 1600x900
   * screen. */
  constexpr static unsigned short int SPRITE_SCALE = 6;   // Sprite scale
  constexpr static unsigned short int _SS = 16;           // Sprite size

  static std::vector< std::vector<size_t> > _map_lay01;   // Layer 1
  static std::vector< std::vector<sf::Sprite> > _map_lay01_S;

  static std::vector< std::vector<size_t> > _map_lay02;   // Layer 2
  static std::vector< sf::Sprite >          _map_lay02_S; // Layer 2 sprites

  static std::vector< std::vector<size_t> > _map_lay03;   // Layer 3
  static std::vector< sf::Sprite >          _map_lay03_S; // Layer 3 sprites

  static std::vector< std::vector<size_t> > _map_EvLay;   // Event layer
  static std::vector< sf::Sprite >          _map_EvLay_S; // Event sprites
}

void game::map::loadMap(const std::string& mapName) {

  std::ifstream infile(mapName);
  if(!infile) {
    std::cerr << "Unable to open map: " << mapName << std::endl;
    std::cerr << "Verify the integrity of " << mapName << std::endl;
    exit(1);
  }
  unsigned short int row, col;
  /* The first two numbers in the map file are always row and col */
  infile >> row >> col;
  std::cout << "Row and col are " << row << " " << col << std::endl;

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
                              //for(size_t i = 0; i < row; i++) {
                                //for(size_t j = 0; j < col; j++) {
                                  //std::cout << "  " << _map_lay01[i][j];
                                //}
                                //std::cout << std::endl;
                              //}
                              //exit(0);

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

  _map_lay01.resize(row);   // Resize first layer
  for(auto& i : _map_lay01) {
    i.reserve(col);
  }
  _map_lay02.resize(row);   // Resize second layer
  for(auto& i : _map_lay02) {
    i.reserve(col);
  }
  _map_lay03.resize(row);   // Resize third layer
  for(auto& i : _map_lay03) {
    i.reserve(col);
  }
  _map_lay01_S.resize(row);   // Resize first sprite layer
  for(auto& i : _map_lay01_S) {
    i.resize(col);
  }

  //_map_lay01_S.resize(row*col);   // Resize first layer sprite
  //_map_lay02_S.resize(row*col);   // Resize second layer sprite
  //_map_lay03_S.resize(row*col);   // Resize third layer sprite

  for(auto& i : _map_lay01_S) {
    for(auto& j : i) {
      j.setScale(SPRITE_SCALE, SPRITE_SCALE);
    }
  }
  for(auto& i : _map_lay02_S) {
    i.setScale(SPRITE_SCALE, SPRITE_SCALE);
  }
  for(auto& i : _map_lay03_S) {
    i.setScale(SPRITE_SCALE, SPRITE_SCALE);
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
        std::cout << "3";
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
      _map_lay01_S[i][j].setPosition(_SS*SPRITE_SCALE*i, _SS*SPRITE_SCALE*j);
      std::cout << "  " << _map_lay01[i][j] << std::endl;
    }
  }

}

void game::map::displayMap() {
  while(win::getWin().pollEvent(win::getEv())) {
    if(win::getEv().type == sf::Event::Closed) {
      game::setGS(game::asset::GS::NONE);

      // DEBUG
      for(size_t i = 0; i < 5; i++) {
        for(size_t j = 0; j < 5; j++) {
      std::cout << _map_lay01_S[i][j].getPosition().x << " " <<
        _map_lay01_S[i][j].getPosition().y << std::endl;
        }
      }

      return;
    }
  }
  win::getWin().clear(sf::Color::Black);
  for(auto& i : _map_lay01_S) {
    for(auto& j : i) {
      win::getWin().draw(j);
    }
  }
  win::getWin().display();
}
