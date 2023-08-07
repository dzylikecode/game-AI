cmake_minimum_required(VERSION 3.7)
project(game)

########################################################################################################################
# util functions

function(add_demo example files)
    add_executable(${example} ${files})
    # link project
    target_link_libraries(${example} PRIVATE core)

    find_package(raylib CONFIG REQUIRED)
    target_link_libraries(${example} PRIVATE raylib)
endfunction()

########################################################################################################################
# make project to library named `core`


set(CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(${CORE_INCLUDE_DIR})

file(GLOB_RECURSE CORE_SOURCE_FILES ${CORE_SOURCE_DIR}/*.cpp ${CORE_SOURCE_DIR}/*.c ${CORE_SOURCE_DIR}/*.h ${CORE_SOURCE_DIR}/*.hpp)
add_library(core STATIC ${CORE_SOURCE_FILES})

find_package(raylib CONFIG REQUIRED)
target_link_libraries(core PRIVATE raylib)

########################################################################################################################
# demo

add_subdirectory(demo)