cmake_minimum_required(VERSION 3.14)
project(chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(chess main.cpp uct_search.cpp uct_search.h uct_node.cpp uct_node.h)