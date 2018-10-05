#include "SimpleBehaviour.h"
#include "Logger.hpp"

void SimpleBehaviour::update(double delta) {
  log_info("%s", "mensagem");
}

void SimpleBehaviour::onGUI(ImGuiContext *context) {
  ImGui::Text("teste");
}
