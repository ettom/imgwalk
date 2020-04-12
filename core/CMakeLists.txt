set(SUBPROJECT_NAME ${PROJECT_NAME}Core)
file(GLOB_RECURSE SRC_LIST *.cpp *.h)
add_library(${SUBPROJECT_NAME} ${SRC_LIST})
target_include_directories(${SUBPROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${SUBPROJECT_NAME}
    exif)

target_compile_options(
    ${SUBPROJECT_NAME}
    PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion
    -Wsign-conversion -Wshadow)
