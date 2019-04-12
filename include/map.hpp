#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "window.hpp"
#include "game.hpp"
#include <string>
#include <vector>
#include <fstream>

using ushort = unsigned short int;

/* For maps, I will be using four layers. These layers will correspond to the
 * following:
 *
 *   1 = Walkable layer (entities can walk on this layer)
 *
 *   2 = Collision layer (entities may not go through this layer)
 *       When reading from the file, the file should only have binary options
 *       0 =  no collision
 *       1 = yes collision
 *
 *   3 = Passthrough layer (These are the parts of the sprite that belong to a
 *       collision layer, but entities can still pass through them. They are
 *       drawn behind this third layer, however)
 *
 *   4 = Event layers. I need this layer to determine which events will
 *       activate upon stepping on a certain tile or pressting a specific key
 *       at a certain tile. In order to do this, I will have to use non-scoped
 *       enumerated data-types.
 *
 * When we have a texture and we set a sprite to that texture, we can expect it
 * to look something like this (if tiling):
 *
 *   SPRITE LAYOUT
 *   -------------
 *    0  1  2  3  4  5  6  7  8  9
 *   10 11 12 13 14 15 16 17 18 19
 *   20 21 22 23 24 25 26 27 28 29
 *   30 31 32 33 34 35 36 37 38 39
 *   40 41 42 43 44 45 46 47 48 49
 *   50 51 52 53 54 55 56 57 58 59
 *   60 61 62 63 64 65 66 67 68 69
 *   70 71 72 73 74 75 76 77 78 79
 *   80 81 82 83 84 85 86 87 88 89
 *   90 91 92 93 94 95 96 97 98 99
 *
 * For example:
 *   0 = Nothing
 *   1 = Stone sprite
 *   2 = Grass sprite
 *   3 = Dirt sprite
 *   4 = Cobblestone sprite
 *   5 = Wood plank sprite
 *   and so on.
 *
 * Our map will look something like this:
 *
 *
 * Tells us that the map is a 10x10 map
 * 10 10
 *
 *    LAYER 1 = Walkable layer
 *    0  1  2  3  4  5  6  7  8  9
 *   10 11 12 13 14 15 16 17 18 19
 *   20 21 22 23 24 25 26 27 28 29
 *   30 31 32 33 34 35 36 37 38 39
 *   40 41 42 43 44 45 46 47 48 49
 *   50 51 52 53 54 55 56 57 58 59
 *   60 61 62 63 64 65 66 67 68 69
 *   70 71 72 73 74 75 76 77 78 79
 *   80 81 82 83 84 85 86 87 88 89
 *   90 91 92 93 94 95 96 97 98 99
 *
 *   Layer 2 = Collision layer
 *    0  1  2  3  4  5  6  7  8  9
 *   10 11 12 13 14 15 16 17 18 19
 *   20 21 22 23 24 25 26 27 28 29
 *   30 31 32 33 34 35 36 37 38 39
 *   40 41 42 43 44 45 46 47 48 49
 *   50 51 52 53 54 55 56 57 58 59
 *   60 61 62 63 64 65 66 67 68 69
 *   70 71 72 73 74 75 76 77 78 79
 *   80 81 82 83 84 85 86 87 88 89
 *   90 91 92 93 94 95 96 97 98 99
 *
 *   Layer 3 = Passthrough layer
 *    0  1  2  3  4  5  6  7  8  9
 *   10 11 12 13 14 15 16 17 18 19
 *   20 21 22 23 24 25 26 27 28 29
 *   30 31 32 33 34 35 36 37 38 39
 *   40 41 42 43 44 45 46 47 48 49
 *   50 51 52 53 54 55 56 57 58 59
 *   60 61 62 63 64 65 66 67 68 69
 *   70 71 72 73 74 75 76 77 78 79
 *   80 81 82 83 84 85 86 87 88 89
 *   90 91 92 93 94 95 96 97 98 99
 *
 *   Layer 4 = Event layer
 *    0  1  2  3  4  5  6  7  8  9
 *   10 11 12 13 14 15 16 17 18 19
 *   20 21 22 23 24 25 26 27 28 29
 *   30 31 32 33 34 35 36 37 38 39
 *   40 41 42 43 44 45 46 47 48 49
 *   50 51 52 53 54 55 56 57 58 59
 *   60 61 62 63 64 65 66 67 68 69
 *   70 71 72 73 74 75 76 77 78 79
 *   80 81 82 83 84 85 86 87 88 89
 *   90 91 92 93 94 95 96 97 98 99
 *
 *
 * Since there can only be one map loaded at a time, I have decided to just go
 * with encapsulation again instead of classes. */

/* In order to have our map display an image, we need to have two things:
 *   1. Texture -> Some piece in memory to hold the graphics
 *   2. Sprite  -> Some rectangle to hold the texture
 * 
 * We will create the texture in the assets file with sf::Texture and load it
 * with a texture from file, memory, or from stream (preferrably from file).
 * 
 * Once we have created a texture, we will assign a sprite to it. Textures are
 * very expensive, but sprites are not. For this reason, using multiple sprites
 * in a map seems OK to me. */

/* When placing sprites and defining their locations, we can have the first
 * layer look something like this.
 *   Layer 1 = Walkable layer
 *   where x represents a tile
 *
 *   We can read them in row-column order by using a for loop, given that we do
 *   something like:
 *
 *     for(int i = 0; i < rol; i++) {
 *       for(int j = 0; i < col; j++) {
 *         sprite.setPosition(_SLOC*i, _SLOC*j);
 *       }
 *     }
 *
 * However, by doing this, we SFML will store them in not of the x,y convential
 * Cartesian-like manner, but do a flip accross the x-y plane. The coordinates
 * of sprite are then adjusted in such a manner where they are then represented
 * as follows:
 *  25 24 23 22 21
 *  20 19 18 17 16
 *  15 14 13 12 11
 *  10  9  8  7  6
 *   5  4  3  2  1
 *
 * To fix this, I am going to read them reverting the x-y flip by doing this:
 *
 *     for(int i = 0; i < rol; i++) {
 *       for(int j = 0; i < col; j++) {
 *         sprite.setPosition(_SLOC*(row-i-1), _SLOC*(col-j-1));
 *       }
 *     }
 *
 * The -1 is in the setPosition function because acts as an offset. If we do
 * not have it there, when the sprites are position on the SFML window, they
 * will have a  gap on the corner where they shouldn't.
 *
 * */

namespace game {
  namespace map {

    /* Define some enum for the tile event. */
    enum TILE_EV {
      NONE,
      PORTAL,
    };

    void init();
    void loadMap(const std::string&);
    void displayMap();
  }
}
