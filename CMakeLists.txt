cmake_minimum_required(VERSION 3.15)
project(b64u-fast)

set(CMAKE_CXX_STANDARD 11)

add_executable(node_binding src/binding.cpp src/base64.h)

include_directories(C:/Zytekaron/node_modules/node-addon-api)
