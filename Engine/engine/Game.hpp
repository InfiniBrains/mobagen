#pragma once

#include "Entity.hpp"
#include "GLManager.hpp"
#include "Input.hpp"

class Engine;

class Game
{
public:
  Game(void);
  virtual ~Game(void);

  void setEngine(Engine *engine);

  virtual void init(GLManager *glManager);

  virtual void updateInput(Input *input, double delta);
  virtual void update(double delta);
  virtual void render(GLManager *glManager);

  inline std::shared_ptr<Entity> getRootScene(void) { return rootScene; };

protected:
  void addToScene(std::shared_ptr<Entity> entity);
  Engine *getEngine(void) const;

private:
  std::shared_ptr<Entity> rootScene;
  Engine *engine;
};