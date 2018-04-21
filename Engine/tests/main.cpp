#include "components/MeshRenderer.hpp"
#include "components/PerspectiveCamera.hpp"
#include "components/OrthoCamera.hpp"
#include "components/FreeMove.hpp"
#include "components/FreeLook.hpp"
#include "components/DirectionalLight.hpp"
#include "components/SpotLight.hpp"
#include "components/PointLight.hpp"
#include "components/Sphere.hpp"

#include "Plane.hpp"
#include "Mesh.hpp"
#include "Texture.hpp"
#include "Logger.hpp"
#include "MeshLoader.hpp"
#include "Engine.hpp"
#include <SDL_main.h>
#include <iostream>
#include <map>
#include <random>
#include <GameObject.hpp>

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
  auto cam = new GameObject("MainCamera");
  cam->AddComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);

//  cam->getTransform()->setPosition(glm::vec3(0, 512, 0));
//  cam->getTransform()->setScale(glm::vec3(1, 1, 1));
//  cam->getTransform()->setRotation(glm::quat(0, 0, 0.707, 0.707));
//  cam->addComponent<DirectionalLight>(glm::vec3(1,1,1), 0.5);
//  addToScene(cam);

  //auto primary_camera = cam->getComponent<OrthoCamera>();
  std::shared_ptr<OrthoCamera> o(cam->GetComponent<OrthoCamera>());
  getEngine()->getGLManager()->setActiveCamera(o);
}

int main(int argc, char *argv[]) {
  DocEditor game;
  Engine gameEngine(&game, "Tests", glm::vec2(800,800));

  gameEngine.start();

  return 0;
}
