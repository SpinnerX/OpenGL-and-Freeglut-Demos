# Ref Link: https://stackoverflow.com/questions/49082471/linking-assimp-library-with-find-package
# Ref Link with the Solution: https://stackoverflow.com/questions/73991892/what-is-the-best-way-to-add-assimp-to-a-cmake-project
# Ref Link for searching file exists: https://stackoverflow.com/questions/13067401/cmake-check-that-a-local-file-exists
# Ref Link for getting colorized cmake message: https://stackoverflow.com/questions/18968979/how-to-make-colorized-message-with-cmake


# This turns off deprecation warnings (although we might want this on, but just for this lib no)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

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

# Modifying the message()
function(message)
    list(GET ARGV 0 MessageType)
    if(MessageType STREQUAL FATAL_ERROR OR MessageType STREQUAL SEND_ERROR)
        list(REMOVE_AT ARGV 0)
        _message(${MessageType} "${Red}${ARGV}${ColourReset}")
    elseif(MessageType STREQUAL WARNING)
        list(REMOVE_AT ARGV 0)
        _message(${MessageType} "${Yellow}${ARGV}${ColourReset}")
    elseif(MessageType STREQUAL AUTHOR_WARNING)
        list(REMOVE_AT ARGV 0)
        _message(${MessageType} "${Cyan}${ARGV}${ColourReset}")
    elseif(MessageType STREQUAL STATUS)
        list(REMOVE_AT ARGV 0)
        _message(${MessageType} "${Green}${ARGV}${ColourReset}")
    else()
        _message("${ARGV}")
    endif()
endfunction()

# include(FetchContent)
# # set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/libs CACHE PATH "Missing description." FORCE)
# FetchContent_Declare(assimp
# GIT_REPOSITORY https://github.com/assimp/assimp.git
# GIT_TAG master)
include(FetchContent)
# set(FETCHCONTENT_BASE_DIR ${PROJECT_SOURCE_DIR}/libs CACHE PATH "Missing description." FORCE)
FetchContent_Declare(assimp
GIT_REPOSITORY https://github.com/assimp/assimp.git
GIT_TAG master)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_INJECT_DEBUG_POSTFIX OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(assimp)

# The filepath should be changed to whatever the assimp include directory is located
set(ASSIMP_INCLUDE_DIR /usr/local/external_libs/assimp/include)

# This is checking if the include directory exists in our system in specific download spot.
# Might need to do another approach for getting the include directory, possibly.
if(NOT EXISTS "${ASSIMP_INCLUDE_DIR}")
    # message("${Red} \n\nassimp.cmake ERROR MESSAGE HERE ==> located in assimp.cmake because filepath: \"${ASSIMP_INCLUDE_DIR}\" does not exist")
    # message("${Red}assimp.cmake ERROR MESSAGE ==> This error is appearing is because you dont have this anywhere on your system, or in the assumed directory for ASSIMP_INCLUDE_DIR\n\n\n")
    message(SEND_ERROR "\n\nassimp.cmake ERROR MESSAGE HERE ==> located in assimp.cmake because filepath: \"${ASSIMP_INCLUDE_DIR}\" does not exist")
    message(SEND_ERROR "assimp.cmake ERROR MESSAGE ==> This error is appearing is because you dont have this anywhere on your system, or in the assumed directory for ASSIMP_INCLUDE_DIR\n\n\n")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${ASSIMP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} assimp)