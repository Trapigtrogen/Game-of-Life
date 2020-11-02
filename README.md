# SDL2_template

Template for SDL using CMake.

# Building

## Windows

Use CMake-gui 

  * Where is the source code: "path to SDL2_template"
  * Where to build the binaries: "path to SDL2_template"\build\win32

or type following in the Command Prompt:

```
cd <path to SDL2_template>

md build
cd build
md win32
cd win32
cmake ..\..\

```


## Linux

Type following in the terminal:

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