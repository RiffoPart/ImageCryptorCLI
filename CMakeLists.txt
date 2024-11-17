cmake_minimum_required(VERSION 3.5)

set(MAIN_PROJECT_NAME "imcrypto")
set(CXX_STANDARD 17)

set(BUILD_SHARED_LIB ON)
set(BUILD_STATIC_LIB OFF)

project(${MAIN_PROJECT_NAME})

find_package(Boost COMPONENTS program_options REQUIRED)

add_subdirectory(./lib/imcryptolib)
include_directories(./lib/imcryptolib/include)

add_subdirectory(./lib/lzw)
include_directories(./lib/lzw/include)

set(SRC
    ./src/main.cpp
)

add_executable(${MAIN_PROJECT_NAME} ${SRC})
target_link_libraries(${MAIN_PROJECT_NAME} ImCrypto lzwlib Boost::program_options)