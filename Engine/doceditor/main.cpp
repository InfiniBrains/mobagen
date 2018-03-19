#include "components/MeshRenderer.h"
#include "components/PerspectiveCamera.h"
#include "components/OrthoCamera.h"
#include "components/FreeMove.h"
#include "components/FreeLook.h"
#include "components/DirectionalLight.h"
#include "components/SpotLight.h"
#include "components/PointLight.h"
#include "components/Sphere.h"

#include "Plane.h"
#include "Mesh.h"
#include "Texture.h"
#include "Logger.h"
#include "MeshLoader.h"
#include "Engine.h"
#include "EditorGUI.h"
#include <SDL_main.h>
#include <iostream>
#include <map>
#include <random>

class DocEditor : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(double delta);
};

void DocEditor::update(double delta)
{
  Game::update(delta);
}

void DocEditor::init(GLManager *glManager)
{
  // init editorgui
  getRootScene()->addComponent<EditorGUI>();
  getRootScene()->getComponent<EditorGUI>()->rootScene = getRootScene();

  // load assets
  getRootScene()->getComponent<EditorGUI>()->normalTexture = std::make_shared<Texture>(Asset("default_normal.jpg"));
  getRootScene()->getComponent<EditorGUI>()->specularTexture = std::make_shared<Texture>(Asset("black.jpg"));

  auto planeEntity = std::make_shared<Entity>();
  getRootScene()->getComponent<EditorGUI>()->originalImage = std::make_shared<Texture>(Asset("boat.png"));
  getRootScene()->getComponent<EditorGUI>()->originalEntity = planeEntity;
  auto backgroundMat = std::make_shared<Material>(getRootScene()->getComponent<EditorGUI>()->originalImage, getRootScene()->getComponent<EditorGUI>()->normalTexture, getRootScene()->getComponent<EditorGUI>()->specularTexture);
  auto backgroundMesh = Plane::getMesh();
  planeEntity->addComponent<MeshRenderer>(backgroundMesh, backgroundMat);
  planeEntity->getTransform().setPosition(glm::vec3(300, 0, 250));
  planeEntity->getTransform().setScale(glm::vec3(300, 1, 300));
  addToScene(planeEntity);

  auto planeSpotLight =  std::make_shared<Entity>();
  planeSpotLight->addComponent<DirectionalLight>(glm::vec3(1,1,1), 0.5);
  planeSpotLight->getTransform().setPosition(glm::vec3(0, 512, 0));
  planeSpotLight->getTransform().setRotation(glm::quat(0, 0, 0.707, 0.707));
  addToScene(planeSpotLight);

  auto cam = std::make_shared<Entity>();
  cam->addComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);
  cam->getTransform().setPosition(glm::vec3(0, 512, 0));
  cam->getTransform().setScale(glm::vec3(1, 1, 1));
  cam->getTransform().setRotation(glm::quat(0, 0, 0.707, 0.707));
  //cam->addComponent<DirectionalLight>(glm::vec3(1,1,1), 0.5);
  addToScene(cam);

  auto primary_camera = cam->getComponent<OrthoCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  DocEditor game;
  Engine gameEngine(&game, "DocEditor", glm::vec2(1024,1024));

  gameEngine.start();

  return 0;
}
