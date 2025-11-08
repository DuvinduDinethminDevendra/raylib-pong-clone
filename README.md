-----------------------------------

_DISCLAIMER:_

Welcome to **raylib game template**!

This template provides a base structure to start developing a small raylib game in plain C. The repo is also pre-configured with a default `LICENSE` (zlib/libpng) and a `README.md` (this one) to be properly filled by users. Feel free to change the LICENSE as required.

All the sections defined by `$(Data to Fill)` are expected to be edited and filled properly. It's recommended to delete this disclaimer message after editing this `README.md` file.

This template has been created to be used with raylib (www.raylib.com) and it's licensed under an unmodified zlib/libpng license.

_Copyright (c) 2014-2025 Ramon Santamaria ([@raysan5](https://github.com/raysan5))_

-----------------------------------
## Getting Started with this template

#### Linux
When setting up this template on linux for the first time, install the dependencies from this page:
([Working on GNU Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux))

You can use this templates in a few ways: using Visual Studio, using CMake, or make your own build setup. This repository comes with Visual Studio and CMake already set up.

Chose one of the follow setup options that fit in you development environment.

### Visual Studio

- After extracting the zip, the parent folder `raylib-game-template` should exist in the same directory as `raylib` itself.  So, your file structure should look like this:
    - Some parent directory
        - `raylib`
            - the contents of https://github.com/raysan5/raylib
        - `raylib-game-template`
            - this `README.md` and all other raylib-game-template files
- If using Visual Studio, open projects/VS2022/raylib-game-template.sln
- Select on `raylib_game` in the solution explorer, then in the toolbar at the top, click `Project` > `Set as Startup Project`
- Now you're all set up!  Click `Local Windows Debugger` with the green play arrow and the project will run.

### CMake

- Extract the zip of this project
- Type the follow command:

```sh
cmake -S . -B build
```

> if you want to configure your project to build with debug symbols, use the flag `-DCMAKE_BUILD_TYPE=Debug`

- After CMake configures your project, build with:

```sh
cmake --build build
```

- Inside the build folder is another folder (named the same as the project name on CMakeLists.txt) with the executable and resources folder.
- In order for resources to load properly, cd to `src` and run the executable (`../build/${PROJECT_NAME}/${PROJECT_NAME}`) from there.

- cmake will automatically download a current release of raylib but if you want to use your local version you can pass `-DFETCHCONTENT_SOURCE_DIR_RAYLIB=<dir_with_raylib>` 

## My First Pong Game

![My First Pong Game](screenshots/screenshot000.png "My First Pong Game")

### Description

A simple yet classic Pong clone created with raylib in plain C. This is a beginner-friendly implementation of the iconic arcade game, featuring two-player gameplay with responsive paddle controls and realistic ball physics. The game includes a menu system for selecting game modes and a complete game loop with collision detection and ball bounce mechanics.

### Features

 - Two-player gameplay (Player vs Player)
 - Interactive menu system with selection indicator
 - Smooth paddle controls with boundary detection
 - Ball physics with wall and paddle collision
 - Ball reset to center when out of bounds
 - Menu navigation with keyboard and mouse wheel support
 - Coming Soon: Player vs AI mode

### Controls

Keyboard:
 - **W / UP Arrow** - Move paddle up
 - **S / DOWN Arrow** - Move paddle down
 - **ENTER** - Confirm menu selection and start game
 - **ESC** - Close game window

Mouse:
 - **Mouse Wheel** - Navigate menu options

### Screenshots

_TODO: Show your game to the world, animated GIFs recommended!._

### Developers

 - Duvindu Dinethmin Devendra - Game Development & Implementation

### Links

 - itch.io Release: (Coming Soon)
 - Steam Release: (Coming Soon)

### License

This game sources are licensed under an unmodified zlib/libpng license, which is an OSI-certified, BSD-like license that allows static linking with closed source software. Check [LICENSE](LICENSE) for further details.

$(Additional Licenses)

*Copyright (c) $(Year) $(User Name) ($(User Twitter/GitHub Name))*
