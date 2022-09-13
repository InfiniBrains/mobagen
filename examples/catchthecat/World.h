#ifndef WORLD_H
#define WORLD_H

#include "Random.h"
#include <iostream>
#include <vector>

struct Point2D {
 public:
  Point2D(int8_t x, int8_t y): x(x), y(y){};
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
  void clearWorld() {
    worldState.resize(sideSize*sideSize);
    for(char &i : worldState) i='.';
    for(int i=0; i<sideSize*1.5; i++)
      worldState[Random::Range(0,(int)worldState.size()-1)]='#';
    worldState[(int)worldState.size()/2] = 'C';
  };

  // directions
  inline static Point2D NE(Point2D p){return {0,0};}; // todo;
  inline static Point2D NW(Point2D p){return {0,0};}; // todo;
  inline static Point2D E(Point2D p){return {0,0};}; // todo;
  inline static Point2D W(Point2D p){return {0,0};}; // todo;
  inline static Point2D SE(Point2D p){return {0,0};}; // todo;
  inline static Point2D SW(Point2D p){return {0,0};}; // todo;

  // check if point is inside the world
  inline static bool isValidPosition(Point2D p){return false;}; // todo;

 public:
  explicit World(int size=11): sideSize(size) {
    if(size%2==0)
      throw;
    clearWorld();
  }

  // the top left (x,y) is (-5,-5) the center is on (0,0);
  // get the content of a given
  char getContent(const int8_t& x, const int8_t& y){
    return worldState[(y+5)*11 + x + 5];
  }

  void print() {
    for(uint8_t i = 0; i<121; ) {
      std::cout << worldState[i];
      i++;
      if((i+11)%22==0)
        std::cout << std::endl << " ";
      else if (i%11==0)
        std::cout << std::endl;
      else
        std::cout << " ";
    }
  }
};

#endif  // WORLD_H
