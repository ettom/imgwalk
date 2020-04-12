cmake_minimum_required(VERSION 3.6)
get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -Wall -Wextra -Wpedantic -Wconversion \
    -Wsign-conversion -Wshadow \
    -ggdb \
    -fno-limit-debug-info -fsanitize=undefined \
    -fsanitize=implicit-conversion -fsanitize=integer")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
    -Wall -Wextra -Wpedantic -Wconversion \
    -Wsign-conversion -Wshadow")
endif()

add_subdirectory(test)

add_custom_target(
    test
    COMMAND ${PROJECT_NAME}Test || :
    DEPENDS ${PROJECT_NAME}Core
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR})

add_subdirectory(core)
add_subdirectory(app)
