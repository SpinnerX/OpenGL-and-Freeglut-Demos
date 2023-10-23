cmake_minimum_required(VERSION 3.15)
project(displayList VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(
    all_src
    Timer.cxx
    Timer.h
    main.cpp

    main.cpp
)



add_executable(${PROJECT_NAME} ${all_src})

include(${PROJECT_SOURCE_DIR}/cmake/glfw.cmake)