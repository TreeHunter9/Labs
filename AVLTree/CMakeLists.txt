cmake_minimum_required(VERSION 3.23)
project(AVLTree)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AVLTree src/main.cpp src/avl_tree.h)
