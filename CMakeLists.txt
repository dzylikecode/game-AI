cmake_minimum_required(VERSION 3.7)
project(game)

########################################################################################################################
# util functions

function(add_demo example files)
    add_executable(${example} ${files})
    # link project
    target_link_libraries(${example} PRIVATE core)

    if (MY_OGRE_CONFIG_DIR)
        target_compile_definitions(${example} PRIVATE MY_OGRE_CONFIG_DIR="${PROJECT_SOURCE_DIR}/${MY_OGRE_CONFIG_DIR}")
    endif()

endfunction()

function(add_test example files)
    add_executable(${example} ${files})
    # link project
    # target_link_libraries(${example} PRIVATE core)


    find_package(OGRE CONFIG REQUIRED)
    target_link_libraries(${example} PRIVATE OgreMain OgreBites Codec_STBI OgrePaging)

    # Or use the header-only version
    find_package(spdlog CONFIG REQUIRED)
    target_link_libraries(${example} PRIVATE spdlog::spdlog_header_only)

    find_package(Lua REQUIRED)
    target_include_directories(${example} PRIVATE ${LUA_INCLUDE_DIR})
    target_link_libraries(${example} PRIVATE ${LUA_LIBRARIES})

    if (MY_OGRE_CONFIG_DIR)
        target_compile_definitions(${example} PRIVATE MY_OGRE_CONFIG_DIR="${PROJECT_SOURCE_DIR}/${MY_OGRE_CONFIG_DIR}")
    endif()

endfunction()

########################################################################################################################
# make project to library named `core`

set(CORE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CORE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# include_directories(${CORE_INCLUDE_DIR})

# file(GLOB_RECURSE CORE_SOURCE_FILES ${CORE_SOURCE_DIR}/*.cpp ${CORE_SOURCE_DIR}/*.c ${CORE_SOURCE_DIR}/*.h ${CORE_SOURCE_DIR}/*.hpp)
# add_library(core STATIC ${CORE_SOURCE_FILES})

# find_package(OGRE CONFIG REQUIRED)
# target_link_libraries(core PRIVATE OgreMain OgreBites Codec_STBI OgrePaging)

# # Or use the header-only version
# find_package(spdlog CONFIG REQUIRED)
# target_link_libraries(core PRIVATE spdlog::spdlog_header_only)

# find_package(Lua REQUIRED)
# target_include_directories(core PRIVATE ${LUA_INCLUDE_DIR})
# target_link_libraries(core PRIVATE ${LUA_LIBRARIES})

########################################################################################################################
# demo

# add_subdirectory(demo)
add_subdirectory(test)