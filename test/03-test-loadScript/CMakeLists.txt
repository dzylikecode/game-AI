get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
set(example ${CURRENT_DIR_NAME})
add_test(${example} main.cpp)
