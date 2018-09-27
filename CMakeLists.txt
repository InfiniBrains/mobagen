cmake_minimum_required(VERSION 2.8)

find_program(LSB_RELEASE_EXEC lsb_release) 
if(LSB_RELEASE_EXEC) 
  execute_process(COMMAND ${LSB_RELEASE_EXEC} -is 
    OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT 
    OUTPUT_STRIP_TRAILING_WHITESPACE 
  ) 
  IF(LSB_RELEASE_ID_SHORT) 
    message(STATUS "ubuntu detected") 
 
  ENDIF() 
ENDIF() 

find_program (perl_path NAMES perl perl.exe) 
IF (NOT perl_path) 
  message(FATAL_ERROR "You must install PERL and add it to PATH") 
ELSE() 
    message(STATUS "Perl was found in PATH: ${perl_path}") 
ENDIF() 
  
IF (NOT EMSCRIPTEN)
  set (HUNTER_SKIP_LOCK ON CACHE BOOL "HUNTER_SKIP_LOCK")
  include(cmake/HunterGate.cmake)
  option(HUNTER_STATUS_DEBUG "Hunter debug info" ON)
  HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.25.tar.gz"
    SHA1 "cb75cce9a3a8d552e70e7118f3203eb4ac05c201"
  )
ENDIF()

project (Engine)

IF (NOT EMSCRIPTEN)
  hunter_add_package(cpr)
  find_package(cpr CONFIG REQUIRED)
  set(LIBC ON CACHE BOOL "LIBC")
ENDIF()

set(NOMINMAX ON CACHE BOOL "workaround for minmax problem with windows.h")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE STRING "Root dir")

set(CP_CMAKE_DIR ${PROJECT_SOURCE_DIR}/cmake)
include(cotire)
include(${CP_CMAKE_DIR}/macros.cmake)

set(BUILD_STATIC_LIBS TRUE)
set(BUILD_SHARED_LIBS FALSE)

IF (ANDROID)
  include(${CP_CMAKE_DIR}/android.cmake)
ENDIF () 

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/lib)

add_definitions(-DGLEW_STATIC)
add_definitions(-UGLEW_BUILD)

add_subdirectory(dependencies)

#add_definitions ( -DOPENSSL_ROOT_DIR ${CMAKE_SOURCE_DIR}/dependencies/openssl/)
#OPENSSL_CRYPTO_LIBRARY
#OPENSSL_SSL_LIBRARY
#add_definitions ( -DOPENSSL_LIBRARIES "${CMAKE_BINARY_DIR}/lib/")

#find_package(OpenSSL)

include(${CMAKE_CURRENT_BINARY_DIR}/dependencies/gdcm/GDCMConfig.cmake )

SET(GDCM_LIBRARIES
        gdcmCommon
        gdcmDICT
        gdcmDSED
        gdcmIOD
        gdcmMSFF
        gdcmMEXD
        gdcmjpeg8
        gdcmjpeg12
        gdcmjpeg16
        gdcmexpat
        gdcmopenjp2
        gdcmcharls
        gdcmzlib
        #gdcmuuid
        socketxx
        )

set ( SDL2_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL/include )
set ( SDL2_LIBRARY SDL2-static )

#set ( GLEW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew/include )
#set ( GLEW_LIBRARIES libglew_static )

set ( ASSIMP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/assimp/include )
set ( ASSIMP_LIBRARY assimp )

set ( GLM_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/ )

set ( WHEREAMI_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/whereami/src/ )
set ( WHEREAMI_LIBRARY whereami )

set ( IMGUI_INCLUDE_DIRS
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/addons
  ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/addons/imguifilesystem)

set ( IMGUI_LIBRARY imgui )

IF (EMSCRIPTEN)
  #SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/Engine/example/assets/ -s DEMANGLE_SUPPORT=1 -s ASSERTIONS=2 -s TOTAL_MEMORY=536870912 -s USE_SDL=2 -std=c++14 -Oz")
  SET(CMAKE_CXX_FLAGS "--closure 1 --preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/ -s TOTAL_MEMORY=536870912 -s USE_SDL=2 -std=c++14 -Oz")
  add_definitions(-DASSET_DIR="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

  set(ENGINE_LIBS
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
    ${GDCM_LIBRARIES}
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
    ${GDCM_INCLUDE_DIRS}
  )

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/index.html ${CMAKE_BINARY_DIR}/bin/index.html COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/midasminer.html ${CMAKE_BINARY_DIR}/bin/midasminer.html COPYONLY)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/html/doceditor.html ${CMAKE_BINARY_DIR}/bin/doceditor.html COPYONLY)

ELSEIF (ANDROID)
  add_definitions( -DGLES2=1 )
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

  set(ENGINE_LIBS
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    ${IMGUI_LIBRARY}
    ${GDCM_LIBRARIES}
  )

  set(ENGINE_INCLUDES
    ${SDL2_INCLUDE_DIR}
    ${GLM_INCLUDE_DIRS}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
    ${GDCM_INCLUDE_DIRS}
  )
ELSE ()
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++14 -fPIC")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -std=c++14 -fPIC")
  find_package(OpenGL REQUIRED)

  set(ENGINE_LIBS
    ${OPENGL_LIBRARY}
    ${SDL2_LIBRARY}
    ${ASSIMP_LIBRARY}
    #${GLEW_LIBRARIES}
    ${WHEREAMI_LIBRARY}
    ${IMGUI_LIBRARY}
    ${GDCM_LIBRARIES}
#    ${OPENSSL_LIBRARIES}
    cpr::cpr
  )

  set(ENGINE_INCLUDES
    ${GLM_INCLUDE_DIRS}
    ${SDL2_INCLUDE_DIR}
    ${ASSIMP_INCLUDE_DIR}
    ${CMAKE_BINARY_DIR}/dependencies/assimp/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/stb
    ${WHEREAMI_INCLUDE_DIRS}
    ${IMGUI_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/engine/
    ${GDCM_INCLUDE_DIRS}
#    ${OPENSSL_INCLUDE_DIRS}
#    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/mingw-std-threads
  )
ENDIF ()

include_directories(${ENGINE_INCLUDES})

add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/engine )
add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/examples )

IF (NOT ANDROID)
  option(BUILD_TESTS "BUILD TESTS" ON)
  IF (BUILD_TESTS)
    add_subdirectory( ${CMAKE_CURRENT_SOURCE_DIR}/tests )
  ENDIF ()
ENDIF ()

#projects
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT midasminer)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT doceditor)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tests)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT uploader)

