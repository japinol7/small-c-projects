cmake_minimum_required(VERSION 3.28)

project(filename_range_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/filename_range.h
)

set(SOURCE_FILES
        src/filename_range.c
)

add_library(filename_range_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(filename_range_run ${SOURCE_FILES} src/main.c)
