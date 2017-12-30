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
You will need to install *git* and *build-essentials* using your package manager. (TODO: improve this)

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
