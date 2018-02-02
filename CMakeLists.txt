cmake_minimum_required(VERSION 3.7.2)
project(sdlplay)

find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
add_executable(sdlplay sdl2play.cpp)
target_link_libraries(sdlplay ${SDL2_LIBRARIES})
target_link_libraries(sdlplay ${CMAKE_THREAD_LIBS_INIT})

