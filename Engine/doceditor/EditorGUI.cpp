//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#include "EditorGUI.h"
#include "Texture.h"

void EditorGUI::onGUI(ImGuiContext* context)
{
  ImGui::SetCurrentContext(context);

  ImGui::Text("Hello, world %d", 123);
  if (ImGui::Button("Save"))
  {
    // do stuff
  }
}

// show image
// show histogram
// add remove constant value to pixels
// average
// median
// equalization
// high-pass
// http://www.cis.umac.mo/cybernetics/WCSR-L2L1/DenoisedResults.htm


const char* EditorGUI::getType()
{
  return "EDITORGUI";
}

void EditorGUI::update(double delta)
{
  auto backgroundTex = std::make_shared<Texture>(Asset("boat.png"));
}

EditorGUI::EditorGUI()
{
  
}
