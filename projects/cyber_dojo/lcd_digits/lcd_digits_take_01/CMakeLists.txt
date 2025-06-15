cmake_minimum_required(VERSION 3.28)

project(lcd_digits_lib C)

set(CMAKE_C_STANDARD 17)

set(HEADER_FILES
        src/lcd_digits.h
        src/lcd_digit_cell.h
)

set(SOURCE_FILES
        src/lcd_digits.c
        src/lcd_digit_cell.c
)

add_library(lcd_digits_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_executable(lcd_digits_run ${SOURCE_FILES} src/main.c)
