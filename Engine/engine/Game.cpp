#include "Game.hpp"
#include "GameObject.hpp"
namespace mobagen {
  Game::Game(void) {
    this->rootScene = std::make_shared<Entity>();
  }

  Game::~Game(void) {
  }

  void Game::setEngine(Engine *engine) {
    this->engine = engine;
  }

  Engine *Game::getEngine(void) const {
    return engine;
  }

  void Game::init(GLManager *glManager) {
  }

  void Game::addToScene(std::shared_ptr<Entity> entity) {
    rootScene->addChild(entity);
  }

  void Game::updateInput(Input *input, double delta) {
    rootScene->updateInputAll(input, delta);
  }

  void Game::update(double delta) {
    rootScene->updateAll(delta);
//  for(auto go : GameObject::){
//
//  }
  }

  void Game::render(GLManager *glManager) {
    glManager->renderScene(rootScene.get());
  }
}