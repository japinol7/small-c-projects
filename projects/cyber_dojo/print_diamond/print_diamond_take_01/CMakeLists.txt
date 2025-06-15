cmake_minimum_required(VERSION 3.28)

project(print_diamond_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/print_diamond.h
)

set(SOURCE_FILES
        src/print_diamond.c
)

add_library(print_diamond_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(print_diamond_run ${SOURCE_FILES} src/main.c)
