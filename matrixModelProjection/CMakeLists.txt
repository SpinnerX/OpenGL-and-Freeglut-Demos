cmake_minimum_required(VERSION 3.15)
project(matrixModelProjection VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

set(
    all_src
    Controller.h
    Controller.cpp

    ControllerFormGL.cpp
    ControllerFormGL.h

    ControllerGL.cpp
    ControllerGL.h

    ControllerMain.cpp
    ControllerMain.h
    Controls.h

    Controls.h

    DialogWindow.cpp
    DialogWindow.h

    Log.cpp
    Log.h

    Matrices.cpp
    Matrices.h

    ModelGL.cpp
    ModelGL.h
    Sphere.cpp
    glExtension.h
     procedure.cpp
    ControllerGL.h
    Sphere.h
    glext.h
    procedure.h
    ControllerMain.cpp
    Vectors.h
    resource.h
    ControllerMain.h
    ViewFormGL.cpp
    Controls.h
    ViewFormGL.h
    DialogWindow.cpp
    ViewGL.cpp
    logResource.h
    wcharUtil.cpp
    DialogWindow.h
    ViewGL.h
    main.cpp
    wcharUtil.h
    Log.cpp
    Window.cpp 

    main.cpp
)



add_executable(${PROJECT_NAME} ${all_src})

include(${PROJECT_SOURCE_DIR}/cmake/glfw.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/boost.cmake)