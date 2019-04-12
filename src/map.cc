#include "map.hpp"

namespace {
  static std::vector< std::vector<size_t> > _map_lay01;  // Layer 1
  static std::vector< std::vector<size_t> > _map_lay02;  // Layer 2
  static std::vector< std::vector<size_t> > _map_lay03;  // Layer 3
  static std::vector< std::vector<size_t> > _map_EvLay;  // Event layer
}

void game::map::loadMap(const std::string& mapName) {

  std::ifstream infile(mapName);
  if(infile) {
    std::cerr << "Unable to open map: " << mapName << std::endl;
    std::cerr << "Verify the integrity of " << mapName << std::endl;
    exit(1);
  }
  unsigned short int row, col;
  /* The first two numbers in the map file are always row and col */
  infile >> row >> col;

  /* Read in the first layer */
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_lay01[i][j];
    }
  }

  /* Read in the second layer */
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_lay02[i][j];
    }
  }

  /* Read in the third layer */
  for(size_t i = 0; i < row; i++) {
    for(size_t j = 0; j < col; j++) {
      infile >> _map_lay03[i][j];
    }
  }

  /* Read in the event layer */
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

}
