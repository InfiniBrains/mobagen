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
#include <gdcmImageReader.h>
#include <string>
#include "Material.h"

static float histogramDataOriginal[256];
static float transferOriginal[256];
static float histogramDataOffset[256];
static float transferOffset[256];
static float histogramDataOffsetEqualized[256];
static float histogramDataEqualized[256];
static float maxValueOriginal=0;
static float maxValueOffset=0;
static float maxValueOffsetEqualized=0;
static float maxValueEqualized=0;
static int imageOffset=0;

static bool offsetApplied = false;

//std::vector<int> histogram(std::shared_ptr<Texture> originalImage)
//{
//  std::vector<int> histogram;
//  histogram.resize(256,0);
//  for (int i = 0; i < originalImage->height() * originalImage->width(); i++) {
//    auto color = originalImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
//    histogram[color] += 1;
//  }
//  return histogram;
//}


//std::shared_ptr<Texture> equalizeHistogram(std::shared_ptr<Texture> originalImage)
//{
//  // histogram
//  static float histogram[256];
//  memset(histogram, 0, sizeof(float)*256);
//  for (int i = 0; i < originalImage->height() * originalImage->width(); i++) {
//    auto color = originalImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
//    histogram[color] += 1;
//  }
//
//  // transfer function
//  float transfer[256];
//  memset(transfer, 0, sizeof(float)*256);
//  transfer[0] = 255.0f * transfer[0] / (float) (originalImage->height() * originalImage->width());
//  for (int i = 1; i < 256; i++)
//    transferOriginal[i] = transferOriginal[i - 1] + 255.0f * histogramDataOriginal[i] / (float) (originalImage->height() * originalImage->width());
//
//  // apply transfer
//  auto equalizedData = originalImage->getTextureData()->data;
//  for (int i = 0; i < equalizedData.size(); i += 4) {
//    int newValue = (int) floor(transferOriginal[equalizedData[i]]);
//    newValue = MIN(255, MAX(0, newValue));
//    equalizedData[i] = newValue;   // r
//    equalizedData[i + 1] = newValue; // g
//    equalizedData[i + 2] = newValue; // b
//  }
//  unsigned char *newEqualizedData = &equalizedData[0];
//
//  auto newTextureData = std::make_shared<TextureData>(originalImage->width(),originalImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
//  return std::make_shared<Texture>(newTextureData);
//}

void EditorGUI::onGUI(ImGuiContext* context)
{
  ImGui::SetCurrentContext(context);

  ImGui::Begin("Options", nullptr, ImVec2(128,128),0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY);
  ImGui::SetWindowPos(ImVec2(370,0),0);
  ImGui::BeginGroup();
  ImGui::Text("Type the offset to be added to image:");
  ImGui::InputInt("Offset", &imageOffset,1,2,0);

  if (offsetApplied == false && ImGui::Button("Apply offset and calculate"))
  {
    // apply offset
    offsetApplied = true;
    {
      auto modifiedData = originalImage->getTextureData()->data;
      for (int i = 0; i < modifiedData.size(); i += 4) {
        int newValue = modifiedData[i] + imageOffset;
        newValue = MIN(255, MAX(0, newValue));
        modifiedData[i] = newValue;   // r
        modifiedData[i + 1] = newValue; // g
        modifiedData[i + 2] = newValue; // b
      }
      unsigned char *newData = &modifiedData[0];

      auto newTextureData = std::make_shared<TextureData>(originalImage->width(), originalImage->height(), newData, GL_TEXTURE_2D, GL_LINEAR);
      offsetImage = std::make_shared<Texture>(newTextureData);

      offsetEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(offsetImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      offsetEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      offsetEntity->getTransform().setPosition(glm::vec3(-300, 0, 250));
      offsetEntity->getTransform().setScale(glm::vec3(300, 1, 300));
      rootScene->addChild(offsetEntity);
    }

    // set histogram original
    {
      memset(histogramDataOriginal, 0, sizeof(histogramDataOriginal));
      for (int i = 0; i < originalImage->height() * originalImage->width(); i++) {
        auto color = originalImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOriginal[color] += 1;
      }
      maxValueOriginal = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOriginal[i] > maxValueOriginal)
          maxValueOriginal = histogramDataOriginal[i];
    }

    // set histogram offset
    {
      memset(histogramDataOffset, 0, sizeof(histogramDataOffset));
      for (int i = 0; i < offsetImage->height() * offsetImage->width(); i++) {
        auto color = offsetImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOffset[color] += 1;
      }
      maxValueOffset = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOffset[i] > maxValueOffset)
          maxValueOffset = histogramDataOffset[i];
    }

    // new equalized image from original
    {
      memset(transferOriginal, 0, sizeof(transferOriginal));
      transferOriginal[0] =
          255.0f * histogramDataOriginal[0] / (float) (originalImage->height() * originalImage->width());
      for (int i = 1; i < 256; i++)
        transferOriginal[i] = transferOriginal[i - 1] + 255.0f * histogramDataOriginal[i] /
                                                        (float) (originalImage->height() * originalImage->width());
      auto equalizedData = originalImage->getTextureData()->data;
      for (int i = 0; i < equalizedData.size(); i += 4) {
        int newValue = (int) floor(transferOriginal[equalizedData[i]]);
        newValue = MIN(255, MAX(0, newValue));
        equalizedData[i] = newValue;   // r
        equalizedData[i + 1] = newValue; // g
        equalizedData[i + 2] = newValue; // b
      }
      unsigned char *newEqualizedData = &equalizedData[0];

      auto newTextureData = std::make_shared<TextureData>(originalImage->width(),originalImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
      equalizedImage = std::make_shared<Texture>(newTextureData);

      equalizedEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(equalizedImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      equalizedEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      equalizedEntity->getTransform().setPosition(glm::vec3(300, 0, -250));
      equalizedEntity->getTransform().setScale(glm::vec3(300, 1, 300));
      rootScene->addChild(equalizedEntity);
    }

    // new equalized image from offset
    {
      memset(transferOffset, 0, sizeof(transferOffset));
      transferOffset[0] = 255.0f * histogramDataOffset[0] / (float) (originalImage->height() * originalImage->width());
      for (int i = 1; i < 256; i++)
        transferOffset[i] = transferOffset[i - 1] + 255.0f * histogramDataOffset[i] / (float) (originalImage->height() * originalImage->width());
      auto equalizedData = offsetImage->getTextureData()->data;
      for (int i = 0; i < equalizedData.size(); i += 4) {
        int newValue = (int) floor(transferOffset[equalizedData[i]]);
        newValue = MIN(255, MAX(0, newValue));
        equalizedData[i] = newValue;   // r
        equalizedData[i + 1] = newValue; // g
        equalizedData[i + 2] = newValue; // b
      }
      unsigned char *newEqualizedData = &equalizedData[0];

      auto newTextureData = std::make_shared<TextureData>(originalImage->width(),originalImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
      offsetEqualizedImage = std::make_shared<Texture>(newTextureData);

      offsetEqualizedEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(offsetEqualizedImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      offsetEqualizedEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      offsetEqualizedEntity->getTransform().setPosition(glm::vec3(-300, 0, -250));
      offsetEqualizedEntity->getTransform().setScale(glm::vec3(300, 1, 300));
      rootScene->addChild(offsetEqualizedEntity);
    }

    // set histogram equalized
    {
      memset(histogramDataEqualized, 0, sizeof(histogramDataEqualized));
      for (int i = 0; i < offsetImage->height() * offsetImage->width(); i++) {
        auto color = equalizedImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataEqualized[color] += 1;
      }
      maxValueEqualized = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataEqualized[i] > maxValueEqualized)
          maxValueEqualized = histogramDataEqualized[i];
    }

    // set histogram offset equalized
    {
      memset(histogramDataOffsetEqualized, 0, sizeof(histogramDataOffsetEqualized));
      for (int i = 0; i < offsetEqualizedImage->height() * offsetEqualizedImage->width(); i++) {
        auto color = offsetEqualizedImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOffsetEqualized[color] += 1;
      }
      maxValueOffsetEqualized = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOffsetEqualized[i] > maxValueOffsetEqualized)
          maxValueOffsetEqualized = histogramDataOffsetEqualized[i];
    }
  }

  ImGui::EndGroup();
  ImGui::End();

  ImGui::Begin("Histogram", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY );
  ImGui::SetWindowPos(ImVec2(50,0),0);
  ImGui::PlotHistogram("", histogramDataOriginal, IM_ARRAYSIZE(histogramDataOriginal), 0, "Original", 0.f, maxValueOriginal, ImVec2(300,80));
  ImGui::End();

  ImGui::Begin("Histogram2", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY );
  ImGui::SetWindowPos(ImVec2(653,0),0);
  ImGui::PlotHistogram("", histogramDataOffset, IM_ARRAYSIZE(histogramDataOffset), 0, "Offset", 0.f, maxValueOffset, ImVec2(300,80));
  ImGui::End();

  ImGui::Begin("Histogram3", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY );
  ImGui::SetWindowPos(ImVec2(50,500),0);
  ImGui::PlotHistogram("", histogramDataEqualized, IM_ARRAYSIZE(histogramDataEqualized), 0, "Equalized", 0.f, maxValueEqualized, ImVec2(300,80));
  ImGui::End();

  ImGui::Begin("Histogram4", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_ChildWindowAutoFitX | ImGuiWindowFlags_ChildWindowAutoFitY );
  ImGui::SetWindowPos(ImVec2(653,500),0);
  ImGui::PlotHistogram("", histogramDataOffsetEqualized, IM_ARRAYSIZE(histogramDataOffsetEqualized), 0, "Offset Equalized", 0.f, maxValueOffsetEqualized, ImVec2(300,80));
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

EditorGUI::EditorGUI() : Component()
{
  memset(histogramDataOriginal,0, sizeof(histogramDataOriginal));
  memset(histogramDataOffset,0, sizeof(histogramDataOffset));
  memset(histogramDataOffsetEqualized,0, sizeof(histogramDataOffsetEqualized));
  memset(histogramDataEqualized,0, sizeof(histogramDataEqualized));

  auto dicomAsset = Asset("brain.dcm");
  gdcm::ImageReader imageReader;

  int fileSize = dicomAsset.getIOStream()->fileSize();

  // todo: check for size greater than 4gb
  auto dicomFileData = new char[fileSize];
  dicomAsset.getIOStream()->read(dicomFileData,1,fileSize);

  std::stringstream str;

  str.write(dicomFileData,fileSize);
  imageReader.SetStream(str);
  imageReader.Read();

  auto image = imageReader.GetImage();

  auto photometric = image.GetPhotometricInterpretation();

  auto pixelformat = image.GetPixelFormat();

  char * imageBuffer = new char[pixelformat.GetPixelSize()*image.GetColumns()*image.GetRows()];
  image.GetBuffer(imageBuffer);

  log_info("format %d", pixelformat.GetBitsAllocated());

  delete []dicomFileData;
  delete []imageBuffer;

  //auto normal = std::make_shared<Texture>(Asset("default_normal.jpg"));
  //auto specular = std::make_shared<Texture>(Asset("default_specular.jpg"));

  //originalImage = std::make_shared<Texture>(Asset("boat.png"));
  //originalImage->bind(0);
  //std::make_shared<Material>(originalImage, normal, specular);

}
