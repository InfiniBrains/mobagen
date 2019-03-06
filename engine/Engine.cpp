#include "Engine.hpp"
#include "Logger.hpp"
#include "Ray.hpp"
#include "GuiManager.hpp"
#include "ForwardRenderer.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <limits>

#ifdef EMSCRIPTEN
#include <emscripten.h>
#endif

// TODO: DO WE NEED FIXED UPDATES?
// std::chrono::microseconds FIXED_TIME_STEP(std::chrono::milliseconds(20));

namespace mobagen {
#ifdef EMSCRIPTEN
  static Engine *instance = NULL;
#endif

  Engine::Engine(Game *game, char *windowTitle, glm::vec2 windowSize) {
    log_info("Initializing SDL");
    m_window = std::make_unique<Window>(windowTitle, windowSize);

    log_info("Initializing GLEW");
    m_glewManager = std::make_unique<GLEWManager>();

    log_info("Initializing GL");
    m_glManager = std::make_unique<GLManager>(std::make_unique<ForwardRenderer>(), m_window->getDrawableSize());

    log_info("Initializing Physics Manager");
    m_physicsManager = std::make_unique<PhysicsManager>();

    this->game = game;

    quit = false;
    m_fireRay = false;
  }

  Engine::~Engine(void) {
  }

  void Engine::start(void) {
    game->setEngine(this);

    game->getRootScene()->registerWithEngineAll(this);

    log_info("Initializing game");

    m_window->init();

    game->init(m_glManager.get());

    m_window->makeCurrentContext();

    m_window->getInput()->registerKeyToAction(SDLK_F1, "propertyEditor");
    m_window->getInput()->registerKeyToAction(SDLK_F2, "fullscreenToggle");

    m_window->getInput()->registerButtonToAction(SDL_BUTTON_LEFT, "fireRay");

    m_window->getInput()->bindAction("propertyEditor", IE_PRESSED, [this]() {
      m_window->getGuiManager()->togglePropertyEditor();
    });

    m_window->getInput()->bindAction("fullscreenToggle", IE_PRESSED, [this]() {
      m_window->toggleFullscreen();
      m_glManager->setDrawSize(m_window->getDrawableSize());
    });

    m_window->getInput()->bindAction("fireRay", IE_PRESSED, [this]() {
      m_fireRay = true;
    });

    m_window->getInput()->bindAction("fireRay", IE_RELEASED, [this]() {
      m_fireRay = false;
    });

    m_time = std::chrono::high_resolution_clock::now();
    // TODO: DO WE NEED FIXED UPDATES?
    //m_physicsTimeSimulated = std::chrono::high_resolution_clock::now();

#ifdef EMSCRIPTEN
    instance = this;

    emscripten_set_main_loop(Engine::loop, 0, 1);
#else
    while (!quit) {
      tick();
    }
#endif
  }

#ifdef EMSCRIPTEN
  void Engine::loop(void)
  {
    instance->tick();
  }
#endif

  void Engine::tick(void) {
    m_lastTime = m_time;
    m_time = std::chrono::high_resolution_clock::now();
    m_deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(m_time - m_lastTime);

    m_window.get()->tick();
    m_window.get()->getGuiManager()->tick(m_window.get(), m_deltaTime);

    quit = m_window.get()->shouldQuit();

    m_physicsManager.get()->tick(m_deltaTime);

    /* TODO: DO WE NEED FIXED UPDATES?
    while (m_physicsTimeSimulated < m_time) {

      m_physicsTimeSimulated += FIXED_TIME_STEP;
    }*/

    game->update(m_window->getInput(), m_deltaTime);

    game->render(m_glManager.get());

//    if (m_fireRay) {
//      Ray ray = Ray::getPickRay(m_window->getInput()->getMousePosition(), m_window->getViewport(),
//                                m_glManager->getViewMatrix(), m_glManager->getProjectionMatrix());
//
//      Entity *pickedEntity = m_physicsManager->pick(&ray);
//
//      if (pickedEntity != nullptr) {
//        m_glManager->drawEntity(pickedEntity);
//      }
//
//      m_glManager->drawLine(ray.getLine(10000.0f));
//    }

    m_window->getGuiManager()->render(game->getRootScene().get());

    m_window->swapBuffer();
  }

  Window *Engine::getWindow(void) const {
    return m_window.get();
  }

  GLManager *Engine::getGLManager(void) const {
    return m_glManager.get();
  }

  PhysicsManager *Engine::getPhysicsManager(void) const {
    return m_physicsManager.get();
  }

  std::chrono::microseconds Engine::getDeltaTime(void) const {
    return m_deltaTime;
  }

}