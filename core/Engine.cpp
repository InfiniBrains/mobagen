#include "Engine.h"
#include "SDL.h"
#include "Polygon.h"

#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl2.h"
#include <SDL.h>
#include <SDL_opengl.h>

#ifdef EMSCRIPTEN
static Engine *instance = nullptr;
void Engine::loop(void){
  instance->Tick();
}
#endif

Engine::Engine() {
#ifdef EMSCRIPTEN
    instance = nullptr;
#endif
    window = nullptr;
}

Engine::~Engine() {
    if(window) {
        // Cleanup
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        delete (window);
    }

    for(auto go : gameObjects)
        delete(go); // clear all remaining game objects
    gameObjects.clear();
}

void Engine::Run() {
    // Main loop
#ifndef EMSCRIPTEN
    while (!done) { Tick(); }
    Exit();
#endif
}

int Engine::Start(std::string title) {
    SDL_Log("Initializing Window");
    window = new Window(title);
    if(window != nullptr)
        SDL_Log("Window Initialized");
    else
        exit(0);

    imGuiContext = ImGui::GetCurrentContext(); // todo: make this work on all game objects

    // start all gameobjects
    for(auto go : gameObjects)
        go->Start();
#ifdef EMSCRIPTEN
    SDL_Log("Setting main loop for emscripten");
    instance = this;
    emscripten_set_main_loop(Engine::loop, 0, 1); // should be called only after sldrenderinit
    SDL_Log("Main loop set");
#endif
    return true;
}

void Engine::Tick() {
    // Start the Dear ImGui frame
    //ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // inputs processing
    processInput();

    // update
    auto io = ImGui::GetIO();
    auto deltaTime = io.DeltaTime;
    for(auto go : gameObjects)
        go->Update(deltaTime);

    // iterate over all game objects ui
    imGuiContext = ImGui::GetCurrentContext();
    auto gos = gameObjects; // clone to prevent out of bounds access
    for(auto go : gos)
        go->OnGui(imGuiContext); // todo: find a better way to pass imgui context

    // Rendering
    ImGui::Render();

    // Rendering
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    auto windowSize = Vector2(io.DisplaySize.x, io.DisplaySize.y);

    // Draw
    for(auto go : gameObjects)
        go->OnDraw(windowSize);

    //glUseProgram(0); // You may want this if using this code in an OpenGL 3+ context where shaders may be bound
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());


    // destroy objects marked to death
    if(!toDestroy.empty()) {
        for (auto go: toDestroy) {
            gameObjects.erase(go);
            delete (go);
        }
        toDestroy.clear();
    }

    SDL_GL_SwapWindow(window->sdlWindow);
#ifndef EMSCRIPTEN
    SDL_Delay(0);
#endif
}

void Engine::Exit() {
    SDL_Log("Exit called");
    done = true;
    SDL_Log("Game Objects Cleared");
}

void Engine::processInput() {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
    // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.

    // todo: move this to Input
    static bool up = false, down = false, left = false, right = false;

    // clean the state
    arrowInput = Vector2();

    // process events
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT)
            done = true;
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window->sdlWindow))
            done = true;

        // todo: improve the key strokes tracking
        switch(event.type){
            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        left = true;
                        break;
                    case SDLK_RIGHT:
                        right = true;
                        break;
                    case SDLK_UP:
                        up = true;
                        break;
                    case SDLK_DOWN:
                        down = true;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch( event.key.keysym.sym ){
                    case SDLK_LEFT:
                        left = false;
                        break;
                    case SDLK_RIGHT:
                        right = false;
                        break;
                    case SDLK_UP:
                        up = false;
                        break;
                    case SDLK_DOWN:
                        down = false;
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    if(up) arrowInput+=Vector2::up();
    if(down) arrowInput+=Vector2::down();
    if(left) arrowInput+=Vector2::left();
    if(right) arrowInput+=Vector2::right();
}

Vector2 Engine::getInputArrow() const {
    return arrowInput;
}

// todo: optimize this
template<class T>
std::unordered_set<T> Engine::FindObjectsOfType() {
    std::unordered_set<T> ret;
    for (GameObject* go: gameObjects)
        if ( T elem = dynamic_cast<T>( &go ) ) // todo: check this
           ret.insert(elem);

    return ret;
}

// todo: optimize this
void Engine::Destroy(GameObject *go) {
    toDestroy.push_back(go);
}


