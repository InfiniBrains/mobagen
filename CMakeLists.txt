cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

IF(EMSCRIPTEN)
    IF (WIN32)
        MESSAGE(FATAL_ERROR "EMSCRIPTEN BUILD NOT SUPPORTED ON WINDOWS")
        MESSAGE(STATUS "INITIALIZING EMSDK")
        execute_process(COMMAND git submodule update --init --recursive )
        execute_process(COMMAND cmd /c "${CMAKE_SOURCE_DIR}/scripts/win-set-env-vars.bat")
        MESSAGE(FATAL_ERROR "PLEASE RESTART YOUR COMPUTER TO RELOAD ENV VARS")
    ELSEIF(NOT DEFINED ENV{EMSDK})
        MESSAGE(STATUS "INITIALIZING EMSDK")
        execute_process(COMMAND git submodule update --init --recursive )
        execute_process(COMMAND external/emsdk/emsdk install latest)
        execute_process(COMMAND external/emsdk/emsdk activate latest --system)
        MESSAGE(FATAL_ERROR "PLEASE RESTART YOUR COMPUTER TO RELOAD ENV VARS")
    ELSEIF(DEFINED ENV{EMSDK})
        MESSAGE(STATUS "EMSDK FOUND AT $ENV{EMSDK}")
        execute_process(COMMAND cmd /c emcc --version RESULT_VARIABLE rv)
        LIST(APPEND CMAKE_PROGRAM_PATH  "$ENV{EMSDK}/upstream/bin")
        SET(ENV{EMSCRIPTEN} $ENV{EMSDK}/upstream/emscripten)
        MESSAGE(STATUS "EMSCRIPTEN PATH: $ENV{EMSCRIPTEN}")

#        SET(CMAKE_CXX_FLAGS "-std=c++20" CACHE STRING "" FORCE)
#        SET(CMAKE_C_COMPILER "emcc" CACHE STRING "" FORCE)

#        include(cmake/polly/emscripten-cxx17.cmake)
    ENDIF()
ENDIF()

include(cmake/gate/cmake/HunterGate.cmake)
option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.269.tar.gz"
        SHA1 "64024b7b95b4c86d50ae05b926814448c93a70a0"
        LOCAL
)


project(mobagen)



set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(external)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libs)

IF(EMSCRIPTEN)
    message(STATUS "emscripten build")
    #  SET(CMAKE_CXX_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=2 -s USE_PTHREADS=1 --proxy-to-worker -s FETCH=1")
    SET(CMAKE_CXX_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=2 --proxy-to-worker -s FETCH=1")
    add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/index.html ${CMAKE_BINARY_DIR}/bin/index.html COPYONLY)
ELSE()
    set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/sdl/include)
    set ( SDL2_LIBRARY SDL2 )
ENDIF()


find_library(SDL2 SDL2)
include_directories(${SDL2_INCLUDE_DIR})
#add_library(main SHARED main.cpp)
#target_sources(main PRIVATE main.cpp)
#target_link_libraries(main SDL2 ${SDL2_LIBRARY})

add_executable(editor)
target_sources(editor PUBLIC editor/main.cpp)
target_link_libraries(editor IMGUI ${SDL2_LIBRARIES})
