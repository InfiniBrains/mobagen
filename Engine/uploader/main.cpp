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

class Uploader : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(double delta);
};

void Uploader::update(double delta)
{
  Game::update(delta);
}

void Uploader::init(GLManager *glManager)
{
  // init editorgui
  getRootScene()->addComponent<EditorGUI>();
  getRootScene()->getComponent<EditorGUI>()->rootScene = getRootScene();

  auto cam = std::make_shared<Entity>();
  cam->addComponent<OrthoCamera>(getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 512, 0.01f, 10000.0f);
  addToScene(cam);

  auto primary_camera = cam->getComponent<OrthoCamera>();
  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  Uploader game;
  Engine gameEngine(&game, "UPLOADER", glm::vec2(800,400));

  gameEngine.start();

  return 0;
}
