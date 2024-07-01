# math static lib CMake

# Do not attempt to compile with an older version of CMake
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# Name static lib after current directory
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Create standalone project if current directory is not a CMake subdir
if(${CMAKE_CURRENT_SOURCE_DIR} PATH_EQUAL ${CMAKE_SOURCE_DIR})

	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_STANDARD_REQUIRED True)

	project(${TARGET_NAME} LANGUAGES CXX)

endif()


# Gather project files

# Header files
file(GLOB_RECURSE TARGET_HEADER_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
)

set(GENERIC_HEADERS ${TARGET_HEADER_FILES})

list(FILTER GENERIC_HEADERS INCLUDE REGEX "Generic.hpp$")
list(FILTER TARGET_HEADER_FILES EXCLUDE REGEX "Generic.hpp$")


source_group("Generic" FILES ${GENERIC_HEADERS})

# Source files
file(GLOB_RECURSE TARGET_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++
)

# Extras/documentation
file(GLOB_RECURSE TARGET_DOC_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/*.txt
	${CMAKE_CURRENT_SOURCE_DIR}/*.md
)

# Put target all files together in a variable
set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES} ${TARGET_DOC_FILES} ${GENERIC_HEADERS})

# Generate Visual Studio filter without the extra "math" folder in Header
source_group("Source" ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_SOURCE_FILES})
source_group("Header" ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_HEADER_FILES})

# Create variable for header directory (will still require to put math/)
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Header)


# Create static lib
add_library(${TARGET_NAME} STATIC)

# Add sources to lib
target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

# Set include directory
target_include_directories(${TARGET_NAME}
	PUBLIC ${TARGET_INCLUDE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/ion
)

# Raise warning level in MSVC and g++
if(MSVC)

	# Compile with all warnings and optimizations available
	target_compile_options(${TARGET_NAME} PRIVATE /W4 /WX)

elseif(LINUX)

    # TODO remove debug symbols
    target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wshadow -Wpedantic -Werror -g)

endif()


# Make library available to other projects (as long as they are built after this)
set(MATHLIB_LIB ${TARGET_NAME} PARENT_SCOPE)

