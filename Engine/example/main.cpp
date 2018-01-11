//
//  Author: Shervin Aflatooni
//

#include "Engine.h"

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

#include <SDL_main.h>

class CoolGame : public Game
{
public:
  virtual void init(GLManager *glManager);
  virtual void update(int delta);
};

void CoolGame::update(int delta)
{
  static float angle = 0;
  angle += delta * 0.0008;
  // plane->getTransform().setRotation(glm::vec3(1, 0, 0), angle);
  //plane->getTransform().setPosition(glm::vec3(glm::sin(angle) * 5, 0, 0));

  Game::update(delta);
}

void CoolGame::init(GLManager *glManager)
{
  /*auto brickMat = std::make_shared<Material>(std::make_shared<Texture>(Asset("bricks2.jpg")), std::make_shared<Texture>(Asset("bricks2_normal.jpg")), std::make_shared<Texture>(Asset("bricks2_specular.png")));
  auto planeMesh = Plane::getMesh();
  auto plane = std::make_shared<Entity>();
  plane->addComponent<MeshRenderer>(planeMesh, brickMat);
  plane->getTransform().setPosition(glm::vec3(0, -2, 0));
  plane->getTransform().setScale(glm::vec3(10, 10, 10));

  addToScene(plane);

  auto plane2 = std::make_shared<Entity>();
  plane2->addComponent<MeshRenderer>(planeMesh, brickMat);
  plane2->getTransform().setPosition(glm::vec3(0, 3, -5));
  plane2->getTransform().setScale(glm::vec3(10, 10, 10));
  plane2->getTransform().rotate(glm::vec3(1, 0, 0), glm::pi<float>() / 2.f);

  addToScene(plane2);

  for (int i = 0; i < 1; i++) {
    MeshLoader ml("Pregnant.obj");
    ml.getEntity()->getTransform().setPosition(glm::vec3(0 + (i * 3), -2, 0));
    ml.getEntity()->addComponent<Sphere>(1);
    addToScene(ml.getEntity());
  }*/

  MeshLoader arteria("arteria2.stl");
  arteria.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2));
 // money.getEntity()->addComponent<PerspectiveCamera>(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 100.0f);
  //money.getEntity()->addComponent<Sphere>(1);
  //money.getEntity()->addComponent<SpotLight>(glm::vec3(0.1f, 1.0f, 1.0f), 5.8f, 0.7f, std::make_shared<Attenuation>(0, 0, 0.2));
  addToScene(arteria.getEntity());

  MeshLoader coletor("coletor2.stl");
  coletor.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2));
  addToScene(coletor.getEntity());

  MeshLoader esqueleto("esqueleto3.stl");
  esqueleto.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2));
  addToScene(esqueleto.getEntity());

  MeshLoader rim("rim2.stl");
  rim.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2));
  addToScene(rim.getEntity());

  MeshLoader veia("veia2.stl");
  veia.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2));
  addToScene(veia.getEntity());

  MeshLoader tumor("tumor2.stl");
  tumor.getEntity()->getTransform().setPosition(glm::vec3(0, 0, -2));
  addToScene(tumor.getEntity());

  auto money2 = std::make_shared<Entity>();
  money2->addComponent<PerspectiveCamera>(glm::pi<float>() / 2.0f, getEngine()->getWindow()->getWidth() / (float)getEngine()->getWindow()->getHeight(), 0.9f, 10000.0f);
  money2->addComponent<FreeMove>();
#if defined(ANDROID)
  money2->addComponent<FreeLook>(0.0001f);
#else
  money2->addComponent<FreeLook>();
#endif
  money2->getTransform().setPosition(glm::vec3(0, 300, 0));
  money2->getTransform().setScale(glm::vec3(0.8, 0.8, 0.8));
  money2->getTransform().setRotation(glm::quat(0, 0, 0.707, 0.707));
  money2->addComponent<SpotLight>(glm::vec3(1.0f, 1.0f, 1.0f), 1.8f, 0.7f, std::make_shared<Attenuation>(0, 0, 0.2));

  addToScene(money2);

  auto primary_camera = money2->getComponent<PerspectiveCamera>();

  getEngine()->getGLManager()->setActiveCamera(primary_camera);
}

int main(int argc, char *argv[]) {
  CoolGame game;
  Engine gameEngine(&game);

  gameEngine.start();

  return 0;
}
