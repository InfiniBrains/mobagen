#ifndef AGENT_H
#define AGENT_H
#include "World.h"

class Agent {
public:
  explicit Agent(World *world):world(world){};

private:
  World *world;
  virtual void moveIsAcceptable(Point2D& p)=0;
};

#endif  // AGENT_H
