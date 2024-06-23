cmake_minimum_required(VERSION 3.22)
project(codeforces LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(-DDEBUG)
endif(CMAKE_BUILD_TYPE STREQUAL "Debug")

subdirs(contest)
subdirs(playground)