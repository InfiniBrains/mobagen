#include "Camera.hpp"

glm::mat4 Camera::getViewMatrix(void) const
{
  return glm::inverse(m_parentEntity->getWorldMatrix());
}

Camera::Camera(std::string name) : Component() {}
