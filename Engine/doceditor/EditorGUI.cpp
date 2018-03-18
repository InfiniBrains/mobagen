//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#include <Material.h>
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
  //ImGui::Image((ImTextureID*)originalImage->getTextureData()->getTextureId(), ImVec2(originalImage->width(), originalImage->height()));

  ImGui::Image((ImTextureID*)originalImage->getTextureData()->getTextureId(), ImVec2(256,256));
  //ImGui::Image((ImTextureID*)tex->id, ImVec2(currentSprite->sW, currentSprite->sH), uv0, uv1, ImColor(255, 255, 255, 55));
}

EditorGUI::EditorGUI()
{
  //auto normal = std::make_shared<Texture>(Asset("default_normal.jpg"));
  //auto specular = std::make_shared<Texture>(Asset("default_specular.jpg"));

  //originalImage = std::make_shared<Texture>(Asset("boat.png"));
  //originalImage->bind(0);
  //std::make_shared<Material>(originalImage, normal, specular);

}
