cmake_minimum_required(VERSION 3.28)

project(mine_field_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/mine_field.h
)

set(SOURCE_FILES
        src/mine_field.c
)

add_library(mine_field_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(mine_field_run ${SOURCE_FILES} src/main.c)
