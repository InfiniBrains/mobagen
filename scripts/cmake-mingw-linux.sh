#!/usr/bin/env bash

set -e

export CC=/usr/bin/x86_64-w64-mingw32-gcc-win32
export CXX=/usr/bin/x86_64-w64-mingw32-g++-win32
export CPP=/usr/bin/x86_64-w64-mingw32-cpp-win32
export CXXCPP=/usr/bin/x86_64-w64-mingw32-cpp-win32
export AR=/usr/bin/x86_64-w64-mingw32-gcc-ar-win32
export NM=/usr/bin/x86_64-w64-mingw32-gcc-nm-win32
export RANLIB=/usr/bin/x86_64-w64-mingw32-gcc-ranlib-win32
export DLLTOOL=/usr/bin/x86_64-w64-mingw32-dlltool
export DLLWRAP=/usr/bin/x86_64-w64-mingw32-dllwrap
export LD=/usr/bin/x86_64-w64-mingw32-ld
export OBJCOPY=/usr/bin/x86_64-w64-mingw32-objcopy
export OBJDUMP=/usr/bin/x86_64-w64-mingw32-objdump
export PKGCONFIG=/usr/bin/x86_64-w64-mingw32-pkg-config

BUILD_TYPE=${BUILD_TYPE:-Release}
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
mkdir -p $DIR/../bin-mingw
cd $DIR/../bin-mingw
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DMINGW=ON -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=`which x86_64-w64-mingw32-windres` -DDLLTOOL=`which x86_64-w64-mingw32-dlltool` -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS=" -static -static-libgcc -static-libstdc++" ../
cmake -DCMAKE_BUILD_TYPE=MinSizeRel -DMINGW=ON -DCMAKE_C_COMPILER=`which x86_64-w64-mingw32-gcc` -DCMAKE_CXX_COMPILER=`which x86_64-w64-mingw32-g++` -DCMAKE_AR=`which x86_64-w64-mingw32-ar` -DGDCM_BUILD_DOCBOOK_MANPAGES=0 -DGDCM_DOCUMENTATION=0 -DBUILD_DOC=0 -DTEST_BIG_ENDIAN=0 -DOPJ_BIG_ENDIAN=0 -DBUILD_SHARED_LIBS=OFF -DBUILD_CLAR=OFF -DTHREADSAFE=ON -DCMAKE_SYSTEM_NAME=Windows -DCMAKE_RC_COMPILER=`which x86_64-w64-mingw32-windres` -DDLLTOOL=`which x86_64-w64-mingw32-dlltool` -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY -DDIRECTX=0 -DVIDEO_OPENGL=1 -DVIDEO_OPENGLES=0 -DBUILD_SHARED_LIBS=OFF -DCMAKE_EXE_LINKER_FLAGS=" -static -static-libgcc -static-libstdc++" ../
make $*
make $*
rm -rf $DIR/../win64mingw.zip
zip -r $DIR/../win64mingw.zip bin/*