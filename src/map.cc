#include "map.hpp"
#include "game.hpp"
#include "asset.hpp"
#include "entity.hpp"
#include "animations.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstdio>
#include <thread>

namespace {

  using cor = std::pair<int,int>;

  /* Current map enum */
  static game::asset::MAP currentMap = game::asset::MAP::NONE;
}

namespace {

  static game::map_ns::MapInfo testMap00(game::asset::MAP::TEST_MAP00, "tstMap00", game::map_ns::MAP_LEVEL::DANGER_ZONE);
  static game::map_ns::MapInfo testMap01(game::asset::MAP::TEST_MAP01, "tstMap01", game::map_ns::MAP_LEVEL::DANGER_ZONE);
  static game::map_ns::MapInfo testMap02(game::asset::MAP::TEST_MAP02, "tstMap02", game::map_ns::MAP_LEVEL::DANGER_ZONE);
  static game::map_ns::MapInfo testMapAlpha(game::asset::MAP::TEST_MAP_ALPHA, "tstMapAlpha", game::map_ns::MAP_LEVEL::DANGER_ZONE);

  /* Making a std::map so we can map map enums to objects */
  static std::map<game::asset::MAP, game::map_ns::MapInfo*> mapInfoContainerMap;
  
  // Tile for mapping tile ID and sf::IntRect
  //static std::map<int,sf::IntRect> tile;
  static std::map<std::string,std::pair<int,cor>> tiles;
}

void game::map_ns::init() {

  /* INIT FUNCTION */
    tiles["none"]            = std::pair<int,cor>(0,cor(0,0));
    tiles["portal"]          = std::pair<int,cor>(1,cor(6,0));
    tiles["grass"]           = std::pair<int,cor>(2,cor(1,0));
    tiles["water"]           = std::pair<int,cor>(3,cor(2,0));
    tiles["tree"]            = std::pair<int,cor>(4,cor(3,0));
    tiles["castle"]          = std::pair<int,cor>(5,cor(4,0));
    tiles["town"]            = std::pair<int,cor>(6,cor(5,0));
    tiles["mountain"]        = std::pair<int,cor>(7,cor(1,1));
    tiles["castle_wall_top"] = std::pair<int,cor>(8,cor(0,1));
    tiles["castle_wall_mid"] = std::pair<int,cor>(9,cor(0,2));
    tiles["castle_wall_bot"] = std::pair<int,cor>(10,cor(0,3));
    tiles["bridge"]          = std::pair<int,cor>(11,cor(5,1));
    tiles["chest_opened"]    = std::pair<int,cor>(12,cor(6,4));
    tiles["chest_closed"]    = std::pair<int,cor>(13,cor(5,4));
    tiles["wood_floor"]      = std::pair<int,cor>(14,cor(4,1));
    tiles["sign_gen"]        = std::pair<int,cor>(15,cor(0,4));
    tiles["sign_wep"]        = std::pair<int,cor>(16,cor(1,4));
    tiles["sign_arm"]        = std::pair<int,cor>(17,cor(2,4));
    tiles["sign_inn"]        = std::pair<int,cor>(18,cor(3,4));
    tiles["sign_nor"]        = std::pair<int,cor>(19,cor(4,4));
    tiles["s_stairD_left"]   = std::pair<int,cor>(20,cor(4,2));
    tiles["s_stairD_right"]  = std::pair<int,cor>(21,cor(5,2));
    tiles["s_stairU_left"]   = std::pair<int,cor>(22,cor(4,3));
    tiles["s_stairU_right"]  = std::pair<int,cor>(24,cor(5,3));
    tiles["wood_door"]       = std::pair<int,cor>(25,cor(6,5));
    tiles["bridge2"]         = std::pair<int,cor>(26,cor(3,2));
  for(auto& i : tiles) {
    i.second.second.first*=_SS;
    i.second.second.second*=_SS;
  }
  /* A lambda function so we can read from the map files to create maps */
  auto createMap = [](std::string mapName, MapInfo* mapObj) {
    std::ifstream infile;
    infile.open(mapName.c_str());
    if(!infile) {
      std::clog << "Unable to open map: " << mapName << std::endl;
      exit(1);
    }
    int row, col;
    infile >> row >> col;
    /* Indicate the map size */
    mapObj->_mapSize = sf::Vector2i(row, col);
    /* Resize the layers before doing anything */

    /* For numbered layer */
    auto resizeLayer = [row,col,&infile](std::vector<std::vector<int>>& sl) {
      sl = std::vector<std::vector<int>>(row,std::vector<int>(col));
      for(int i = 0; i < row; i++) {
        /* Layer 1 read in */
        for(int j = 0; j < col; j++) {
          infile >> sl[i][j];
        }
      }
    };

    /* For sprites layer */
    auto resizeSpriteLayer = [row, col](std::vector<std::vector<sf::Sprite>>& s) {
      s = std::vector<std::vector<sf::Sprite>>(row,std::vector<sf::Sprite>(col));
      for(auto& i : s) {
        for(auto& j : i) {
          j.setScale(SPRITE_SCALE, SPRITE_SCALE);
        }
      }
    };
    resizeLayer(mapObj->_map_lay01);
    resizeLayer(mapObj->_map_lay02);
    resizeLayer(mapObj->_map_lay03);
    resizeLayer(mapObj->_map_EvLay);

    /* No need for lambda on this one because only 1 exists */
    mapObj->evV.resize(row);
    for(auto& i : mapObj->evV) {
      /* Resize the vector containing information about event */
      i.resize(col);
    }

    /* If reading went well, we should be ok...
     * TODO: Implement error checking later */
    infile.close();

    /* Resize sprites */
    resizeSpriteLayer(mapObj->_map_lay01_S);
    resizeSpriteLayer(mapObj->_map_lay02_S);
    resizeSpriteLayer(mapObj->_map_lay03_S);
    resizeSpriteLayer(mapObj->_mapEvV);

    auto setTextureLambda = [&](std::vector<std::vector<sf::Sprite>>& sp, std::vector<std::vector<int>>& ld, const int i, const int j) -> void {
      for(auto key : tiles) {
        if(ld[i][j] == key.second.first) {
          sp[i][j].setTexture(game::asset::mapTexture());
          sp[i][j].setTextureRect(sf::IntRect(key.second.second.first, key.second.second.second,_SS,_SS));
          sp[i][j].setPosition(_SLOC*(i), _SLOC*(j));
        }
      }
    };

    /* After allocating space and resizing the sprites, now we set the textures
     * for each of the sprite depending on what the data was for the first
     * layer. */
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
        setTextureLambda(mapObj->_map_lay01_S,mapObj->_map_lay01,i,j);
      }
    }

    /* Noticed above how I set the position using the [i][j] subscripting.
     * In the below, I do [j][i] subscripting. This works perfectly. I do not
     * know why, but do not try to apply anymore "fixes". I have come to terms
     * that this is just the way it will be done. */

    /* Define data for the collisions layer */
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
        if(mapObj->_map_lay02[i][j] != 0) { // if not 0, it's a collision
          setTextureLambda(mapObj->_map_lay02_S,mapObj->_map_lay02,i,j);
        }
      }
    }

    // Define data for passthrough layer
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
        if(mapObj->_map_lay03[i][j] != 0) {
          setTextureLambda(mapObj->_map_lay03_S,mapObj->_map_lay03,i,j);
        }
      }
    }

    /* Define data for the events layer */
    for(int i = 0; i < row; i++) {
      for(int j = 0; j < col; j++) {
        if(mapObj->_map_EvLay[i][j] == tiles["portal"].first) {
          setTextureLambda(mapObj->_mapEvV,mapObj->_map_EvLay,i,j);
          /* If it is a portal */
          // Do not touch below unless tile size changes
          #define O 10 // portal pixel offset
          mapObj->_mapEvV[i][j].setTextureRect(sf::IntRect(tiles["portal"].second.first,tiles["portal"].second.second,_SS-10,_SS-10));
          mapObj->_mapEvV[i][j].setPosition(_SLOC*(i)+O*3, _SLOC*(j)+O*3);
          std::clog << "Index of portal for map " << mapName << ": " << '[' << i << ',' << j << ']' << std::endl;
          mapObj->evV[i][j].ev = game::map_ns::TILE_EV::PORTAL;
          #undef O
          // Do not touch above unless tile size changes
        }
        else if(mapObj->_map_EvLay[i][j] != tiles["none"].first) {
          setTextureLambda(mapObj->_mapEvV,mapObj->_map_EvLay,i,j);
          mapObj->evV[i][j].ev = game::map_ns::TILE_EV::NONE;
        }
      }
    }
    std::clog << "Created map: " << mapName << std::endl;
  };

  /* Map the object to a std::map */
  mapInfoContainerMap[game::asset::MAP::TEST_MAP00] = &testMap00;
  mapInfoContainerMap[game::asset::MAP::TEST_MAP01] = &testMap01;
  mapInfoContainerMap[game::asset::MAP::TEST_MAP02] = &testMap02;
  mapInfoContainerMap[game::asset::MAP::TEST_MAP_ALPHA] = &testMapAlpha;

  /* Create the map from the lambda */
  createMap(asset::getMapName(asset::MAP::TEST_MAP00), &testMap00);
  createMap(asset::getMapName(asset::MAP::TEST_MAP01), &testMap01);
  createMap(asset::getMapName(asset::MAP::TEST_MAP02), &testMap02);
  createMap(asset::getMapName(asset::MAP::TEST_MAP_ALPHA), &testMapAlpha);

  /* When placing portals, remember that the sprites are inverted accross the
   * Cartesian-like x-y plane!!
   *
   * So if we have an index at i j, we need to define the second (of the pair)
   * to be j i.
   *
   * Well, my math seems to suck, so that's probably a reason why it's like
   * that. I'm too lazy to apply a fix, so I will just leave it as it is */

  /* Below are the definitons of the map. Here, define portal locations,
   * events, type of map level, etc. Comment the map name first as below.
   * Follow this structure for defining maps
   * 1. portal defintions
   * 2. other event definitions. <- fix this up later
   * 3. If a danger zone, define the types of monsters that are allowed to
   *    spawn. */

  ////////////////////////////////////////////////// 
  // Read a file to define their portals
  ////////////////////////////////////////////////// 
  std::ifstream infile; // used for reading portal destinations
  auto readPortal = [](std::string fn, game::map_ns::MapInfo& m) -> void {
    fn = fn.substr(0,fn.length()-4);
    fn+="-portal.txt";
    std::ifstream infile(fn);
    if(!infile) {
      std::cerr << "Unable to load portals for map " << fn << std::endl;
      exit(1);
    }
    int x, y, a, b, z;
    while(infile >> x >> y >> a >> b >> z) {
      printf("I got: %d,%d,%d,%d,%d\n",x,y,a,b,z);
      m.evV[x][y].portalTransportLoc.first = static_cast<game::asset::MAP>(z);
      m.evV[x][y].portalTransportLoc.second = sf::Vector2f(a,b);
    }
  };
  /* --------------------------------------------------------------------------
   * TEST_MAP00
   * ------------------------------------------------------------------------*/
  readPortal(game::asset::getMapName(game::asset::MAP::TEST_MAP00), testMap00);

  /* --------------------------------------------------------------------------
   * TEST_MAP01
   * ------------------------------------------------------------------------*/
  readPortal(game::asset::getMapName(game::asset::MAP::TEST_MAP01), testMap01);


  /* --------------------------------------------------------------------------
   * TEST_MAP02
   * ------------------------------------------------------------------------*/
  readPortal(game::asset::getMapName(game::asset::MAP::TEST_MAP02), testMap02);

  readPortal(game::asset::getMapName(game::asset::MAP::TEST_MAP_ALPHA), testMapAlpha);
}


void game::map_ns::loadMap(const game::asset::MAP& mapID, const sf::Vector2f playerPos) {
  ani::fadeOut();
  entity::getPl().m_enSprite.setPosition(playerPos.x*_SLOC, playerPos.y*_SLOC);
  setMapID(mapID);
  game::ani::fadeIn();
}

void game::map_ns::displayMap_L1() {

  /* Clear the screen black */
  win::getWin().clear(sf::Color::Black);
  game::map_ns::MapInfo* curr_map = getMapObjectByID(currentMap);
  for(const auto& i : curr_map->_map_lay01_S) {
    for(const auto& j : i) {
      win::getWin().draw(j);
    }
  }
  for(const auto& i : curr_map->_map_lay02_S)
    for(const auto& j : i)
      win::getWin().draw(j);

  /* Drawing */
  win::getWin().draw(game::entity::getPl().m_enSprite);

  for(const auto& i : curr_map->_map_lay03_S)
    for(const auto& j : i)
      win::getWin().draw(j);

  for(const auto& i : getMapObjectByID(currentMap)->_mapEvV) {
    for(const auto& j : i) {
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

namespace game {
  namespace map_ns {
    MapInfo::MapInfo() { }
    MapInfo::MapInfo(const game::asset::MAP& ID, const std::string& s, game::map_ns::MAP_LEVEL ml) {
      this->m_mapID = ID;
      this->m_mapName = s;
      this->_mapLevel = ml;
    }
  }
}
