cmake_minimum_required(VERSION 3.11)
project(RemoteManagement VERSION 0.0.1)

include(CMake/cmrc-2.0.1/CMakeRC.cmake)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/RemoteManagement/Server)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/RemoteManagement/Client)
