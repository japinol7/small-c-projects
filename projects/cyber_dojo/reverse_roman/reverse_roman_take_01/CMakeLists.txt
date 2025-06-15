cmake_minimum_required(VERSION 3.28)

project(reverse_roman_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/reverse_roman.h
)

set(SOURCE_FILES
        src/reverse_roman.c
)

add_library(reverse_roman_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(reverse_roman_run ${SOURCE_FILES} src/main.c)
