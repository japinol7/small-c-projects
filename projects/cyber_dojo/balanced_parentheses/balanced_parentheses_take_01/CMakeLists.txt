cmake_minimum_required(VERSION 3.28)

project(balanced_parentheses_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/balanced_parentheses.h
)

set(SOURCE_FILES
        src/balanced_parentheses.c
)

add_library(balanced_parentheses_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(balanced_parentheses_run ${SOURCE_FILES} src/main.c)
