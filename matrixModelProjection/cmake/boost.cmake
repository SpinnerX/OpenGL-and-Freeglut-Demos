find_package(Boost 1.40 REQUIRED regex date_time system filesystem thread graph)
include_directories(${BOOST_INCLUDE_DIRS})
message("boost lib: ${Boost_LIBRARIES}")
message("boost inc:${Boost_INCLUDE_DIR}")


if(APPLE)
    target_link_libraries(${PROJECT_NAME} ${BOOST_LIBRARIES})
endif(APPLE)