# Zeppelin Battle Simulation - User Manual

## Video Demonstration

[![Zeppelin Demonstration Video](https://img.youtube.com/vi/7nhuF90u0dk/0.jpg)](https://www.youtube.com/watch?v=7nhuF90u0dk)\
Youtube Link: https://www.youtube.com/watch?v=7nhuF90u0dk

## Setup
- Make sure you have OpenGL installed and setup on your computer before doing any of the steps afterwards. There is a setup guide for Windows attached to the repo main branch named "OpenGL_Setup_Windows.pdf".

- Put the header files into a folder called header in the same directory as the solution.
Depending on your IDE/configuration you may need to put them elsewhere.

- Also include the OBJ and bmp files in the same folder as the solution so that they are accessible by the program.

## Features
- Player and enemy zeppelins with body, engine, and propellors texture mapped. (We did use Modulate Mode)

- Propellors, Body, and engine parts are read from OBJ files.

- FPV camera and world view on separate windows.

- Zeppelins fire lasers. These lasers were made to be as bright as possible.

- Zeppelins have health, if they are shot with the laser for long enough, the zeppelin will be destroyed and respawned. Destruction animation is included.

- Enemy zeppelin moves, tracks, and attacks player.

- There is a texture mapped ground mesh in the world.

- There is a building in the world which is texture mapped. 

- There is collision detection on the blimps for the building.

- When zeppelins are hit, they make a small rotating object which is supposed to represent some of the material heating up and melting away.
