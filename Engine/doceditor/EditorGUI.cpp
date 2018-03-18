//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#include "EditorGUI.h"
#include <Logger.h>
#include <imgui_internal.h>

static float histogramData[256];
static float maxValue=0;

void EditorGUI::onGUI(ImGuiContext* context)
{
  ImGui::SetCurrentContext(context);

  ImGui::Begin("Options", nullptr, ImVec2(128,128),0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY);
  if (ImGui::Button("Histogram"))
  {
    memset(histogramData,0, sizeof(histogramData));
    for(int i=0; i<originalImage->height()*originalImage->width();i++)
    {
      auto color = originalImage->getTextureData()->data[i*4]; // get the red channel of the grayscale rgba image
      histogramData[color]+=1;
    }
    maxValue = 0;
    for(int i=0; i<255; i++)
      if(histogramData[i]>maxValue)
        maxValue=histogramData[i];
  }
  ImGui::End();

  ImGui::Begin("Histogram", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY );
  ImGui::PlotHistogram("", histogramData, IM_ARRAYSIZE(histogramData), 0, "Color", 0.f, maxValue, ImVec2(256,256));
  ImGui::End();
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

void EditorGUI::update(double delta) {}

EditorGUI::EditorGUI()
{
  memset(histogramData,0, sizeof(histogramData));
  //auto normal = std::make_shared<Texture>(Asset("default_normal.jpg"));
  //auto specular = std::make_shared<Texture>(Asset("default_specular.jpg"));

  //originalImage = std::make_shared<Texture>(Asset("boat.png"));
  //originalImage->bind(0);
  //std::make_shared<Material>(originalImage, normal, specular);

}
