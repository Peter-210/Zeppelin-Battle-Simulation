# Zeppelin Battle Simulation

## Video Demonstration

[![Zeppelin Demonstration Video](https://img.youtube.com/vi/p9G6Ar1LSQ0/0.jpg)](https://www.youtube.com/watch?v=p9G6Ar1LSQ0)\
Youtube Link: https://www.youtube.com/watch?v=p9G6Ar1LSQ0


## Features

- Player and enemy zeppelins with body, engine, and propellors texture mapped. (Used Modulate Mode)

- Propellors, Body, and engine parts are read from OBJ files.

- FPV camera and world view on separate windows.

- Zeppelins fire lasers. These lasers were made to be as bright as possible.

- Zeppelins have health, if they are shot with the laser for long enough, the zeppelin will be destroyed and respawned. Destruction animation is included.

- Enemy zeppelin moves, tracks, and attacks player.

- There is a texture mapped ground mesh in the world.

- There is a building in the world which is texture mapped. 

- There is collision detection on the blimps for the building.

- When zeppelins are hit, they make a small rotating object which is supposed to represent some of the material heating up and melting away.


## How To Play

| Keybind | Description |
| --- | --- |
| W | Move Forwards |
| S | Move Backwards |
| UP ARROW | Fly Up |
| DOWN ARROW | Descend Down |
| LEFT ARROW | Turn Left |
| RIGHT ARROW | Turn Right |
| SPACEBAR | Toggle Laser |

## Option 1: Setup - Using CMake

Run the following commands:
```
cmake --workflow default
.\build\main.exe
```

## Option 2: Setup - Using Visual Studio

1. Use Visual Studio 2017 if possible

2. On Solution Explorer, right click Source Files -> Add --> Existing Item (Select all src/*.cpp files)

3. On Solution Explorer, right click Header Files -> Add --> Existing Item (Select all header/*.h files)

4. In Blimp.cpp and ObjectTextureHandler.cpp, change "assets/" to "../assets/"

5. Open Main.cpp and go to properties: "Project -> Properties"

6. Change Configuration to "All Configurations" and Platform to "All Platforms" (Located at the top of window)

7. In properties, go to "Configuration Properties -> VC++ Directories -> Include Directories" and add the following to the first top textbox.
```
$(SolutionDir)Dependencies\freeglut\include
```
```
$(SolutionDir)Dependencies\GLEW\include
```

5. In properties, go to "Configuration Properties -> VC++ Directories -> Library Directories" and add the following to the first top textbox.
```
$(SolutionDir)Dependencies\freeglut\lib\$(platform)
```
```
$(SolutionDir)Dependencies\GLEW\lib\Release\$(platform)
```

6. In properties, go to "Configuration Properties -> C/C++ -> Language -> C++ Language Standard" and change to ISO C++17 Standard (/std:c++17) 

5. In properties, go to "Configuration Properties -> C/C++ -> Preprocessor -> Preprocessor Definitions" and add the following to the first top textbox.
```
GLEW_STATIC
```

5. In properties, go to "Configuration Properties -> Linker -> Input -> Additional Dependencies" and add the following to the first top textbox.
```
freeglut.lib
```
```
glew32s.lib
```

5. In properties, go to "Configuration Properties -> Build Events -> Post-Build Event -> Command Line" and add the following to the first top textbox.
```
copy "$(SolutionDir)Dependencies\freeglut\bin\$(Platform)\freeglut.dll" "$(OutDir)"
```
