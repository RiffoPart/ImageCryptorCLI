cmake_minimum_required(VERSION 3.5)

set("OpenCV_DIR" "/usr/share/opencv4")
set(CXX_STANDARD 17)

project(ImCrypto)

set(SRC
./src/imcrypto.cpp
)

set(HDR
./include/imcrypto.hpp
)

find_package(OpenCV REQUIRED)


add_library(ImCrypto SHARED ${SRC})
target_link_libraries(ImCrypto ${OpenCV_LIBS})
