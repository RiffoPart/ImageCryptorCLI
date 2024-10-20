cmake_minimum_required(VERSION 3.5)

set("OpenCV_DIR" "/usr/share/opencv4")
set(CXX_STANDARD 17)

option(SHARED_LIB "Compile as SHARED library" ON)

project(ImCrypto)

set(SRC
./src/imcrypto.cpp
)

set(HDR
./include/imcrypto.hpp
)

find_package(OpenCV REQUIRED)

if (SHARED_LIB)
    add_library(ImCrypto SHARED ${SRC})
else()
    add_library(ImCrypto STATIC ${SRC})
endif()

target_link_libraries(ImCrypto ${OpenCV_LIBS})
