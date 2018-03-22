#include "Engine.h"
#include "Logger.h"
#include "Ray.h"
#include "GuiManager.h"
#include <memory>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <limits>

#ifdef EMSCRIPTEN
  #include <emscripten.h>
  static Engine *instance = NULL;
#else
#include <thread>
#endif

//#ifdef __MINGW32__
//#include "mingw.thread.h"
//#endif


Engine::Engine(Game *game, char * windowTitle, glm::vec2 windowSize)
{
  log_info("Initializing SDL");
  m_window = std::make_unique<Window>(windowTitle, windowSize);

  log_info("Initializing GL");
  m_glManager = std::make_unique<GLManager>(m_window.get());

  log_info("Initializing GLEW");
  m_glewManager = std::make_unique<GLEWManager>();


  log_info("Initializing Physics Manager");
  m_physicsManager = std::make_unique<PhysicsManager>();

  this->game = game;

  m_deltaTime = 1 / 60.0;

  quit = false;
}

Engine::~Engine(void)
{
}

void Engine::start(void)
{
  game->setEngine(this);

  game->getRootScene()->registerWithEngineAll(this);

  log_info("Initializing game");

  m_window->init();

  game->init(m_glManager.get());

  m_window->makeCurrentContext();

  lastUpdateTime = std::chrono::high_resolution_clock::now();

#ifdef EMSCRIPTEN
  instance = this;
  emscripten_set_main_loop(Engine::loop, 0, 1);
#else
  auto accumulatedTime = std::chrono::duration<double>(std::chrono::duration_values<double>::zero());
  while (!quit) {
	// run engine loop
	tick(); 
	// get time
	const auto afterTick = std::chrono::high_resolution_clock::now();
	
	// sleep
    std::chrono::duration<double> sleepTime;
    sleepTime = std::chrono::duration<double>(1 / 60.0) - (afterTick - lastUpdateTime) - accumulatedTime;


	if (sleepTime.count() > 0)
#ifndef __MINGW32__
		std::this_thread::sleep_for(sleepTime); //SDL_Delay(sleepTime);
#else
        SDL_Delay(std::chrono::duration_cast<std::chrono::milliseconds>(sleepTime).count());
#endif
	// get the sleep error and store the lastFrame time duration
	auto now = std::chrono::high_resolution_clock::now();
	m_deltaTime = (now - lastUpdateTime).count()/1000000000.0;
	lastUpdateTime = now;
	accumulatedTime = (lastUpdateTime - afterTick) - sleepTime;
  }
#endif
}

#ifdef EMSCRIPTEN
void Engine::loop(void)
{
  instance->tick();
}
#endif

void Engine::tick(void)
{
  m_window->tick(m_deltaTime);

  quit = m_window->shouldQuit();

  game->updateInput(m_window->getInput(), getDeltaTime());

  game->update(getDeltaTime());

  game->render(m_glManager.get());

  static bool f1Pressed = false;

  if (!f1Pressed && m_window->getInput()->isPressed(SDLK_F1)) {
    f1Pressed = true;
    m_window->getGuiManager()->togglePropertyEditor();
  } else if (f1Pressed && m_window->getInput()->isReleased(SDLK_F1)) {
    f1Pressed = false;
  }

  m_window->getGuiManager()->render(game->getRootScene().get());

  m_window->swapBuffer();
#if EMSCRIPTEN
  auto now = std::chrono::high_resolution_clock::now();
  m_deltaTime = (now - lastUpdateTime).count()/1000000000.0;
  lastUpdateTime = now;
#endif
}

Window *Engine::getWindow(void) const
{
  return m_window.get();
}

GLManager *Engine::getGLManager(void) const
{
  return m_glManager.get();
}

PhysicsManager *Engine::getPhysicsManager(void) const
{
  return m_physicsManager.get();
}

double Engine::getDeltaTime()
{
	return m_deltaTime;
}
