cmake_minimum_required(VERSION 3.28)

project(roman_numerals_full_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/roman_numerals_full.h
)

set(SOURCE_FILES
        src/roman_numerals_full.c
)

add_library(roman_numerals_full_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(roman_numerals_full_run ${SOURCE_FILES} src/main.c)
