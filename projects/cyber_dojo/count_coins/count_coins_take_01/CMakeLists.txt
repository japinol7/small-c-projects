cmake_minimum_required(VERSION 3.28)

project(count_coins_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/count_coins.h
)

set(SOURCE_FILES
        src/count_coins.c
)

add_library(count_coins_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(count_coins_run ${SOURCE_FILES} src/main.c)
