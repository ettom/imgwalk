set(SUBPROJECT_NAME ${PROJECT_NAME}Test)
file(GLOB_RECURSE SRC_LIST *)
add_executable(${SUBPROJECT_NAME} ${SRC_LIST})

target_link_libraries(${SUBPROJECT_NAME}
    PRIVATE
    ${PROJECT_NAME}Core)

target_include_directories(${SUBPROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR})

# remove -O3 and -DNDEBUG for release builds
set(CMAKE_CXX_FLAGS_RELEASE "")

target_compile_options(
    ${SUBPROJECT_NAME}
    PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion
    -Wsign-conversion -Wshadow)

