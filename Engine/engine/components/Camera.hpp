#pragma once

#include "Component.hpp"

#include <glm/glm.hpp>

class Camera : public Component
{
public:
  Camera(std::string name);

  virtual ~Camera(void) {}

  glm::mat4 getViewMatrix(void) const;
  virtual glm::mat4 getProjectionMatrix(void) const = 0;

  inline virtual const char *getType(void) { return "CAMERA"; }
};