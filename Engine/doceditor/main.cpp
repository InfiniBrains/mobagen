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

  // load assets
  auto normal = std::make_shared<Texture>(Asset("default_normal.jpg"));
  auto specular = std::make_shared<Texture>(Asset("default_specular.jpg"));

  auto planeEntity = std::make_shared<Entity>();
  planeEntity->addComponent<EditorGUI>();
  planeEntity->getComponent<EditorGUI>()->originalImage = std::make_shared<Texture>(Asset("boat.png"));

  auto backgroundMat = std::make_shared<Material>(planeEntity->getComponent<EditorGUI>()->originalImage, normal, specular);
  auto backgroundMesh = Plane::getMesh();
  planeEntity->addComponent<MeshRenderer>(backgroundMesh, backgroundMat);
  planeEntity->getTransform().setPosition(glm::vec3(0, -10, 0));
  planeEntity->getTransform().setScale(glm::vec3(512, 1, 512));
  addToScene(planeEntity);



  auto cam = std::make_shared<Entity>();
  cam->addComponent<PerspectiveCamera>(glm::pi<float>() / 4.0f * 0.96f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.01f, 10000.0f);
  cam->getTransform().setPosition(glm::vec3(0, getEngine()->getWindow()->getWidth(), 0));
  cam->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  cam->getTransform().setRotation(glm::quat(0, 0, 0.707, 0.707));
  cam->addComponent<DirectionalLight>(glm::vec3(1,1,1), 0.5);
  addToScene(cam);

  auto primary_camera = cam->getComponent<PerspectiveCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  DocEditor game;
  Engine gameEngine(&game, "DocEditor", glm::vec2(1024,1024));

  gameEngine.start();

  return 0;
}
