#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/
cp $DIR/../Engine/example/html/index.html $DIR/../bin-emscripten/bin/
cd $DIR/../bin-emscripten
echo $EMSCRIPTEN
echo `which emcc`
source $DIR/../emsdk-portable/emsdk_env.sh
echo $EMSCRIPTEN
echo `which emcc`
emcc --version
emconfigure cmake -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$EMSCRIPTEN/Modules/cmake ../
emmake make $*
