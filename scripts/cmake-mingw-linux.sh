#!/usr/bin/env bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin
cd $DIR/../bin
/usr/bin/cmake -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
/usr/bin/cmake -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DCMAKE_BUILD_TYPE=$BUILD_TYPE ../
make $*
rm -rf $DIR/../win64mingw.zip
zip -r $DIR/../win64mingw.zip bin/*