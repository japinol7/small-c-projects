cmake_minimum_required(VERSION 3.28)

project(leap_year_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/leap_year.h
)

set(SOURCE_FILES
        src/leap_year.c
)

add_library(leap_year_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(leap_year_run ${SOURCE_FILES} src/main.c)
