#pragma once
#include "components/Sphere.hpp"
#include "Entity.hpp"
#include "Ray.hpp"

#include <vector>

namespace mobagen {
  class PhysicsManager {
  public:
    PhysicsManager(void);

    ~PhysicsManager(void);

    void registerCollider(std::shared_ptr<Sphere> sphere);

    void deregisterCollider(std::shared_ptr<Sphere> sphere);

    Entity *pick(Ray *ray) const;

  private:
    std::vector<std::shared_ptr<Sphere>> m_colliders;
  };
}