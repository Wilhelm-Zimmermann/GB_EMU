cmake_minimum_required(VERSION 3.10)

project(GB_EMU C)

find_package(SDL2 REQUIRED)

file(GLOB SRCS "src/*.c")

set(ALL_SRCS main.c ${SRCS})

add_executable(main.out ${ALL_SRCS})

target_include_directories(main.out PRIVATE src/headers)
target_link_libraries(main.out PRIVATE SDL2::SDL2main SDL2::SDL2)