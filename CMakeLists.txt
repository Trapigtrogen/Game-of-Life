# Minimum supported CMake version.
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Name of the project
project(GoL)

set( VIDEO_RPI OFF CACHE BOOL "" FORCE )
set( SDL_STATIC ON CACHE BOOL "" FORCE )
set( SDL_SHARED OFF CACHE BOOL "" FORCE )
# Add SDL2 to build
add_subdirectory("ext/SDL2-2.0.12")

# INC_FILES and SRC_FILES
file(GLOB INC_FILES "include/*.h")
file(GLOB SRC_FILES "src/*.cpp")

# Include dir
include_directories("ext/SDL2-2.0.10/include")

# määritä exe tiedoston käännettävät tiedostot
add_executable(GoL ${SRC_FILES} ${INC_FILES} )

target_link_libraries(GoL SDL2main SDL2-static)

