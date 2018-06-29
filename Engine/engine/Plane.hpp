#pragma once
#include "Mesh.hpp"

namespace mobagen {
  class Plane {
  public:
    Plane(void) = default;

    ~Plane(void) = default;

    static std::shared_ptr<Mesh> getMesh(void);
  };
}