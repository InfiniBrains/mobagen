cmake_minimum_required(VERSION 3.21.1)

include(cmake/hunter/gate/cmake/HunterGate.cmake)
option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.24.2.tar.gz"
        SHA1 "17fd3b9f0b8c271eac9b71e30a6aa1b9fecab299"
)

project(mobagen)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_C_STANDARD 17)
#set(CMAKE_C_STANDARD_REQUIRED ON)

#CHECK MINGW
IF(NOT DEFINED MINGW)
    SET(MINGW OFF)
ENDIF()

# check if mingw
#IF("${CMAKE_GENERATOR}" MATCHES "(M|m?)in(G|g?)(W|w?)")
#    SET(MINGW ON)
#    MESSAGE(STATUS "MinGW Detected")
#    MESSAGE(STATUS "${CMAKE_GENERATOR}")
#ELSE()
#    SET(MINGW OFF CACHE BOOL "MINGW")
#ENDIF()

# make this only for VS and not WIN32
if(DEFINED WIN32 AND NOT DEFINED MINGW)
    SET(CMAKE_CXX_FLAGS "/w /EHsc")
endif()

# CHECK OR APPLE MACHINE
IF(NOT DEFINED APPLE)
    set(APPLE OFF)
    MESSAGE(STATUS "NOT APPLE MACHINE")
ENDIF()

find_program(LSB_RELEASE_EXEC lsb_release)
if(LSB_RELEASE_EXEC)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -is
            OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            )
    IF(LSB_RELEASE_ID_SHORT)
        message(STATUS "ubuntu detected")
        SET(UBUNTU ON)
    ENDIF()
ENDIF()

# make this more general approach
IF(DEFINED UBUNTU)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
ENDIF()

MESSAGE(STATUS "MSYS=${MSYS}")
MESSAGE(STATUS "CYGWIN=${CYGWIN}")
MESSAGE(STATUS "MINGW=${MINGW}")
MESSAGE(STATUS "WIN32=${WIN32}")
MESSAGE(STATUS "MSVC=${MSVC}")
MESSAGE(STATUS "UBUNTU=${UBUNTU}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libs)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libs/Debug)

#set(DIRECTX OFF CACHE BOOL "use directx")
#set(VIDEO_OPENGL ON CACHE BOOL "use opengl")
#set(VIDEO_OPENGLES OFF CACHE BOOL "use opengles")
#add_definitions(-DGL_GLEXT_PROTOTYPES)

message("CMAKE_SYSTEM_NAME [${CMAKE_SYSTEM_NAME}]")


IF(EMSCRIPTEN)
    message(STATUS "emscripten build")
    #  SET(CMAKE_CXX_FLAGS "--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s ALLOW_MEMORY_GROWTH=1 -s USE_SDL=2 -s DISABLE_EXCEPTION_CATCHING=2 -s USE_PTHREADS=1 --proxy-to-worker -s FETCH=1")
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s WASM=0 -s DISABLE_EXCEPTION_CATCHING=2 --proxy-to-worker -s FETCH=1")
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/")

    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
#    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -s WASM=0 -s USE_SDL=2 -s FULL_ES2=1 -s MAX_WEBGL_VERSION=2 -s USE_GLFW=3 -lgl -lglfw3 -lGLEW")

    MESSAGE(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")

    add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/" -DGLES2)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/index.html ${CMAKE_BINARY_DIR}/bin/index.html COPYONLY)
ELSE()
    set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/SDL/include)
ENDIF()

#SET(CORE_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)

add_subdirectory(external)

add_subdirectory(core)

add_subdirectory(examples)
#add_subdirectory(editor)