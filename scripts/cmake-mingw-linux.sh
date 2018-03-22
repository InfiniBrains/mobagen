#!/usr/bin/env bash

set -e

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin
cd $DIR/../bin
/usr/bin/cmake -DMINGW=ON -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=`which x86_64-w64-mingw32-windres` -DDLLTOOL=`which x86_64-w64-mingw32-dlltool` -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF ../
/usr/bin/cmake -DMINGW=ON -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=`which x86_64-w64-mingw32-windres` -DDLLTOOL=`which x86_64-w64-mingw32-dlltool` -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF ../
make $*
rm -rf $DIR/../win64mingw.zip
zip -r $DIR/../win64mingw.zip bin/*