//
// Created by Alexandre Tolstenko Nogueira on 3/18/18.
//

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#include "EditorGUI.h"
#include <Logger.h>
#include "components/MeshRenderer.h"
#include <Plane.h>
#include <gdcmImageReader.h>
#include <string>
#include "Material.h"
#include <imgui.h>

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

ImVec2 windowFactor;

static bool applied = false;

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

  mainMenu();

  if(applied == false) {
    // options
    ImGui::Begin("Options", nullptr, ImVec2(128*windowFactor.x, 128*windowFactor.y), 0, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
    ImGui::SetWindowPos(ImVec2(370*windowFactor.x, 20*windowFactor.y), 0);
    if (option == 0)
      options();

    if (option == 1 && applied == false)
      equalize();

    if (option == 2 && applied == false)
      highPass();
    ImGui::End();
  }

  ImGui::Begin("Histogram", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowPos(ImVec2(50*windowFactor.x,20*windowFactor.y),0);
  ImGui::PlotHistogram("", histogramDataOriginal, IM_ARRAYSIZE(histogramDataOriginal), 0, "Original", 0.f, maxValueOriginal, ImVec2(300*windowFactor.x,80*windowFactor.y));
  ImGui::End();

  ImGui::Begin("Histogram2", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowPos(ImVec2(653*windowFactor.x,20*windowFactor.y),0);
  ImGui::PlotHistogram("", histogramDataOffset, IM_ARRAYSIZE(histogramDataOffset), 0, "Offset", 0.f, maxValueOffset, ImVec2(300*windowFactor.x,80*windowFactor.y));
  ImGui::End();

  ImGui::Begin("Histogram3", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowPos(ImVec2(50*windowFactor.x, 500*windowFactor.y),0);
  ImGui::PlotHistogram("", histogramDataEqualized, IM_ARRAYSIZE(histogramDataEqualized), 0, "Equalized", 0.f, maxValueEqualized, ImVec2(300*windowFactor.x,80*windowFactor.y));
  ImGui::End();

  ImGui::Begin("Histogram4", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove);
  ImGui::SetWindowPos(ImVec2(653*windowFactor.x,500*windowFactor.y),0);
  ImGui::PlotHistogram("", histogramDataOffsetEqualized, IM_ARRAYSIZE(histogramDataOffsetEqualized), 0, "Offset Equalized", 0.f, maxValueOffsetEqualized, ImVec2(300*windowFactor.x,80*windowFactor.y));
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
  windowFactor.y = getEngine()->getWindow()->getHeight()/1024.0f;
  windowFactor.x = getEngine()->getWindow()->getWidth()/1024.0f;

  memset(histogramDataOriginal,0, sizeof(histogramDataOriginal));
  memset(histogramDataOffset,0, sizeof(histogramDataOffset));
  memset(histogramDataOffsetEqualized,0, sizeof(histogramDataOffsetEqualized));
  memset(histogramDataEqualized,0, sizeof(histogramDataEqualized));

  auto dicomAsset = Asset("brain.dcm");
  gdcm::ImageReader imageReader;

  auto fileSize = dicomAsset.getIOStream()->fileSize();

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

void EditorGUI::mainMenu() {
  ImGui::BeginMainMenuBar();
  if (ImGui::BeginMenu("File"))
  {
    //ShowExampleMenuFile();
    if (ImGui::MenuItem("New Scene")) {}
    if (ImGui::MenuItem("Open Scene")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Save Scene")) {}
    if (ImGui::MenuItem("Save Scene as...")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("New Project")) {}
    if (ImGui::MenuItem("Open Project")) {}
    if (ImGui::MenuItem("Save Project")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Build Settings")) {}
    if (ImGui::MenuItem("Build and Run")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Close")) {
#ifndef EMSCRIPTEN
      exit(0);
#endif
    }

    ImGui::EndMenu();
  }

  if (ImGui::BeginMenu("Edit"))
  {
    if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
    if (ImGui::MenuItem("Redo", "CTRL+SHIFT+Z", false, false)) {}  // Disabled item
    ImGui::Separator();
    if (ImGui::MenuItem("Cut", "CTRL+X")) {}
    if (ImGui::MenuItem("Copy", "CTRL+C")) {}
    if (ImGui::MenuItem("Paste", "CTRL+V")) {}
    ImGui::Separator();
    if (ImGui::MenuItem("Duplicate", "CTRL+D")) {}
    if (ImGui::MenuItem("Delete", "Del")) {}
    ImGui::EndMenu();
  }
  ImGui::EndMainMenuBar();
}

void EditorGUI::options() {
  ImGui::BeginGroup();
  ImGui::Text("Choose your Algorithm:");
  if(ImGui::Button("Equalization")){option = 1;}
  if(ImGui::Button("High-Pass")){option=2;}
  ImGui::EndGroup();
}

void EditorGUI::equalize() {
  ImGui::BeginGroup();
  ImGui::Text("Type the offset to be added to image:");
  ImGui::InputInt("Offset", &imageOffset,1,2,0);

  if (applied == false && ImGui::Button("Apply offset and calculate"))
  {
    // apply offset
    applied = true;
    {
      auto modifiedData = firstImage->getTextureData()->data;
      for (int i = 0; i < modifiedData.size(); i += 4) {
        int newValue = modifiedData[i] + imageOffset;
        newValue = MIN(255, MAX(0, newValue));
        modifiedData[i] = newValue;   // r
        modifiedData[i + 1] = newValue; // g
        modifiedData[i + 2] = newValue; // b
      }
      unsigned char *newData = &modifiedData[0];

      auto newTextureData = std::make_shared<TextureData>(firstImage->width(), firstImage->height(), newData, GL_TEXTURE_2D, GL_LINEAR);
      secondImage = std::make_shared<Texture>(newTextureData);

      secondEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(secondImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      secondEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      secondEntity->getTransform()->setPosition(glm::vec3(-300, 0, 250));
      secondEntity->getTransform()->setScale(glm::vec3(300, 1, 300));
      rootScene->addChild(secondEntity);
    }

    // set histogram original
    {
      memset(histogramDataOriginal, 0, sizeof(histogramDataOriginal));
      for (int i = 0; i < firstImage->height() * firstImage->width(); i++) {
        auto color = firstImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
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
      for (int i = 0; i < secondImage->height() * secondImage->width(); i++) {
        auto color = secondImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
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
          255.0f * histogramDataOriginal[0] / (float) (firstImage->height() * firstImage->width());
      for (int i = 1; i < 256; i++)
        transferOriginal[i] = transferOriginal[i - 1] + 255.0f * histogramDataOriginal[i] /
                                                        (float) (firstImage->height() * firstImage->width());
      auto equalizedData = firstImage->getTextureData()->data;
      for (int i = 0; i < equalizedData.size(); i += 4) {
        int newValue = (int) floor(transferOriginal[equalizedData[i]]);
        newValue = MIN(255, MAX(0, newValue));
        equalizedData[i] = newValue;   // r
        equalizedData[i + 1] = newValue; // g
        equalizedData[i + 2] = newValue; // b
      }
      unsigned char *newEqualizedData = &equalizedData[0];

      auto newTextureData = std::make_shared<TextureData>(firstImage->width(),firstImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
      thirdImage = std::make_shared<Texture>(newTextureData);

      thirdEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(thirdImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      thirdEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      thirdEntity->getTransform()->setPosition(glm::vec3(300, 0, -250));
      thirdEntity->getTransform()->setScale(glm::vec3(300, 1, 300));
      rootScene->addChild(thirdEntity);
    }

    // new equalized image from offset
    {
      memset(transferOffset, 0, sizeof(transferOffset));
      transferOffset[0] = 255.0f * histogramDataOffset[0] / (float) (firstImage->height() * firstImage->width());
      for (int i = 1; i < 256; i++)
        transferOffset[i] = transferOffset[i - 1] + 255.0f * histogramDataOffset[i] / (float) (firstImage->height() * firstImage->width());
      auto equalizedData = secondImage->getTextureData()->data;
      for (int i = 0; i < equalizedData.size(); i += 4) {
        int newValue = (int) floor(transferOffset[equalizedData[i]]);
        newValue = MIN(255, MAX(0, newValue));
        equalizedData[i] = newValue;   // r
        equalizedData[i + 1] = newValue; // g
        equalizedData[i + 2] = newValue; // b
      }
      unsigned char *newEqualizedData = &equalizedData[0];

      auto newTextureData = std::make_shared<TextureData>(firstImage->width(),firstImage->height(), newEqualizedData ,GL_TEXTURE_2D,GL_LINEAR);
      forthImage = std::make_shared<Texture>(newTextureData);

      forthEntity = std::make_shared<Entity>();
      auto modifiedMat = std::make_shared<Material>(forthImage, normalTexture, specularTexture);
      auto modifiedMesh = Plane::getMesh();
      forthEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
      forthEntity->getTransform()->setPosition(glm::vec3(-300, 0, -250));
      forthEntity->getTransform()->setScale(glm::vec3(300, 1, 300));
      rootScene->addChild(forthEntity);
    }

    // set histogram equalized
    {
      memset(histogramDataEqualized, 0, sizeof(histogramDataEqualized));
      for (int i = 0; i < secondImage->height() * secondImage->width(); i++) {
        auto color = thirdImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
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
      for (int i = 0; i < forthImage->height() * forthImage->width(); i++) {
        auto color = forthImage->getTextureData()->data[i * 4]; // get the red channel of the grayscale rgba image
        histogramDataOffsetEqualized[color] += 1;
      }
      maxValueOffsetEqualized = 0;
      for (int i = 0; i < 255; i++)
        if (histogramDataOffsetEqualized[i] > maxValueOffsetEqualized)
          maxValueOffsetEqualized = histogramDataOffsetEqualized[i];
    }
  }
  ImGui::EndGroup();

}

void EditorGUI::highPass() {
  applied = true;
  auto outputdata = new unsigned char[firstImage->getTextureData()->data.size()];
  Laplace(& (firstImage->getTextureData()->data[0]),outputdata,firstImage->width(),firstImage->height());


  auto newTextureData = std::make_shared<TextureData>(firstImage->width(), firstImage->height(), outputdata, GL_TEXTURE_2D, GL_LINEAR);
  secondImage = std::make_shared<Texture>(newTextureData);

  secondEntity = std::make_shared<Entity>();
  auto modifiedMat = std::make_shared<Material>(secondImage, normalTexture, specularTexture);
  auto modifiedMesh = Plane::getMesh();
  secondEntity->addComponent<MeshRenderer>(modifiedMesh, modifiedMat);
  secondEntity->getTransform()->setPosition(glm::vec3(-300, 0, 250));
  secondEntity->getTransform()->setScale(glm::vec3(300, 1, 300));
  rootScene->addChild(secondEntity);
  
  delete[] outputdata;
}

void EditorGUI::Laplace(unsigned char * input, unsigned char * output, int width, int height, int bytesPerChannels, int numberOfChannels)
{
  if(numberOfChannels!=4 || bytesPerChannels!=1)
    throw NotImplementedException();

  for(int line =0;line<height;line++){
    for(int column =0;column<width;column++){
      int pos = (line * width + column) * numberOfChannels * bytesPerChannels;
	  unsigned char color = LaplaceMask(input, width, height, line, column);
      output[pos]  =color;
      output[pos+1]=color;
      output[pos+2]=color;
      output[pos+3]=255;
    }
  }
}

unsigned char EditorGUI::LaplaceMask(unsigned char* input, int width, int height, int line, int column, int bytesPerChannels, int numberOfChannels)
{
  // TODO: handle borders
  if (column >= width || column <= 0 || line >= height || line <= 0)
    return 0;

  float laplace[] = {-1,-1,-1,-1,8,-1,-1,-1,-1};
  float ret = 0;
  for (int y = -1; y <= 1; y++) {
	for (int x = -1; x <= 1; x++) {
	  int pos = ((line+y) * width + column+x) * numberOfChannels * bytesPerChannels;
	  float color = 0;
	  for (auto i = 0; i < numberOfChannels - 1; i++)
		color += input[pos + i];
	  color /= numberOfChannels - 1;
	  color *= laplace[x + 1 + (y + 1) * 3];
	  ret += color;
	}
  }
  
  return (unsigned char) MIN(MAX(ret,0),255);
}
