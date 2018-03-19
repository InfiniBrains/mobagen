//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "EditorGUI.h"
#include <Logger.h>
#include <imgui_internal.h>
#include "components/MeshRenderer.h"
#include <Plane.h>
#include "Material.h"

static float histogramData[256];
static float maxValue=0;
static float imageOffset=0;

static bool histogramApplied = false;
static bool offsetApplied = false;

void EditorGUI::onGUI(ImGuiContext* context)
{
  ImGui::SetCurrentContext(context);

  ImGui::Begin("Options", nullptr, ImVec2(128,128),0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY);
  if (histogramApplied==false && ImGui::Button("Histogram"))
  {
    histogramApplied = true;
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

  ImGui::BeginGroup();
  ImGui::Text("Type the offset to be added to image:");
  ImGui::InputFloat("Offset", &imageOffset,1,2,-1,0);

  if (offsetApplied == false && ImGui::Button("Apply offset"))
  {
    offsetApplied = true;
    auto modifiedData = originalImage->getTextureData()->data;

    for(int i=0; i<modifiedData.size();i+=4)
    {
      int newValue = modifiedData[i]+imageOffset;
      newValue = MIN(255,MAX(0,newValue));
      modifiedData[i] = newValue;   // r
      modifiedData[i+1] = newValue; // g
      modifiedData[i+2] = newValue; // b
    }
    unsigned char * newData = &modifiedData[0];

    auto newTextureData = std::make_shared<TextureData>(originalImage->width(),originalImage->height(), newData ,GL_TEXTURE_2D,GL_LINEAR);
    modifiedImage = std::make_shared<Texture>(newTextureData);

    auto modifiedEntity = std::make_shared<Entity>();
    auto modifiedMat = std::make_shared<Material>(modifiedImage, normalTexture, specularTexture);
    auto modifiedMesh = Plane::getMesh();
    modifiedEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
    modifiedEntity->getTransform().setPosition(glm::vec3(-256, 0, 0));
    modifiedEntity->getTransform().setScale(glm::vec3(400, 1, 400));
    rootScene->addChild(modifiedEntity);

    //modifiedEntity->getComponent<Material>

    //MeshRenderer
  }

  ImGui::EndGroup();
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
