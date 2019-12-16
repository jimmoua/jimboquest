#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <map>
#include <fstream>


namespace {
  bool DEBUG = true;
  int layer = 1;
  sf::RenderWindow mapWindow;
  sf::RenderWindow spriteTiles;
  constexpr float PS = 16;
  std::vector<std::vector<sf::RectangleShape>> mapGrids;
  std::vector<std::vector<sf::RectangleShape>> tileGrids;
  std::vector<std::vector<sf::Sprite>> spriteLayer1;
  std::vector<std::vector<sf::Sprite>> spriteLayer2;
  std::vector<std::vector<sf::Sprite>> spriteLayer3;
  std::vector<std::vector<sf::Sprite>> spriteLayer4;
  sf::Texture mapTexture;
}

namespace tile {
  //////////////////////////////////////////////////////////////////////////////
  // DEFINE WHERE TILES ARE
  //////////////////////////////////////////////////////////////////////////////
  std::pair<float,float> curr;
  std::map<std::string,std::pair<float,float>> tiles_map;
  //////////////////////////////////////////////////////////////////////////////
  // DEFINE WHERE TILES ARE
  //////////////////////////////////////////////////////////////////////////////
  void init() {
    tiles_map["none"] = std::pair<float,float>(0,0);
    tiles_map["grass"] = std::pair<float,float>(1,0);
    tiles_map["water"] = std::pair<float,float>(16,3);
    tiles_map["redBrick"] = std::pair<float,float>(12,4);
    tiles_map["greyBrick"] = std::pair<float,float>(9,5);
    tiles_map["tree"] = std::pair<float,float>(12,4);
    tiles_map["mountainRock"] = std::pair<float,float>(6,8);
    for(auto& i : tiles_map) {
      i.second.first*=PS;
      i.second.second*=PS;
    }
  }
  int which(const sf::Sprite& sp) {
    auto i = std::pair<float,float>(sp.getTextureRect().left,sp.getTextureRect().top);
    if(i == tiles_map["none"]) return 0;
    else if(i == tiles_map["grass"]) return 2;
    else if(i == tiles_map["water"]) return 3;
    else if(i == tiles_map["greyBrick"]) return 4;
    else if(i == tiles_map["tree"]) return 6;
    return 1;
  }
  std::pair<int,int> which(const int x) {
    switch(x) {
      case 0: return tiles_map["none"];
      case 2: return tiles_map["grass"];
      case 3: return tiles_map["water"];
      case 4: return tiles_map["greyBrick"];
      case 6: return tiles_map["tree"];
    }
    return std::pair<int,int>(0,0);
  }
}

int main(int argc, const char* argv[]) {
  // argv[1] == input png name
  // argv[2] == output text map file
  tile::init();
  if(argc != 3) {
    std::cerr << "Invalid arguments\n";
    return 1;
  }
  int choice;
  printf("[1] Create map\n[2] Edit map\n(defaults to create)\n\n >>");
  std::cin >>  choice; std::cin.ignore();
  std::ifstream infile;
  std::string openfileName;
  int x,y;
  if(choice == 2) {
    std::getline(std::cin, openfileName);
    infile.open(openfileName);
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
  }
  else {
    printf("Enter in map size: ");
    std::cin >> x;
    std::cin.ignore();
    std::cin >> y;
    std::cin.ignore();
    //////////////////////////////////////////////////////////// 
    // CREATE SPRITES FOR FOR SPRITE PLACEMENT
    //////////////////////////////////////////////////////////// 
    spriteLayer1 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
    for(size_t i = 0; i < spriteLayer1.size(); i++) {
      for(size_t j = 0; j < spriteLayer1[i].size(); j++) {
        spriteLayer1[i][j].setTexture(mapTexture);
        spriteLayer1[i][j].setTextureRect(sf::IntRect(tile::tiles_map["none"].first,tile::tiles_map["none"].second,PS,PS));
        spriteLayer1[i][j].setPosition(i*PS,j*PS);
      }
    }
    spriteLayer2 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
    for(size_t i = 0; i < spriteLayer2.size(); i++) {
      for(size_t j = 0; j < spriteLayer2[i].size(); j++) {
        spriteLayer2[i][j].setTexture(mapTexture);
        spriteLayer2[i][j].setTextureRect(sf::IntRect(tile::tiles_map["none"].first,tile::tiles_map["none"].second,PS,PS));
        spriteLayer2[i][j].setPosition(i*PS,j*PS);
        spriteLayer2[i][j].setColor(sf::Color(255,255,255,128));
      }
    }
    spriteLayer3 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
    for(size_t i = 0; i < spriteLayer3.size(); i++) {
      for(size_t j = 0; j < spriteLayer3[i].size(); j++) {
        spriteLayer3[i][j].setTexture(mapTexture);
        spriteLayer3[i][j].setTextureRect(sf::IntRect(tile::tiles_map["none"].first,tile::tiles_map["none"].second,PS,PS));
        spriteLayer3[i][j].setPosition(i*PS,j*PS);
        spriteLayer2[i][j].setColor(sf::Color(255,255,255,96));
      }
    }
    spriteLayer4 = std::vector<std::vector<sf::Sprite>>(x, std::vector<sf::Sprite>(y));
    for(size_t i = 0; i < spriteLayer4.size(); i++) {
      for(size_t j = 0; j < spriteLayer4[i].size(); j++) {
        spriteLayer4[i][j].setTexture(mapTexture);
        spriteLayer4[i][j].setTextureRect(sf::IntRect(tile::tiles_map["none"].first,tile::tiles_map["none"].second,PS,PS));
        spriteLayer4[i][j].setPosition(i*PS,j*PS);
        spriteLayer4[i][j].setColor(sf::Color(100,0,170,128));
      }
    }
  }
  sf::Image mapImage;
  if(!mapImage.loadFromFile(argv[1])) return 2;
  mapImage.createMaskFromColor(sf::Color(255,121,155));
  if(!mapTexture.loadFromImage(mapImage)) return 3;
  sf::Sprite mapSprite(mapTexture);
  spriteTiles.create(sf::VideoMode(mapTexture.getSize().x, mapTexture.getSize().y), "Map Creator", sf::Style::Close);

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

  spriteTiles.setFramerateLimit(60);

  ////////////////////////////////////////////////// 
  // Variables for controlling mapWindow
  ////////////////////////////////////////////////// 
  sf::View mapView = mapWindow.getView();
  mapView.zoom(.5);

  tile::init();



  //////////////////////////////////////////////////////////// 
  // LAMBDA FUNCTION TO CHECK TO SEE IF MOUSE IS INTERSECTING
  // WITH A SPRITE TILE OR MAP TILE.
  // 
  // FOR TILE GRIDS
  //////////////////////////////////////////////////////////// 
  auto check = [&](sf::RectangleShape& tg) -> bool {
    const auto tgPos = tg.getPosition();
    const auto right = tg.getSize().x+tgPos.x;
    const auto height = tg.getSize().y+tgPos.y;
    const auto mousePos = sf::Mouse::getPosition(spriteTiles);
    if( (mousePos.x > tgPos.x && mousePos.x < right) && 
        (mousePos.y > tgPos.y && mousePos.y < height) )
    {
      return true;
    }
    return false;
  };

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
  while(mapWindow.isOpen() && spriteTiles.isOpen()) {
    sf::Event e;

    //////////////////////////////////////////////////////////// 
    // poll spriteTiles window
    //////////////////////////////////////////////////////////// 
    while(spriteTiles.pollEvent(e) && spriteTiles.hasFocus()) {
      if(e.type == sf::Event::Closed) {
        spriteTiles.close();
      }
      else if(e.type == sf::Event::KeyPressed) {
      }
      else if(e.type == sf::Event::MouseButtonPressed) {
        if(e.mouseButton.button == sf::Mouse::Left) {
          for(auto& i : tileGrids) {
            for(auto& j : i) {
              if(check(j)) {
                j.setOutlineColor(sf::Color::Green);
                tile::curr = std::pair<float,float>(j.getPosition().x,j.getPosition().y);
                printf("Tile: ");
                std::cout << tile::curr.first/PS << " " << tile::curr.second/PS << std::endl;
              }
              else j.setOutlineColor(sf::Color(sf::Color::Blue));
            }
          }
        }
      }
    }

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
    }

    if(mapWindow.hasFocus()) {
      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if(layer == 1) {
          for(auto& i : spriteLayer1) {
            for(auto& j : i) {
              if(checkSprite(j)) {
                j.setTextureRect(sf::IntRect(tile::curr.first, tile::curr.second,PS,PS));
              }
            }
          }
        }
        else if(layer == 2) {
          for(auto& i : spriteLayer2) {
            for(auto& j : i) {
              if(checkSprite(j)) {
                j.setTextureRect(sf::IntRect(tile::curr.first, tile::curr.second,PS,PS));
              }
            }
          }
        }
        else if(layer == 3) {
          for(auto& i : spriteLayer3) {
            for(auto& j : i) {
              if(checkSprite(j)) {
                j.setTextureRect(sf::IntRect(tile::curr.first, tile::curr.second,PS,PS));
              }
            }
          }
        }
        else if(layer == 4) {
          for(auto& i : spriteLayer4) {
            for(auto& j : i) {
              if(checkSprite(j)) {
                j.setTextureRect(sf::IntRect(tile::curr.first, tile::curr.second,PS,PS));
              }
            }
          }
        }
      }
    }

    static constexpr float ms{4};
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
    // BEGIN DRAW for spriteTiles window
    //////////////////////////////////////////////////////////// 
    spriteTiles.clear(sf::Color::White);
    spriteTiles.draw(mapSprite);
    for(auto& i : tileGrids) {
      for(auto& j : i) {
        spriteTiles.draw(j);
      }
    }
    spriteTiles.display();

    
    //////////////////////////////////////////////////////////// 
    // BEGIN DRAW for mapWindow window
    //////////////////////////////////////////////////////////// 
    mapWindow.clear(sf::Color::White);
    for(auto& i : spriteLayer1)
    {
      for(auto& j : i)
      {
        if(std::pair<float,float>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"])
            mapWindow.draw(j);
      }
    }
    for(auto& i : spriteLayer2)
    {
      for(auto& j : i)
      {
        if(std::pair<float,float>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"])
            mapWindow.draw(j);
      }
    }
    for(auto& i : spriteLayer3)
    {
      for(auto& j : i)
      {
        if(std::pair<float,float>(j.getTextureRect().left*PS,j.getTextureRect().top*PS) != tile::tiles_map["none"])
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
  printf("Enter output filename: ");
  std::getline(std::cin,fileName);
  std::ofstream out;
  out.open(fileName);
  out << x << " " << y << "\n\n"; // Write to file size of map
  //////////////////////////////////////////////////////////// 
  // Output first layer (walkable)
  //////////////////////////////////////////////////////////// 
  for(auto& i : spriteLayer1) {
    for(auto& j : i) {
      out << tile::which(j) << " ";
    }
    out << "\n";
  }
  out << "\n";
  //////////////////////////////////////////////////////////// 
  // Output second layer (collisions)
  //////////////////////////////////////////////////////////// 
  for(auto& i : spriteLayer2) {
    for(auto& j : i) {
      out << tile::which(j) << " ";
    }
    out << "\n";
  }
  out << "\n";
  ////////////////////////////////////////////////////////////
  // Output third layer (passthrough)
  //////////////////////////////////////////////////////////// 
  for(auto& i : spriteLayer3) {
    for(auto& j : i) {
      out << tile::which(j) << " ";
    }
    out << "\n";
  }
  out << "\n";
  //////////////////////////////////////////////////////////// 
  // Output fourth layer (events)
  //////////////////////////////////////////////////////////// 
  for(auto& i : spriteLayer4) {
    for(auto& j : i) {
      if(tile::which(j) == 1) {
        out << tile::which(j) << " ";
      }
    }
    out << "\n";
  }
  
  out.close();
  return 0;
}
