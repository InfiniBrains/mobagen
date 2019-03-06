#pragma once

#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace mobagen {
  class FreeMove : public Component {
  public:
    FreeMove(bool moveForwards = true, float speed = 10.f);

    ~FreeMove(void);

    virtual void update(Input *input, std::chrono::microseconds delta);

    virtual void registerWithEngine(Engine *engine);

    virtual void deregisterFromEngine(Engine *engine);

    inline virtual const char *getType(void) { return "FREE_MOVE"; }

  private:
    void Move(const glm::vec3 &direction, float amount);

    float m_speed, m_forwardsVelocity, m_strafeVelocity;
    bool m_moveForwards, m_sprinting;
  };
}