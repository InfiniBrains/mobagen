#include "Camera.hpp"

namespace mobagen {
  glm::mat4 Camera::getViewMatrix(void) const {
    return glm::inverse(m_parentEntity->getWorldMatrix());
  }
}