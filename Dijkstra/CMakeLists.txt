cmake_minimum_required(VERSION 3.10.0)
project(Dijkstra VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(Dijkstra src/main.cpp include/graph.h)
include_directories(${PROJECT_SOURCE_DIR}/include/)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
