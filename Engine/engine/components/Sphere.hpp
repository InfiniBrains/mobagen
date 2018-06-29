#pragma once
#include "Component.hpp"

namespace mobagen {
  class Sphere : public Component, public std::enable_shared_from_this<Sphere> {
  public:
    // todo: explicit?
    Sphere(float radius = 0);

    // todo: switch from virtual to final or override
    virtual void registerWithEngine(Engine *engine);

    // todo: switch from virtual to final or override
    virtual void deregisterFromEngine(Engine *engine);

    inline virtual const char *getType() { return "SPHERE"; }

    float getRadius() const;

  private:
    float m_radius;
  };
}