cmake_minimum_required(VERSION 3.2)
set(LIB_PROJECT_NAME "lzwlib")
project(${LIB_PROJECT_NAME})


option(BUILD_STATIC_LIB "Build the static library"      ON)
option(BUILD_SHARED_LIB "Build the shared library"      OFF)

set(SRC
    ./src/lzw.cpp
)

if (BUILD_SHARED_LIB)
    add_library(${LIB_PROJECT_NAME} SHARED ${SRC})
endif(BUILD_SHARED_LIB)

if(BUILD_STATIC_LIB)
    add_library(${LIB_PROJECT_NAME} STATIC ${SRC})
endif(BUILD_STATIC_LIB)