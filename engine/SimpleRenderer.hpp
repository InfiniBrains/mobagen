#pragma once

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Line.hpp"

namespace mobagen {
  class SimpleRenderer : public Renderer {
  public:
    SimpleRenderer();

    virtual ~SimpleRenderer();

    virtual void render(const Entity &scene, std::shared_ptr<Camera> activeCamera,
                        const std::vector<std::shared_ptr<PointLight>> &pointLights,
                        const std::vector<std::shared_ptr<DirectionalLight>> &directionalLights,
                        const std::vector<std::shared_ptr<SpotLight>> &spotLights) const;

    void renderLine(const Line &line, std::shared_ptr<Camera> activeCamera) const;

  private:
    void createShaders();

    std::unique_ptr<Shader> m_simple;
  };
}