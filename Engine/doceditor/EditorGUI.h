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
  ~EditorGUI(){};
  const char* getType() override;
  void updateInput(Input* input, double delta) override {};
  void update(double delta) override;
  void render(Shader* shader) override {};
  void registerWithEngine(Engine* engine) override {};
  void deregisterFromEngine(Engine* engine) override {};
  void onGUI(ImGuiContext* context) override;

  std::shared_ptr<Texture> originalImage;
  std::shared_ptr<Entity> originalEntity;

  std::shared_ptr<Texture> offsetImage;
  std::shared_ptr<Entity> offsetEntity;

  std::shared_ptr<Texture> equalizedImage;
  std::shared_ptr<Entity> equalizedEntity;

  std::shared_ptr<Texture> offsetEqualizedImage;
  std::shared_ptr<Entity> offsetEqualizedEntity;

  std::shared_ptr<Texture> normalTexture;
  std::shared_ptr<Texture> specularTexture;

  std::shared_ptr<Entity> rootScene;
private:
  void mainMenu();
  void options();
  void equalize();
  void highPass();
  void Laplace(unsigned char * input, unsigned char * output, int width, int height,int bytesPerChannels, int numberOfChannels);

  // 0 -> not chosen
  // 1 -> equalization
  // 2 -> high-pass
  int option = 0;
};
