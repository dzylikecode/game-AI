cmake_minimum_required(VERSION 3.15)

project(framework)

set(OUTPUT_NAME "test")

aux_source_directory(./src SRC_LIST)
include_directories(./include)


add_executable(${OUTPUT_NAME} ${SRC_LIST})



# find_package(Bullet REQUIRED)
# find_package(FreeImage REQUIRED)
# find_package(Freetype REQUIRED)
# find_package(ogg REQUIRED)
# find_package(OpenJPEG REQUIRED)
# find_package(PNG REQUIRED)
# find_package(LibRaw REQUIRED)
# find_package(TIFF REQUIRED)
# find_package(Vorbis REQUIRED)
# find_package(Lua REQUIRED)
# find_package(OIS REQUIRED) # can't find FindOIS.cmake
# The CONFIG flag makes sure you get OGRE instead of OGRE-next
# find_package(OGRE REQUIRED COMPONENTS Bites RTShaderSystem CONFIG)
# this also sets the includes and pulls third party dependencies
# target_link_libraries(${OUTPUT_NAME} OgreBites OgreRTShaderSystem)
# find_package(OpenEXR REQUIRED)
# find_package(OpenSteer REQUIRED) # can't find it
# find_package(Recast REQUIRED) # can't find FindRecast.cmake
# find_package(ZLIB REQUIRED)
# find_package(unofficial-zziplib CONFIG REQUIRED)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${OUTPUT_NAME}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

# [CMake Managing Resources | Jeremi Mucha](https://jeremimucha.com/2021/05/cmake-managing-resources/)
# [CMake: adding custom resources to build directory - Stack Overflow](https://stackoverflow.com/questions/17018477/cmake-adding-custom-resources-to-build-directory)
# 
set(RESOURCE_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources)
add_custom_command(
    TARGET ${OUTPUT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${RESOURCE_FILES}
    ${CMAKE_CURRENT_BINARY_DIR}/resources)