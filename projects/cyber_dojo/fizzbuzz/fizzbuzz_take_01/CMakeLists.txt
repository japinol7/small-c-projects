cmake_minimum_required(VERSION 3.28)

project(fizzbuzz_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/fizzbuzz.h
        src/utils/utils.h
)

set(SOURCE_FILES
        src/fizzbuzz.c
        src/utils/utils.c
)

add_library(fizzbuzz_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(fizzbuzz_run ${SOURCE_FILES} src/main.c)
