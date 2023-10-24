# Ref Link Solution: https://stackoverflow.com/questions/30004850/cmake-does-not-find-opencv-libraries
# Searching for OpenCV
find_package(OpenCV REQUIRED)


if(APPLE)
    # This is making sure that opencv on mac has been found!
    if(OpenCV_FOUND)
        # message("NOT CMAKE MESSAGE ==> OPENCV HAS BEEN NOTICED AND FOUNDDD!\n")
        # Additional Include Directories
        include_directories(${OpenCV_INCLUDE_DIRS})

        # Additional Library Directories
        link_directories(${OpenCV_LIB_DIR})
        
    else()
        message("${Red}Opencv is not found on mac!")
        message("${Red}
            Make sure you installed opencv correctly!
            - Check homebrew
            - Check if opencv is installed correctly with homebrew.
        ")
    endif()
endif(APPLE)

target_link_libraries(
    ${PROJECT_NAME}
    ${OpenCV_LIBS}
)