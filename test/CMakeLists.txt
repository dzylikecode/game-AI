file(GLOB SUB_DIRS LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(subdir ${SUB_DIRS})
    if(IS_DIRECTORY ${subdir})
        add_subdirectory(${subdir})
    endif()
endforeach()