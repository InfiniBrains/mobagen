#ifndef WORLD_H
#define WORLD_H

#include "Random.h"
#include <iostream>
#include <vector>

struct Point2D {
 public:
  Point2D(int x, int y): x((int8_t)x), y((int8_t)y){};
  int8_t x, y;
};

class World {
 private:
  // . means empty
  // C means cat
  // # means blocked
  std::vector<char>worldState;
  int sideSize=0;
  // todo: optimization make the world state only use 16 Bytes.
  // hints on how to do it:
  // the world have 11x11 size, so it needs 121 bits to represent it. in other words we need 16 bytes to fully represent it. bit representation: 0 empty, 1 blocked.
  // to represent the cat position we need only one byte. 4 bits for X and another 4 for Y
  // create a structure holding one byte for cat position and 16 bytes for the blocked map.

  // clears the world
  void clearWorld();

  // directions
  static Point2D NE(const Point2D &p);
  static Point2D NW(const Point2D &p);
  static Point2D E(const Point2D &p);
  static Point2D W(const Point2D &p);
  static Point2D SE(const Point2D &p);
  static Point2D SW(const Point2D &p);

  // check if point is inside the world
  inline static bool isValidPosition(Point2D p){return false;}; // todo;

 public:
  explicit World(int size=11);

  // the top left (x,y) is (-5,-5) the center is on (0,0);
  // get the content of a given
  inline char getContent(const int8_t& x, const int8_t& y) {
    return worldState[(y+sideSize/2)*(sideSize) + x + sideSize/2];
  }

  void print() ;
};

#endif  // WORLD_H
