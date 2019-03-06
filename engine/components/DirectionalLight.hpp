#pragma once

#include "BaseLight.hpp"

namespace mobagen {
  class DirectionalLight : public BaseLight {
  public:
    DirectionalLight(glm::vec3 color, float intensity);

    virtual void registerWithEngine(Engine *engine);

    virtual void deregisterFromEngine(Engine *engine);

    virtual void updateShader(Shader *shader);

    inline virtual const char *getType(void) { return "DIRECTIONAL_LIGHT"; }
  };
}