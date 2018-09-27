#pragma once
#include "Component.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

namespace mobagen {
  class FreeMove : public Component {
  public:
    FreeMove(bool moveForwards = true, float speed = 0.01f);

    ~FreeMove(void);

    virtual void updateInput(Input *input, double delta);

    inline virtual const char *getType(void) { return "FREE_MOVE"; }

  private:
    void Move(const glm::vec3 &direction, float amount);

    float m_speed;
    bool m_moveForwards;
  };
}