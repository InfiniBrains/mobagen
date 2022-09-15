#ifndef CAT_H
#define CAT_H

#include "Agent.h"

class Cat: public Agent {
public:
    explicit Cat(World *world):Agent(world){};
};

#endif  // CAT_H
