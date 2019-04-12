#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "window.hpp"
#include "game.hpp"
#include <string>
#include <vector>
#include <fstream>

/* For maps, I will be using four layers. These layers will correspond to the
 * following:
 *
 *   1 = Walkable layer (entities can walk on this layer)
 *
 *   2 = Collision layer (entities may not go through this layer)
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
 * in a map seems OK to me.
 * */

namespace game {
  namespace map {
    void loadMap(const std::string&);
  }
}
