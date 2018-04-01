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

  std::shared_ptr<Texture> firstImage;
  std::shared_ptr<Entity> firstEntity;

  std::shared_ptr<Texture> secondImage;
  std::shared_ptr<Entity> secondEntity;

  std::shared_ptr<Texture> thirdImage;
  std::shared_ptr<Entity> thirdEntity;

  std::shared_ptr<Texture> forthImage;
  std::shared_ptr<Entity> forthEntity;

  std::shared_ptr<Texture> normalTexture;
  std::shared_ptr<Texture> specularTexture;

  std::shared_ptr<Entity> rootScene;
private:
  void mainMenu();
  void options();
  void equalize();
  void highPass();
  void Laplace(unsigned char * input, unsigned char * output, int width, int height, int bytesPerChannels = 1, int numberOfChannels = 4);
  unsigned char LaplaceMask(unsigned char * input, int width, int height, int line, int column, int bytesPerChannels = 1, int numberOfChannels = 4);

  // 0 -> not chosen
  // 1 -> equalization
  // 2 -> high-pass
  int option = 0;
};
