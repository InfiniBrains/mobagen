//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#pragma once

#include "Engine.h"

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
private:
};
