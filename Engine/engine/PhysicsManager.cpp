#include "PhysicsManager.hpp"
#include <glm/gtx/norm.hpp>
#include <algorithm>

namespace mobagen {
  PhysicsManager::PhysicsManager(void) = default;
  PhysicsManager::~PhysicsManager(void) = default;

  void PhysicsManager::registerCollider(std::shared_ptr<Sphere> sphere) {
    m_colliders.push_back(sphere);
  }

  void PhysicsManager::deregisterCollider(std::shared_ptr<Sphere> sphere) {
    m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), sphere), m_colliders.end());
  }

  Entity *PhysicsManager::pick(Ray *ray) const {
    glm::vec3 intersectionPosition;
    float closest = std::numeric_limits<float>::max();
    Entity *entity = nullptr;

    for (const auto &m_collider : m_colliders) {
      if (ray->intersects(m_collider.get(), intersectionPosition)) {
        float length = glm::length2(intersectionPosition - ray->getPosition());
        if (length < closest)
          entity = m_collider->getParent();
      }
    }

    return entity;
  }
}