#pragma once
#include "GLManager.hpp"
#include "Window.hpp"
#include "GLEWManager.hpp"
#include "PhysicsManager.hpp"

#include "Game.hpp"

#include "Input.hpp"
#include "components/Sphere.hpp"
#include <chrono>

class Engine
{
public:
  Engine(Game *game, char * windowTitle, glm::vec2 windowSize);
  ~Engine(void);

#ifdef EMSCRIPTEN
  static void loop(void);
#endif

  void tick(void);
  void start(void);

  Window         *getWindow(void) const;
  GLManager      *getGLManager(void) const;
  PhysicsManager *getPhysicsManager(void) const;
  double         getDeltaTime();
private:
  std::unique_ptr<Window> m_window;
  std::unique_ptr<GLEWManager> m_glewManager;
  std::unique_ptr<GLManager> m_glManager;
  std::unique_ptr<PhysicsManager> m_physicsManager;

  std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;

  Game *game;

  Input input;

  bool quit;
  double m_deltaTime;
};
