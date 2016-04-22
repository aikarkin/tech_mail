cmake_minimum_required(VERSION 3.5)
project(MailAlgo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -std=c++11")

set(SOURCE_FILES Module2/3_1.cpp)
add_executable(MailAlgo ${SOURCE_FILES})