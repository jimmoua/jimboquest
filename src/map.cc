#include "map.hpp"
#include "game.hpp"
#include "asset.hpp"


namespace {

  /* Current map enum */
  static game::asset::MAP currentMap = game::asset::MAP::NONE;

}

namespace {

  static game::map_ns::MapInfo testMap00(game::asset::MAP::TEST_MAP00, "tstMap00");
  static game::map_ns::MapInfo testMap01(game::asset::MAP::TEST_MAP01, "tstMap01");
  static game::map_ns::MapInfo testMap02(game::asset::MAP::TEST_MAP02, "tstMap02");

  /* Making a std::map so we can map map enums to objects */
  static std::map<game::asset::MAP, game::map_ns::MapInfo*> mapInfoContainerMap;
}

void game::map_ns::init() {

  /* INIT FUNCTION */

  /* A lambda function so we can read from the map files to create maps */
  auto createMap = [](std::string mapName, MapInfo* mapObj) {
    std::ifstream infile;
    infile.open(mapName.c_str());
    if(!infile) {
      std::cerr << "Unable to open map: " << mapName << std::endl;
      exit(1);
    }
    size_t row, col;
    infile >> row >> col;
    /* Indicate the map size */
    mapObj->_mapSize = sf::Vector2i(row, col);
    /* Resize the layers before doing anything */
    mapObj->_map_lay01.resize(row);
    for(auto& i : mapObj->_map_lay01) {
      /* layer 1 resize */
      i.resize(col);
    }
    mapObj->_map_lay02.resize(row);
    for(auto& i : mapObj->_map_lay02) {
      /* layer 2 resize */
      i.resize(col);
    }
    mapObj->_map_lay03.resize(row);
    for(auto& i : mapObj->_map_lay03) {
      /* layer 3 resize */
      i.resize(col);
    }
    mapObj->_map_EvLay.resize(row);
    for(auto& i : mapObj->_map_EvLay) {
      /* event layer resize */
      i.resize(col);
    }
    mapObj->evV.resize(row);
    for(auto& i : mapObj->evV) {
      /* Resize the vector containing information about event */
      i.resize(col);
    }

    /* READ IN THE LAYERS */
    for(size_t i = 0; i < row; i++) {
      /* Layer 1 read in */
      for(size_t j = 0; j < col; j++) {
        infile >> mapObj->_map_lay01[i][j];
      }
    }
    for(size_t i = 0; i < row; i++) {
      /* Layer 2 read in */
      for(size_t j = 0; j < col; j++) {
        infile >> mapObj->_map_lay02[i][j];
      }
    }
    for(size_t i = 0; i < row; i++) {
      /* Layer 3 read in */
      for(size_t j = 0; j < col; j++) {
        infile >> mapObj->_map_lay03[i][j];
      }
    }
    for(size_t i = 0; i < row; i++) {
      for(size_t j = 0; j < col; j++) {
        infile >> mapObj->_map_EvLay[i][j];
      }
    }

    /* If reading went well, we should be ok...
     * TODO: Implement error checking later */
    infile.close();

    /* Clear the sprites */
    mapObj->_map_lay01_S.clear();
    mapObj->_map_lay02_S.clear();
    mapObj->_map_lay03_S.clear();

    /* Resize sprites */
    mapObj->_map_lay01_S.resize(row);
    for(auto& i : mapObj->_map_lay01_S) {
      i.resize(col);
    }
    mapObj->_map_lay02_S.resize(row);
    for(auto& i : mapObj->_map_lay02_S) {
      i.resize(col);
    }
    mapObj->_map_lay03_S.resize(row);
    for(auto& i : mapObj->_map_lay03_S) {
      i.resize(col);
    }
    mapObj->_mapEvV.resize(row);
    for(auto& i : mapObj->_mapEvV) {
      i.resize(col);
    }

    /* Scale the sprites */
    for(auto& i : mapObj->_map_lay01_S) {
      for(auto& j : i) {
        j.setScale(SPRITE_SCALE, SPRITE_SCALE);
      }
    }
    for(auto& i : mapObj->_map_lay02_S) {
      for(auto& j : i) {
        j.setScale(SPRITE_SCALE, SPRITE_SCALE);
      }
    }
    for(auto& i : mapObj->_map_lay03_S) {
      for(auto& j : i) {
        j.setScale(SPRITE_SCALE, SPRITE_SCALE);
      }
    }
    for(auto& i : mapObj->_mapEvV) {
      for(auto& j : i) {
        j.setScale(SPRITE_SCALE, SPRITE_SCALE);
      }
    }
    /* After allocating space and resizing the sprites, now we set the textures
     * for each of the sprite depending on what the data was for the first
     * layer. */
    for(size_t i = 0; i < row; i++) {
      for(size_t j = 0; j < col; j++) {
        if(mapObj->_map_lay01[i][j] == 1) {
          /* Black (nothing tile) */
          mapObj->_map_lay01_S[i][j].setTexture(game::asset::mapTexture());
          mapObj->_map_lay01_S[i][j].setTextureRect(sf::IntRect(0,0,_SS,_SS));
        }
        else if(mapObj->_map_lay01[i][j] == 2) {
          /* Grass tile */
          mapObj->_map_lay01_S[i][j].setTexture(game::asset::mapTexture());
          mapObj->_map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS,0,_SS,_SS));
        }
        else if(mapObj->_map_lay01[i][j] == 3) {
          /* Water tile */
          mapObj->_map_lay01_S[i][j].setTexture(game::asset::mapTexture());
          mapObj->_map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*2,0,_SS,_SS));
        }
        else if(mapObj->_map_lay01[i][j] == 4) {
          /* Stone tile */
          mapObj->_map_lay01_S[i][j].setTexture(game::asset::mapTexture());
          mapObj->_map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*3,0,_SS,_SS));
        }
        else if(mapObj->_map_lay01[i][j] == 5) {
          /* Dirt tile */
          mapObj->_map_lay01_S[i][j].setTexture(game::asset::mapTexture());
          mapObj->_map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*4,0,_SS,_SS));
        }
        else if(mapObj->_map_lay01[i][j] == 6) {
          mapObj->_map_lay01_S[i][j].setTexture(game::asset::mapTexture());
          mapObj->_map_lay01_S[i][j].setTextureRect(sf::IntRect(_SS*5,0,_SS,_SS));
        }
        mapObj->_map_lay01_S[j][i].setPosition(_SLOC*(i), _SLOC*(j));
      }
    }

    /* Noticed above how I set the position using the [i][j] subscripting.
     * In the below, I do [j][i] subscripting. This works perfectly. I do not
     * know why, but do not try to apply anymore "fixes". I have come to terms
     * that this is just the way it will be done. */

    /* Define data for the collisions layer */
    for(size_t i = 0; i < row; i++) {
      for(size_t j = 0; j < col; j++) {
        if(mapObj->_map_lay02[i][j] == 1) {
          mapObj->_map_lay02_S[i][j].setTextureRect(sf::IntRect(00,00,_SS,_SS));
          mapObj->_map_lay02_S[i][j].setPosition(_SLOC*(j), _SLOC*(i));
        }
      }
    }

    /* Define data for the events layer */
    for(size_t i = 0; i < row; i++) {
      for(size_t j = 0; j < col; j++) {
        if(mapObj->_map_EvLay[i][j] == 1) {
          /* If it is a portal */
          mapObj->_mapEvV[i][j].setTexture(asset::mapTexture());
          mapObj->_mapEvV[i][j].setTextureRect(sf::IntRect(_SS*0,_SS,_SS,_SS));
          mapObj->_mapEvV[i][j].setPosition(_SLOC*(j), _SLOC*(i));
          std::cout << "Index of portal is " << i << " " << j << std::endl;
          mapObj->evV[i][j].ev = game::map_ns::TILE_EV::PORTAL;
        }
        else {
          mapObj->evV[i][j].ev = game::map_ns::TILE_EV::NONE;
        }
      }
    }

    std::clog << "Successfully created map: " << mapName << "\n\n";

  };
  /* Map the object to a std::map */
  mapInfoContainerMap[game::asset::MAP::TEST_MAP00] = &testMap00;
  mapInfoContainerMap[game::asset::MAP::TEST_MAP01] = &testMap01;
  mapInfoContainerMap[game::asset::MAP::TEST_MAP02] = &testMap02;

  /* Create the map from the lambda */
  createMap(asset::getMapName(asset::MAP::TEST_MAP00), &testMap00);
  createMap(asset::getMapName(asset::MAP::TEST_MAP01), &testMap01);
  createMap(asset::getMapName(asset::MAP::TEST_MAP02), &testMap02);


  /* When placing portals, remember that the sprites are inverted accross the
   * Cartesian-like x-y plane!!
   *
   * So if we have an index at i j, we need to define the second (of the pair)
   * to be j i.
   *
   * Well, my math seems to suck, so that's probably a reason why it's like
   * that. I'm too lazy to apply a fix, so I will just leave it as it is */

  /* --------------------------------------------------------------------------
   * TEST_MAP00 PORTALS
   * ------------------------------------------------------------------------*/
  /* Event at [1][3] is a portal that leads to TEST_MAP02 */
  testMap00.evV[1][3].portalTransportLoc.first = game::asset::MAP::TEST_MAP02;
  testMap00.evV[1][3].portalTransportLoc.second = sf::Vector2f(2, 5);
  /* Event at [3][5] is a portal that leads to TEST_MAP01 */
  testMap00.evV[3][5].portalTransportLoc.first = game::asset::MAP::TEST_MAP01;
  testMap00.evV[3][5].portalTransportLoc.second = sf::Vector2f(1, 3);

  /* --------------------------------------------------------------------------
   * TEST_MAP01 PORTALS
   * ------------------------------------------------------------------------*/
  testMap01.evV[3][1].portalTransportLoc.first = game::asset::MAP::TEST_MAP00;
  testMap01.evV[3][1].portalTransportLoc.second = sf::Vector2f(5, 3);


  /* --------------------------------------------------------------------------
   * TEST_MAP02
   * ------------------------------------------------------------------------*/
  testMap02.evV[5][2].portalTransportLoc.first = game::asset::MAP::TEST_MAP00;
  testMap02.evV[5][2].portalTransportLoc.second = sf::Vector2f(3, 1);
}


void game::map_ns::loadMap(const game::asset::MAP& mapID, const sf::Vector2f playerPos) {
  /* TODO: implement correct loading functions -> plan */
  //std::cout << "At least it compiles.\n"; exit(1);
  entity::getPl()->m_enSprite.setPosition(playerPos.x*_SLOC, playerPos.y*_SLOC);
  setMapID(mapID);
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
  for(auto& i : getMapObjectByID(currentMap)->_map_lay01_S) {
    for(auto& j : i) {
      win::getWin().draw(j);
    }
  }
  for(auto& i : getMapObjectByID(currentMap)->_mapEvV) {
    for(auto& j : i) {
      win::getWin().draw(j);
    }
  }

}

game::map_ns::MapInfo* game::map_ns::getMapObjectByID(const game::asset::MAP& mapID) {
  return mapInfoContainerMap[mapID];
}

const game::asset::MAP& game::map_ns::getCurrentMapID() {
  return currentMap;
}

void game::map_ns::setMapID(const game::asset::MAP& ID) {
  currentMap = ID;
}
