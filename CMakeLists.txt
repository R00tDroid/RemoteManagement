cmake_minimum_required(VERSION 3.11)
project(RemoteManagement VERSION 0.0.1)

if (MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

include(CMake/cmrc-2.0.1/CMakeRC.cmake)
include(CMake/CPM.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/RemoteManagement/Server)
