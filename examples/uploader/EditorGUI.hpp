#pragma once
#include "Engine.hpp"
#include "Texture.hpp"
using namespace mobagen;

class EditorGUI : public Component
{
public:
  EditorGUI();
  ~EditorGUI() = default;;
  const char* getType() override;
  void updateInput(Input* input, double delta) override {};
  void update(double delta) override;
  void render(Shader* shader) override {};
  void registerWithEngine(Engine* engine) override {};
  void deregisterFromEngine(Engine* engine) override {};
  void onGUI(ImGuiContext* context) override;




  std::shared_ptr<Texture> normalTexture;
  std::shared_ptr<Texture> specularTexture;

  std::shared_ptr<Entity> rootScene;
private:

};
