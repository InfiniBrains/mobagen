#include <Engine.h>
#include "World.h"
// Main code
int main(int, char**) {
  SDL_Log("Creating Engine");
  auto engine = new Engine();
  SDL_Log("Engine Created");

  SDL_Log("Starting Engine");
  if(engine->Start("Editor")) {
    SDL_Log("Engine Started");
    engine->Run();
  }

  SDL_Log("Exiting Engine");
  engine->Exit();
  SDL_Log("Engine Exited");
  auto w = new World(21);
  w->print();

  return 0;
}

