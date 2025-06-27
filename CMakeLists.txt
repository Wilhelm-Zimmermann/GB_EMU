cmake_minimum_required(VERSION 3.10)

project(GB_EMU C)

file(GLOB SRCS "src/*.c")

set(ALL_SRCS main.c ${SRCS})

add_executable(main.out ${ALL_SRCS})