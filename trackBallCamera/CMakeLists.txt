cmake_minimum_required(VERSION 3.15)
project(trackBallCamera VERSION 0.1.0 LANGUAGES C CXX)

set(PROJECT_INCLUDE_DIR 6502EmulatorRenderer)
set(CMAKE_CXX_STANDARD 20)

set(
    all_src
    animUtils.h
    animUtils.cpp

    Matrices.h
    Matrices.cpp

    Primitives.h
    Primitives.cpp

    Quaternion.h
    
    Trackball.h
    Trackball.cpp

    Vectors.h

    main.cpp
)



add_executable(${PROJECT_NAME} ${all_src})

include(${PROJECT_SOURCE_DIR}/cmake/glfw.cmake)