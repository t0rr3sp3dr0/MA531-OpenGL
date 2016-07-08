cmake_minimum_required(VERSION 3.5)
project(AVLC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(SOURCE_FILES main.cpp display.cpp display.h shader.cpp shader.h mesh.cpp mesh.h texture.cpp texture.h stb_image.c stb_image.h transformer.h transform.h camera.h)
add_executable(AVLC ${SOURCE_FILES})
target_link_libraries(AVLC GL SDL2 GLEW)