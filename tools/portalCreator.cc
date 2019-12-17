#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cctype>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <map>
#include <fstream>

using cor = std::pair<int,int>;

namespace {
  bool DEBUG = true;
  int layer = 1;
  sf::RenderWindow mapWindow;
  constexpr int PS = 16;
  std::vector<std::vector<sf::RectangleShape>> mapGrids;
  std::vector<std::vector<sf::RectangleShape>> tileGrids;
  std::vector<std::vector<sf::Sprite>> spriteLayer1;
  std::vector<std::vector<sf::Sprite>> spriteLayer2;
  std::vector<std::vector<sf::Sprite>> spriteLayer3;
  std::vector<std::vector<sf::Sprite>> spriteLayer4;
  sf::Texture mapTexture;
  int mapID_dest;
  int source_x, source_y, dest_x, dest_y;
}

namespace tile {
  //////////////////////////////////////////////////////////////////////////////
  // DEFINE WHERE TILES ARE
  //////////////////////////////////////////////////////////////////////////////
  std::pair<int,int> curr;
  static std::map<std::string,std::pair<int,cor>> tiles_map;
  //////////////////////////////////////////////////////////////////////////////
  // DEFINE WHERE TILES ARE
  //////////////////////////////////////////////////////////////////////////////
  void init() {
    tiles_map["none"]            = std::pair<int,cor>(0,cor(0,0));
    tiles_map["portal"]          = std::pair<int,cor>(1,cor(6,0));
    tiles_map["grass"]           = std::pair<int,cor>(2,cor(1,0));
    tiles_map["water"]           = std::pair<int,cor>(3,cor(2,0));
    tiles_map["tree"]            = std::pair<int,cor>(4,cor(3,0));
    tiles_map["castle"]          = std::pair<int,cor>(5,cor(4,0));
    tiles_map["town"]            = std::pair<int,cor>(6,cor(5,0));
    tiles_map["mountain"]        = std::pair<int,cor>(7,cor(1,1));
    tiles_map["castle_wall_top"] = std::pair<int,cor>(8,cor(0,1));
    tiles_map["castle_wall_mid"] = std::pair<int,cor>(9,cor(0,2));
    tiles_map["castle_wall_bot"] = std::pair<int,cor>(10,cor(0,3));
    tiles_map["bridge"]          = std::pair<int,cor>(11,cor(5,1));
    tiles_map["chest_opened"]    = std::pair<int,cor>(12,cor(6,4));
    tiles_map["chest_closed"]    = std::pair<int,cor>(13,cor(5,4));
    tiles_map["wood_floor"]      = std::pair<int,cor>(14,cor(4,1));
    tiles_map["sign_gen"]        = std::pair<int,cor>(15,cor(0,4));
    tiles_map["sign_wep"]        = std::pair<int,cor>(16,cor(1,4));
    tiles_map["sign_arm"]        = std::pair<int,cor>(17,cor(2,4));
    tiles_map["sign_inn"]        = std::pair<int,cor>(18,cor(3,4));
    tiles_map["sign_nor"]        = std::pair<int,cor>(19,cor(4,4));
    tiles_map["s_stairD_left"]   = std::pair<int,cor>(20,cor(4,2));
    tiles_map["s_stairD_right"]  = std::pair<int,cor>(21,cor(5,2));
    tiles_map["s_stairU_left"]   = std::pair<int,cor>(22,cor(4,3));
    tiles_map["s_stairU_right"]  = std::pair<int,cor>(24,cor(5,3));
    tiles_map["wood_door"]       = std::pair<int,cor>(25,cor(6,5));
    tiles_map["bridge2"]         = std::pair<int,cor>(26,cor(3,2));
    for(auto& i : tiles_map) {
      i.second.second.first*=PS;
      i.second.second.second*=PS;
    }
  }
  int which(const sf::Sprite& sp) {
    auto i = std::pair<int,int>(sp.getTextureRect().left,sp.getTextureRect().top);
    for(auto j : tiles_map) {
      if(i == j.second.second) return j.second.first;
    }
    return 0;
  }
  std::pair<int,int> which(const int x) {
    for(auto i : tiles_map) {
      if(x == i.second.first) return i.second.second;
    }
    return std::pair<int,int>(0,0);
  }
}

int main(int argc, const char* argv[]) {
  std::ofstream out2;
  std::string fn2output;
  printf("Write to file: ");
  std::getline(std::cin,fn2output);
  // argv[1] == input png name
  // argv[2] == output text map file
  tile::init();
  if(argc != 2) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  std::string mapName;
  printf("source map: ");
  std::getline(std::cin,mapName);
  std::ifstream infile;
  int x,y;
  infile.open(mapName);
  if(!infile) exit(1);
  infile >> x; infile.ignore();
  infile >> y; infile.ignore();
  //////////////////////////////////////////////////////////// 
  // Read first layer (walkable)
  //////////////////////////////////////////////////////////// 
  std::vector<std::vector<int>> l_intv(x,std::vector<int>(y)); // for reading in ints from map
  spriteLayer1 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      infile >> l_intv[i][j];
      spriteLayer1[i][j].setTexture(mapTexture);
      spriteLayer1[i][j].setTextureRect(sf::IntRect(tile::which(l_intv[i][j]).first, tile::which(l_intv[i][j]).second,PS,PS));
      spriteLayer1[i][j].setPosition(i*PS,j*PS);
    }
  }
  //////////////////////////////////////////////////////////// 
  // Read second layer (collisions)
  //////////////////////////////////////////////////////////// 
  spriteLayer2 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      infile >> l_intv[i][j];
      spriteLayer2[i][j].setTexture(mapTexture);
      spriteLayer2[i][j].setTextureRect(sf::IntRect(tile::which(l_intv[i][j]).first, tile::which(l_intv[i][j]).second,PS,PS));
      spriteLayer2[i][j].setPosition(i*PS,j*PS);
      spriteLayer2[i][j].setColor(sf::Color(255,255,255,96));
    }
  }
  ////////////////////////////////////////////////////////////
  // Read third layer (passthrough)
  //////////////////////////////////////////////////////////// 
  spriteLayer3 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      infile >> l_intv[i][j];
      spriteLayer3[i][j].setTexture(mapTexture);
      spriteLayer3[i][j].setTextureRect(sf::IntRect(tile::which(l_intv[i][j]).first, tile::which(l_intv[i][j]).second,PS,PS));
      spriteLayer3[i][j].setPosition(i*PS,j*PS);
      spriteLayer3[i][j].setColor(sf::Color(255,255,255,128));
    }
  }
  //////////////////////////////////////////////////////////// 
  // Read fourth layer (events)
  //////////////////////////////////////////////////////////// 
  spriteLayer4 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
  for(int i = 0; i < x; i++) {
    for(int j = 0; j < y; j++) {
      infile >> l_intv[i][j];
      spriteLayer4[i][j].setTexture(mapTexture);
      spriteLayer4[i][j].setTextureRect(sf::IntRect(tile::which(l_intv[i][j]).first, tile::which(l_intv[i][j]).second,PS,PS));
      spriteLayer4[i][j].setPosition(i*PS,j*PS);
      spriteLayer4[i][j].setColor(sf::Color(100,0,170,128));
    }
  }
  infile.close();
  sf::Image mapImage;
  if(!mapImage.loadFromFile(argv[1])) return 2;
  mapImage.createMaskFromColor(sf::Color(255,121,155));
  if(!mapTexture.loadFromImage(mapImage)) return 3;
  sf::Sprite mapSprite(mapTexture);


  ////////////////////////////////////////////////// 
  // Create gridlines for the map so I can place
  // tiles down easily
  ////////////////////////////////////////////////// 
  mapGrids = std::vector<std::vector<sf::RectangleShape>>(x, std::vector<sf::RectangleShape>(y));
  for(size_t i = 0; i < mapGrids.size(); i++) {
    for(size_t j = 0; j < mapGrids[i].size(); j++) {
      mapGrids[i][j].setFillColor(sf::Color::Transparent);
      mapGrids[i][j].setSize(sf::Vector2f(PS,PS));
      mapGrids[i][j].setOutlineThickness(.5f);
      mapGrids[i][j].setOutlineColor(sf::Color::Blue);
      mapGrids[i][j].setPosition(i*PS,j*PS);
    }
  }
  tileGrids = std::vector<std::vector<sf::RectangleShape>>(mapTexture.getSize().x/PS, std::vector<sf::RectangleShape>(mapTexture.getSize().y/PS));
  for(size_t i = 0; i < tileGrids.size(); i++) {
    for(size_t j = 0; j < tileGrids[i].size(); j++) {
      tileGrids[i][j].setFillColor(sf::Color::Transparent);
      tileGrids[i][j].setSize(sf::Vector2f(PS,PS));
      tileGrids[i][j].setOutlineThickness(1.f);
      tileGrids[i][j].setOutlineColor(sf::Color::Blue);
      tileGrids[i][j].setPosition(i*PS,j*PS);
    }
  }
  // Allow the max view size to be 48 by 48
  mapWindow.create(sf::VideoMode(PS*48,PS*48), "mapWindow - Layer 1", sf::Style::Close);
  mapWindow.setFramerateLimit(60);

  ////////////////////////////////////////////////// 
  // Variables for controlling mapWindow
  ////////////////////////////////////////////////// 
  sf::View mapView = mapWindow.getView();
  mapView.zoom(.5);
  mapView.setCenter(spriteLayer1[0][0].getPosition());
  mapWindow.setView(mapView);

  tile::init();

  auto checkSprite = [&](sf::Sprite& sp) -> bool {
    auto mouse_pos = sf::Mouse::getPosition(mapWindow); // Mouse position relative to the window
    auto translated_pos = mapWindow.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
    if(sp.getGlobalBounds().contains(translated_pos)) // Rectangle-contains-point check
      return true;
    return false;
  };

  ////////////////////////////////////////////////// 
  // BEGIN WINDOW LOOP
  ////////////////////////////////////////////////// 
  while(mapWindow.isOpen()) {
    sf::Event e;
    char choice;
    //////////////////////////////////////////////////////////// 
    // poll mapWindow window
    //////////////////////////////////////////////////////////// 
    while(mapWindow.pollEvent(e) && mapWindow.hasFocus()) {
      if(e.type == sf::Event::Closed) {
        mapWindow.close();
      }
      if(e.type == sf::Event::KeyPressed) {
        if(e.key.code == sf::Keyboard::Num1) {
          layer = 1;
          mapWindow.setTitle("mapWindow - Layer 1");
        }
        else if(e.key.code == sf::Keyboard::Num2) {
          layer = 2;
          mapWindow.setTitle("mapWindow - Layer 2");
        }
        else if(e.key.code == sf::Keyboard::Num3) {
          layer = 3;
          mapWindow.setTitle("mapWindow - Layer 3");
        }
        else if(e.key.code == sf::Keyboard::Num4) {
          layer = 4;
          mapWindow.setTitle("mapWindow - Layer 4");
        }
      }
      else if(e.type == sf::Event::MouseButtonPressed) {
        if(e.mouseButton.button == sf::Mouse::Left) {
          for(size_t i = 0; i < spriteLayer4.size(); i++) {
            for(size_t j = 0; j < spriteLayer4[i].size(); j++) {
              if(checkSprite(spriteLayer4[i][j])) {
                printf("confirm for: (%zu,%zu) <y/n>\n >>> ",i,j);
                std::cin >> choice; std::cin.ignore();
                source_x = i;
                source_y = j;
              }
            }
          }
        }
      }
    }

    ////////////////////////////////////////////////////////////////////// 
    // START DESTINATION MAP
    ////////////////////////////////////////////////////////////////////// 
    if(std::tolower(choice) == 'y') {
      printf("dest map id: ");
      std::cin >> mapID_dest;
      std::cin.ignore();
      choice = '\0';
      std::string map2fn;
      std::cout << "destination path: ";
      std::getline(std::cin,map2fn);
      std::vector<std::vector<sf::Sprite>> spriteLayer1win2;
      std::vector<std::vector<sf::Sprite>> spriteLayer2win2;
      std::vector<std::vector<sf::Sprite>> spriteLayer3win2;
      std::vector<std::vector<sf::Sprite>> spriteLayer4win2;
      std::ifstream infile2;
      int x2,y2;
      infile2.open(map2fn);
      while(!infile2) {
        std::clog << "Unable to open file: " << map2fn << std::endl;
        std::cout << "destination path: ";
        std::getline(std::cin,map2fn);
        infile2.open(map2fn);
      }
      infile2 >> x2; infile2.ignore();
      infile2 >> y2; infile2.ignore();
      // Map grids for map2
      std::vector<std::vector<sf::RectangleShape>> mapGrids2(x2, std::vector<sf::RectangleShape>(y2));
      for(size_t i = 0; i < mapGrids2.size(); i++) {
        for(size_t j = 0; j < mapGrids2[i].size(); j++) {
          mapGrids2[i][j].setFillColor(sf::Color::Transparent);
          mapGrids2[i][j].setSize(sf::Vector2f(PS,PS));
          mapGrids2[i][j].setOutlineThickness(.5f);
          mapGrids2[i][j].setOutlineColor(sf::Color::Blue);
          mapGrids2[i][j].setPosition(i*PS,j*PS);
        }
      }
      printf("grids 2 passed\n");
      //////////////////////////////////////////////////////////// 
      // Read first layer (walkable)
      //////////////////////////////////////////////////////////// 
      std::vector<std::vector<int>> l_intv2(x2,std::vector<int>(y2)); // for reading in ints from map
      spriteLayer1win2 = std::vector<std::vector<sf::Sprite>>(x2, std::vector<sf::Sprite>(y2));
      for(int i = 0; i < x2; i++) {
        for(int j = 0; j < y2; j++) {
          infile2 >> l_intv2[i][j];
          spriteLayer1win2[i][j].setTexture(mapTexture);
          spriteLayer1win2[i][j].setTextureRect(sf::IntRect(tile::which(l_intv2[i][j]).first, tile::which(l_intv2[i][j]).second,PS,PS));
          spriteLayer1win2[i][j].setPosition(i*PS,j*PS);
        }
      }
      printf("layer1 win 2 passed\n");
      //////////////////////////////////////////////////////////// 
      // Read second layer (collisions)
      //////////////////////////////////////////////////////////// 
      spriteLayer2win2 = std::vector<std::vector<sf::Sprite>>(x2, std::vector<sf::Sprite>(y2));
      for(int i = 0; i < x2; i++) {
        for(int j = 0; j < y2; j++) {
          infile2 >> l_intv2[i][j];
          spriteLayer2win2[i][j].setTexture(mapTexture);
          spriteLayer2win2[i][j].setTextureRect(sf::IntRect(tile::which(l_intv2[i][j]).first, tile::which(l_intv2[i][j]).second,PS,PS));
          spriteLayer2win2[i][j].setPosition(i*PS,j*PS);
          spriteLayer2win2[i][j].setColor(sf::Color(255,255,255,96));
        }
      }
      printf("layer2 win 2 passed\n");
      ////////////////////////////////////////////////////////////
      // Read third layer (passthrough)
      //////////////////////////////////////////////////////////// 
      spriteLayer3win2 = std::vector<std::vector<sf::Sprite>>(x2, std::vector<sf::Sprite>(y2));
      for(int i = 0; i < x2; i++) {
        for(int j = 0; j < y2; j++) {
          infile2 >> l_intv2[i][j];
          spriteLayer3win2[i][j].setTexture(mapTexture);
          spriteLayer3win2[i][j].setTextureRect(sf::IntRect(tile::which(l_intv2[i][j]).first, tile::which(l_intv2[i][j]).second,PS,PS));
          spriteLayer3win2[i][j].setPosition(i*PS,j*PS);
          spriteLayer3win2[i][j].setColor(sf::Color(255,255,255,128));
        }
      }
      printf("layer3 win 2 passed\n");
      //////////////////////////////////////////////////////////// 
      // Read fourth layer (events)
      //////////////////////////////////////////////////////////// 
      spriteLayer4win2 = std::vector<std::vector<sf::Sprite>>(x2, std::vector<sf::Sprite>(y2));
      for(int i = 0; i < x2; i++) {
        for(int j = 0; j < y2; j++) {
          infile2 >> l_intv2[i][j];
          spriteLayer4win2[i][j].setTexture(mapTexture);
          spriteLayer4win2[i][j].setTextureRect(sf::IntRect(tile::which(l_intv2[i][j]).first, tile::which(l_intv2[i][j]).second,PS,PS));
          spriteLayer4win2[i][j].setPosition(i*PS,j*PS);
          spriteLayer4win2[i][j].setColor(sf::Color(100,0,170,128));
        }
      }
      printf("layer4 win 2 passed\n");
      infile2.close();
      // Create window map2win
      sf::RenderWindow map2win;
      map2win.create(sf::VideoMode(PS*48,PS*48),"Destination Map", sf::Style::Close);
      map2win.setFramerateLimit(60);
      sf::View map2View = map2win.getView();
      map2View.zoom(.5);
      map2View.setCenter(spriteLayer1win2[0][0].getPosition());
      map2win.setView(map2View);
      auto checkSprite2 = [&](sf::Sprite& sp) -> bool {
        auto mouse_pos = sf::Mouse::getPosition(map2win); // Mouse position relative to the window
        auto translated_pos = map2win.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
        if(sp.getGlobalBounds().contains(translated_pos)) // Rectangle-contains-point check
          return true;
        return false;
      };
      out2.open(fn2output,std::ios::app);
      while(map2win.isOpen()) {
        sf::Event e2;
        while(map2win.pollEvent(e2)) {
          if(e2.type == sf::Event::MouseButtonPressed) {
            if(e2.mouseButton.button == sf::Mouse::Left) {
              //map2win.close();
              for(size_t i = 0; i < spriteLayer1win2.size(); i++) {
                for(size_t j = 0; j < spriteLayer1win2[i].size(); j++) {
                  if(checkSprite2(spriteLayer1win2[i][j])) {
                    dest_x = i;
                    dest_y = j;
                    printf("%d %d %d %d %d\n",source_x,source_y,dest_x,dest_y,mapID_dest);
                  }
                }
              }
            }
          }
          else if(e2.type == sf::Event::Closed) {
            map2win.close();
          }
        }
        constexpr int ms2{4};
        if(map2win.hasFocus()) {
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            map2View.move(0,-ms2);
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            map2View.move(0,ms2);
          }
          if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            map2View.move(-ms2,0);
          }
          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            map2View.move(ms2,0);
          }
          map2win.setView(map2View);
        }
        map2win.clear(sf::Color::Black);
        for(auto& i : spriteLayer1win2)
          for(auto& j : i)
            if(std::pair<int,int>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"].second)
              map2win.draw(j);
        for(auto& i : spriteLayer2win2)
          for(auto& j : i)
            if(std::pair<int,int>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"].second)
              map2win.draw(j);
        for(auto& i : spriteLayer3win2)
          for(auto& j : i)
            if(std::pair<int,int>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"].second)
              map2win.draw(j);
        for(auto& i : mapGrids2)
          for(auto& j : i)
            map2win.draw(j);
        map2win.display();
      }
      out2 << source_x << " " << source_y << " " << dest_x << " " << dest_y << " " << mapID_dest << std::endl;
      out2.close();
    }
    ////////////////////////////////////////////////////////////////////// 
    // END DESTINATION MAP
    ////////////////////////////////////////////////////////////////////// 

    static constexpr int ms{4};
    if(mapWindow.hasFocus()) {
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        mapView.move(0,-ms);
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        mapView.move(0,ms);
      }
      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        mapView.move(-ms,0);
      }
      else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        mapView.move(ms,0);
      }
      mapWindow.setView(mapView);
    }

    //////////////////////////////////////////////////////////// 
    // BEGIN DRAW for mapWindow window
    //////////////////////////////////////////////////////////// 
    mapWindow.clear(sf::Color::Black);
    for(auto& i : spriteLayer1)
    {
      for(auto& j : i)
      {
        if(std::pair<int,int>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"].second)
            mapWindow.draw(j);
      }
    }
    for(auto& i : spriteLayer2)
    {
      for(auto& j : i)
      {
        if(std::pair<int,int>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"].second)
            mapWindow.draw(j);
      }
    }
    for(auto& i : spriteLayer3)
    {
      for(auto& j : i)
      {
        if(std::pair<int,int>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"].second)
            mapWindow.draw(j);
      }
    }

    for(auto& i : mapGrids) {
      for(auto& j : i) {
        mapWindow.draw(j);
      }
    }
    mapWindow.display();
  }
  std::string fileName;
  return 0;
}
