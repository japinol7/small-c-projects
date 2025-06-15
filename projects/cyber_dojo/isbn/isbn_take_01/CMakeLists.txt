cmake_minimum_required(VERSION 3.28)

project(isbn_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/isbn.h
)

set(SOURCE_FILES
        src/isbn.c
)

add_library(isbn_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(isbn_run ${SOURCE_FILES} src/main.c)
