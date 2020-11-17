# Game of Life
my take on Conway's Game of Life.
Window and grid system creation edited from from: https://github.com/catsocks/sdl-grid

# Controls
Click to select/unselect
Space to start simulation and pause / unpause when running
ESC to stop simulation

# Building

## Windows

```
cd <path to SDL2_template>

md build
cd build
md win32
cd win32
cmake ..\..\

```


## Linux

```
cd <path to SDL2_template>

md build
cd build
md linux
cd linux
cmake ..\..\
make

```


# License
[MIT License](LICENSE)