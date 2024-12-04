cmake_minimum_required(VERSION 3.29)
project(main C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(SDL2_PATH "../SDL2-2.30.9/x86_64-w64-mingw32")
set(IMAGE_PATH "..SDL2_image-2.8.2/x86_64-w64-mingw32")

find_package(SDL2_image REQUIRED)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

add_executable(main main.c)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY})
target_link_libraries(${PROJECT_NAME} ${SDL2_IMAGE_LIBRARY})
