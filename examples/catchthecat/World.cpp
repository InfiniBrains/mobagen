#include "World.h"
void World::print() {
  for (int i = 0; i < worldState.size();) {
    std::cout << worldState[i];
    i++;
    if ((i + sideSize) % (2 * sideSize) == 0)
      std::cout << std::endl << " ";
    else if (i % sideSize == 0)
      std::cout << std::endl;
    else
      std::cout << " ";
  }
}
World::World(int size): sideSize(size) {
  if(size%2==0)
    throw;
  clearWorld();
}
void World::clearWorld() {
  worldState.resize(sideSize*sideSize);
  for(char &i : worldState) i='.';
  for(int i=0; i<sideSize*1.5; i++)
    worldState[Random::Range(0,(int)worldState.size()-1)]='#';
  worldState[(int)worldState.size()/2] = 'C';
}

Point2D World::E(const Point2D& p) {
  return {p.x-1, p.y};
}

Point2D World::W(const Point2D& p) {
  return {p.x+1, p.y};
}

Point2D World::NE(const Point2D& p) {
  if(p.y%2)
    return {p.x-1, p.y-1};
  return {p.x, p.y-1};
}

Point2D World::NW(const Point2D& p) {
  if(p.y%2)
    return {p.x, p.y-1};
  return {p.x+1, p.y-1};
}

Point2D World::SE(const Point2D& p) {
  if(p.y%2)
    return {p.x-1, p.y+1};
  return {p.x, p.y+1};
}

Point2D World::SW(const Point2D& p) {
  if(p.y%2)
    return {p.x, p.y+1};
  return {p.x+1, p.y+1};
}