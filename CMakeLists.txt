# libmath project with with unit tests (NOT LIBMATH STATIC LIB CMAKE, see libmath subdirectory)

# I am using 3.29 on Ubuntu and 3.27 on Windows, and the most recent
# features I usually use in CMake were added in 3.25, so allow 3.25 and up
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)


# Write directory name into variable to automatically name lib project
get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Create standalone project if current directory is CMake root folder
if (${CMAKE_CURRENT_SOURCE_DIR} PATH_EQUAL ${CMAKE_SOURCE_DIR})

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED True)

    project(${PROJECT_NAME})

# If this script is ran from add_subdirectory()
else()

    # Place targets build from this file in a folder named after this directory
    set(CMAKE_FOLDER ${PROJECT_NAME})

endif()

# Build libmath static lib
add_subdirectory(mathlib)
