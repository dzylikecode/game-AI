cmake_minimum_required(VERSION 3.15)

project(gameAI)

# set(CMAKE_CXX_STANDARD 17)

# # If no installation prefix is given manually, install locally.
# if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#     set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE STRING
#             "The install location"
#             FORCE)
# endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

# set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")

# set debug or release
set(BUILD_TYPE "Debug")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# add_subdirectory(lib)
add_subdirectory(core)
add_subdirectory(test)