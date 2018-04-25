#pragma once

#include "Mesh.hpp"

class Plane
{
public:
  Plane(void);
  ~Plane(void);

  static std::shared_ptr<Mesh> getMesh(void);
};
