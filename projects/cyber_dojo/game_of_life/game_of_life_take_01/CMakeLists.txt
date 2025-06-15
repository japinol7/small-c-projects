cmake_minimum_required(VERSION 3.28)

project(game_of_life_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/game_of_life.h
)

set(SOURCE_FILES
        src/game_of_life.c
)

add_library(game_of_life_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(game_of_life_run ${SOURCE_FILES} src/main.c)
