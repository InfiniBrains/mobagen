#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/
cp $DIR/../Engine/example/html/index.html $DIR/../bin-emscripten/bin/
cd $DIR/../bin-emscripten
emconfigure cmake -DEMSCRIPTEN=1 -DCMAKE_C_COMPILER_ENV_VAR=`which emcc` -DCMAKE_CXX_COMPILER_ENV_VAR=`which em++`  -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN/Modules/cmake ../
emmake make $*
