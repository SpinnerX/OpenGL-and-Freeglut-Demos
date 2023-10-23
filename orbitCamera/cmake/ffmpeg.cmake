# Cmake links: https://github.com/Kitware/VTK/blob/master/CMake/FindPythonModules.cmake

# This is to allow coloring text
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# if(NOT TARGET FFMPEG::avutil)
#   message("${Red}NOT CMAKE ACTUAL MESSAGE ===> FFMPEG HAS NOT BEEN FOUND!\n\n\n")
# endif()

if(__APPLE__)
    #message("${Red}IF-STATEMENT BYPASSED HERE!\n")
    # For ffmpeg
    find_package(PkgConfig REQUIRED)
        pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil
    )

    # Linking ffmpeg LIBAV library
    target_link_libraries(${PROJECT_NAME} PkgConfig::LIBAV)
endif(__APPLE__)