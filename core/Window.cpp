#include "Window.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <stdexcept>

#include <SDL.h>
#ifdef EMSCRIPTEN
EM_JS(int, canvas_get_width, (), {
return canvas.width;
});

EM_JS(int, canvas_get_height, (), {
return canvas.height;
});
#endif

Window::Window(std::string title) {
    // Setup SDL
    // (Some versions of SDL before <2.0.10 appears to have performance/stalling issues on a minority of Windows systems,
    // depending on whether SDL_INIT_GAMECONTROLLER is enabled or disabled.. updating to latest version of SDL is recommended!)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("SDL INIT");

//    SDL_DisplayMode mode;
//    SDL_GetCurrentDisplayMode(0, &mode);

//    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
//    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8 * 4);
//    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8 * 2);
//    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
//
//#if defined(GLES3)
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
//#elif defined(GLES2)
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
//#elif defined(EMSCRIPTEN)
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
//#else
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
//    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
//#endif

    auto width = 1280;
    auto height = 720;
#ifdef EMSCRIPTEN
    width = canvas_get_width();
    height = canvas_get_height();
#endif


    // Setup window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    //auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    auto window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
    sdlWindow = SDL_CreateWindow("Dear ImGui SDL2+OpenGL example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, window_flags);

    if (sdlWindow == nullptr) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("SDL WINDOW CREATED");

    // Setup SDL_Renderer instance
//    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
//    if (sdlRenderer == nullptr) {
//        SDL_Log("Error creating SDL_Renderer!");
//        throw std::runtime_error("Error creating SDL_Renderer!");
//    }

//    SDL_RendererInfo info;
//    SDL_GetRendererInfo(sdlRenderer, &info);
//    SDL_Log("Current SDL_Renderer: %s", info.name);

// Setup Platform/Renderer backends
//    ImGui_ImplSDL2_InitForSDLRenderer(sdlWindow, sdlRenderer);
//    ImGui_ImplSDLRenderer_Init(sdlRenderer);

    SDL_GLContext gl_context = SDL_GL_CreateContext(sdlWindow);

    m_glContext = SDL_GL_CreateContext(sdlWindow);
    if (m_glContext == nullptr) {
        printf("SDL_GL_CreateContext Error: %s\n", SDL_GetError());
        throw std::runtime_error(SDL_GetError());
    }
    SDL_Log("SDL GL CONTEXT CREATED");

    SDL_GL_MakeCurrent(sdlWindow, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync
//    SDL_GL_SetSwapInterval(0);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGui_ImplSDL2_InitForOpenGL(sdlWindow, m_glContext);
    ImGui_ImplOpenGL2_Init();

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != NULL);
}

Window::~Window() {
//    SDL_DestroyRenderer(sdlRenderer);
    SDL_GL_DeleteContext(m_glContext);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
}

// todo: cache this per frame to avoid call SDL_GetWindowSize every single call
// todo: this should be integer return
Vector2 Window::size() const {
    // int display_w, display_h;
    // SDL_GL_GetDrawableSize(sdlWindow, &display_w, &display_h);

    int x,y;
    SDL_GetWindowSize(this->sdlWindow,&x, &y);
    return {(float)x,(float)y};
}
