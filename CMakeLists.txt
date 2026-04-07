cmake_minimum_required(VERSION 3.20)
project(ProjetAvalanche LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

set(PLATFORM "SDL" CACHE STRING "" FORCE)
set(GRAPHICS "GRAPHICS_API_OPENGL_33" CACHE STRING "" FORCE)
set(raylib_FOUND FALSE CACHE BOOL "" FORCE)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if(NOT raylib_FOUND)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_MakeAvailable(raylib)
endif()

add_subdirectory(src)
add_subdirectory(tests)
