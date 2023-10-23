cmake_minimum_required(VERSION 3.15)
project(orbitCamera VERSION 0.1.0 LANGUAGES C CXX)

set(PROJECT_INCLUDE_DIR 6502EmulatorRenderer)
set(CMAKE_CXX_STANDARD 20)

set(
    all_src
    animUtils.h
    animUtils.cpp
    BitmapFont.h
    BitmapFont.cpp
    BoundingBox.h

    Controller.h
    Controller.cpp

    ControllerForm.h
    ControllerForm.cpp

    ControllerGL1.h
    ControllerGL1.cpp

    ControllerGL2.h
    ControllerGL2.cpp

    ControllerMain.cpp
    ControllerMain.h

    Controls.h

    DialogWindow.h
    DialogWindow.cpp

    Log.h
    Log.cpp

    Matrices.h
    Matrices.cpp

    ModelGL.h
    ModelGL.cpp

    ObjModel.h    
    ObjModel.cpp

    OrbitCamera.h
    OrbitCamera.cpp

    Quaternion.h

    Tga.h
    Tga.cpp

    Tokenizer.h
    Tokenizer.cpp

    Vectors.h
    Vertices.h

    ViewForm.h
    ViewForm.cpp

    ViewGL.h
    ViewGL.cpp

    Window.h
    Window.cpp

    animUtils.h
    animUtils.cpp

    glExtension.h
    glExtension.cpp

    glext.h
    logResource.h

    procedure.h
    procedure.cpp

    wcharUtil.h
    wcharUtil.cpp

    main.cpp
)



add_executable(${PROJECT_NAME} ${all_src})

include(${PROJECT_SOURCE_DIR}/cmake/glfw.cmake)