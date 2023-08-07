get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(example ${CURRENT_DIR_NAME})
add_demo(${example} main.cpp)
