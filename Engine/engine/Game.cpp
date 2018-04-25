#include "Game.hpp"

Game::Game(void)
{
  this->rootScene = std::make_shared<Entity>();
}

Game::~Game(void)
{
}

void Game::setEngine(Engine *engine)
{
  this->engine = engine;
}

Engine *Game::getEngine(void) const
{
  return engine;
}

void Game::init(GLManager *glManager)
{
}

void Game::addToScene(std::shared_ptr<Entity> entity)
{
  rootScene->addChild(entity);
}

void Game::updateInput(Input *input, double delta)
{
  rootScene->updateInputAll(input, delta);
}

void Game::update(double delta)
{
  rootScene->updateAll(delta);
}

void Game::render(GLManager *glManager)
{
  glManager->renderScene(rootScene.get());
}
