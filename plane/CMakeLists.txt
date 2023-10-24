cmake_minimum_required(VERSION 3.15)
project(plane VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(
    all_src
    Cylinder.h
    Cylinder.cpp

    Line.h
    Line.cpp

    Matrices.h
    Matrices.cpp

    Plane.h
    Plane.cpp

    Vectors.h
    main.cpp
)



add_executable(${PROJECT_NAME} ${all_src})

include(${PROJECT_SOURCE_DIR}/cmake/glfw.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/boost.cmake)