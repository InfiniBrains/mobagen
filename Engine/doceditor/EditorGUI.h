//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#pragma once

#include "Engine.h"
#include "Texture.h"

class EditorGUI : public Component
{
public:
  EditorGUI();
  ~EditorGUI() override{};
  const char* getType() override;
  void updateInput(Input* input, double delta) override {};
  void update(double delta) override;
  void render(Shader* shader) override {};
  void registerWithEngine(Engine* engine) override {};
  void deregisterFromEngine(Engine* engine) override {};
  void onGUI(ImGuiContext* context) override;

  std::shared_ptr<Texture> originalImage;
  std::shared_ptr<Entity> originalEntity;

  std::shared_ptr<Texture> modifiedImage;
  std::shared_ptr<Entity> modifiedEntity;

  std::shared_ptr<Texture> normalTexture;
  std::shared_ptr<Texture> specularTexture;

  std::shared_ptr<Entity> rootScene;
private:


};
