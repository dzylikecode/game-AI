cmake_minimum_required(VERSION 3.15)

project(framework)

set(OUTPUT_NAME "core")

aux_source_directory(./src SRC_LIST)
include_directories(./include)


add_library(${OUTPUT_NAME} STATIC ${SRC_LIST})



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
# find_package(OGRE CONFIG REQUIRED)
# target_link_libraries(${OUTPUT_NAME} PRIVATE OgreMain OgreBites Codec_STBI OgrePaging)
# find_package(OpenEXR REQUIRED)
# find_package(OpenSteer REQUIRED) # can't find it
# find_package(Recast REQUIRED) # can't find FindRecast.cmake
# find_package(ZLIB REQUIRED)
# find_package(unofficial-zziplib CONFIG REQUIRED)




