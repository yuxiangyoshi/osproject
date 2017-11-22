cmake_minimum_required(VERSION 3.1)

PROJECT(coen283)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost 1.58.0 REQUIRED COMPONENTS system thread regex coroutine)
if(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
endif(Boost_FOUND)

find_package(gflags REQUIRED)

ADD_EXECUTABLE(coroutine main.cc worker.cc)
TARGET_LINK_LIBRARIES(coroutine ${Boost_LIBRARIES} gflags)
