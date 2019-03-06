#ifndef ANDROID
  #include <GL/glew.h>
#endif

#include "GLEWManager.hpp"

#include "Logger.hpp"

namespace mobagen {
  GLEWManager::GLEWManager(void) {
#ifndef ANDROID
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();

    if (GLEW_OK != err) {
      log_err("GLEW failed to initalize: %s", glewGetErrorString(err));
    }

    log_info("Status: Using GLEW %s", glewGetString(GLEW_VERSION));
#endif
  }

  GLEWManager::~GLEWManager(void) {}
}