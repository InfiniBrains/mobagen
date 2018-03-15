#!/bin/bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-emscripten
mkdir -p $DIR/../bin-emscripten/bin/
cp $DIR/../Engine/midasminer/html/index.html $DIR/../bin-emscripten/bin/
cd $DIR/../bin-emscripten
/usr/bin/cmake -DCMAKE_C_COMPILER=`which emcc` -DCMAKE_CXX_COMPILER=`which em++` -DCMAKE_AR=`which llvm-ar` -DCMAKE_MODULE_PATH=$EMSCRIPTEN/cmake/ -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_STATIC_LIBRARY_SUFFIX=".bc" -DCMAKE_SHARED_LIBRARY_SUFFIX=".bc" -DEMSCRIPTEN=1 -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
/usr/bin/cmake -DCMAKE_C_COMPILER=`which emcc` -DCMAKE_CXX_COMPILER=`which em++` -DCMAKE_AR=`which llvm-ar` -DCMAKE_MODULE_PATH=$EMSCRIPTEN/cmake/ -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_STATIC_LIBRARY_SUFFIX=".bc" -DCMAKE_SHARED_LIBRARY_SUFFIX=".bc" -DEMSCRIPTEN=1 -DCMAKE_BUILD_TYPE=MinSizeRel -DCMAKE_TOOLCHAIN_FILE=$EMSCRIPTEN/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
rm emscripten.zip
zip -r emscripten.zip bin/
make $*
