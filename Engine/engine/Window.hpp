//
//  Author: Shervin Aflatooni
//

#pragma once

#include "settings.hpp"
#include "Input.hpp"

#include <string>
#include <memory>

#include <glm/glm.hpp>
#include <SDL.h>

#if _WIN32
  // https://stackoverflow.com/questions/4845410/error-lnk2019-unresolved-external-symbol-main-referenced-in-function-tmainc
  #undef main
#endif

class GuiManager;

class Window
{
public:
  Window(char * title, glm::vec2 windowSize);
  ~Window(void);

  void init(void);

  void tick(double deltaTime);
  void swapBuffer(void);
  int poll_event(SDL_Event *event);

  int getWidth(void) const;
  int getHeight(void) const;
  glm::vec4 getViewport(void) const;
  glm::vec2 getDisplaySize(void) const;
  glm::vec2 getDrawableSize(void) const;

  GuiManager *getGuiManager(void) const;

  static const char* getClipboardText();
  static void setClipboardText(const char* text);

  void makeCurrentContext(void) const;

  Input* getInput(void);
  SDL_Window* getSDLWindow(void);

  bool shouldQuit(void) const;

  void drawCursor(bool enabled);

private:
  SDL_Window    *m_window;
  SDL_GLContext m_glContext;
  std::unique_ptr<GuiManager> m_guiManager;

  int m_width, m_height;

  Input m_input;

  bool m_quit;
};