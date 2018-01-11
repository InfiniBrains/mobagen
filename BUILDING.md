# Preparation

## OSX
If you don't have XCode:
- Install it [here](https://stackoverflow.com/questions/10335747/how-to-download-xcode-dmg-or-xip-file);
- Install *command line tools* via terminal or follow this [tutorial](https://www.moncefbelyamani.com/how-to-install-xcode-homebrew-git-rvm-ruby-on-mac/):
```bash
xcode-select --install
``` 

OSX already has *git*, but if it doesn't, try install it using *brew*. To install brew, type this in terminal:
```bash
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
brew update
brew install git
```

## Linux
You will need to install *git* and *build-essentials* using your package manager. 

### Ubuntu
``` bash
sudo apt-get install git cmake clang build-essential
```

## Windows
- Installing [MSYS2](http://www.msys2.org/) to install linux tools on Windows terminal;
- Open *MSYS2* terminal and install the i686 or x64 versions of *gcc*(or *clang*), *git*, *make* and *cmake*:
``` bash
pacman -S mingw-w64-x86_64-gcc git mingw-w64-x86_64-make mingw-w64-x86_64-cmake
```
If this fails, try to search the right package name using:
``` bash
pacman -Ss packagename
```
Where *packagename* is the package you want to search for the right name.

# Clonning
In every platform already preparated you will have git installed, so open your terminal and type:
```
git clone --recursive -j8 https://github.com/InfiniBrains/mobagen.git
``` 
This will clone the repo and all submodules.

# Building
If you are platform agnostic, you can use VScode or CLion: 
## Visual Studio Code
- Install [Visual Studio Code](https://code.visualstudio.com/);
- Install all C++ extensions that may help you:
-- C++ Intellisense
-- C++ Lint (this will enforce code style)
-- CMake tools
-- CMake

## CLion 
- [JetBrains CLion](https://www.jetbrains.com/clion/)
- Toolchain will be automatically set on Linux and OSX. But in Windows, if you follow our way of work, point it to: *C:\msys64\mingw64* . 

## Windows
But if you prefer Microsoft development tools:
- [Microsoft Visual Studio Community](https://www.visualstudio.com/downloads/) as IDE and Compiler;
- [CMake addon](https://marketplace.visualstudio.com/items?itemName=vector-of-bool.cmake-tools) as CMake tool helper;
- [JetBrains Resharper C++](https://www.jetbrains.com/resharper-cpp/) to follow our coding style.


## Usage

First clone repo with the following command to download all submodules (which are located in the dependencies folder):
`git clone --recursive git@github.com:Shervanator/Engine.git`

All builds require cmake 3.6.0, so the first step is to download that [here](https://cmake.org/download/)

#### Windows Build

1. Run the cmake gui and point it to this projects folder, configure and then generate a project using whatever toolchain you want. Tested with visual studio 2015
2. Build the project

#### Mac/Linux Build

Run:

```bash
./scripts/cmake-make.sh -j8
```

Then run with:
```bash
./bin/bin/game
```

This will run the first build for you! After that if you need to rebuild do the following:
```bash
cd bin
make -j8
```

#### HTML 5 WebGL engine Build

To build the html5 engine:

First install emscripten:
```bash
brew install emscripten
```

Then build the engine:
```bash
./scripts/cmake-emscripten.sh -j8
```

Then run with:
```bash
cd bin-emscripten/bin

python -m SimpleHTTPServer

open http://localhost:8000/
```

If you make a change you can rebuild with the following command:
```bash
cd bin-emscripten/
make -j8
```

#### Android Build

To build for android do the following:

First download the android ndk and sdk (https://developer.android.com/tools/sdk/ndk/) and (https://developer.android.com/sdk/index.html)

Then add the SDK and NDK to your path:

e.g. (you can add this to your .bash_profile for convenience)

```bash
export ANDROID_SDK=$HOME/Library/Android/sdk/
export ANDROID_NDK=$HOME/workspace/android-ndk-r12b

export PATH="$ANDROID_NDK:$ANDROID_SDK/tools:$ANDROID_SDK/platform-tools:$PATH"
```

Then to build (connect phone in dev mode to computer if you want it to install and run):
```
./scripts/cmake-android.sh -j8
```

To rebuild do the following:
```bash
cd bin-android
make -j8
make android-build android-install android-start
```

If you want to view the backtrace (to see logs and errors do the following):
```bash
cd bin-android
make android-backtrace
```

### To Use:

To use the engine in a game build the engine library and include Engine.h in your game.

View the example in `./src/example/main.cpp`

Or a simple case:

Eg:

```c++
#include "Engine.h"

class CoolGame : public Game
{
public:
  virtual void init(void);
};

void CoolGame::init(void)
{
  auto test_entity = std::make_shared<Entity>();
  test_entity->addComponent<MeshRenderer>(std::make_shared<Mesh>(Asset("../assets/monkey3.obj")), std::make_shared<Texture>(Asset("../assets/t.jpg")));
  addToScene(test_entity);
}

int main(int argc, char **argv){
  CoolGame game;
  Engine gm(&game);

  gm.start();

  return 0;
}
```
