cmake_minimum_required(VERSION 3.15)
project(b64u-fast)

set(CMAKE_CXX_STANDARD 11)

add_executable(b64u_fast src/binding.cpp src/lib/config.h)

include_directories(C:/Zytekaron/node_modules/node-addon-api)