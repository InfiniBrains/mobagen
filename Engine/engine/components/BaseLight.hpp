#pragma once

#include <glm/glm.hpp>

#include "Component.hpp"
#include "Shader.hpp"

class BaseLight : public Component, public std::enable_shared_from_this<BaseLight>
{
public:
  BaseLight(glm::vec3 color, float intensity);
  virtual ~BaseLight(void);

  virtual void registerWithEngine(Engine *engine) {};

  glm::vec3 getColor(void) const;
  float getIntensity(void) const;

  virtual void updateShader(Shader *shader) = 0;

protected:
  glm::vec3 m_color;
  float m_intensity;
};
