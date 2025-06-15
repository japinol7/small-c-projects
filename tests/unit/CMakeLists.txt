cmake_minimum_required(VERSION 3.28)
project(Google_tests_unit VERSION 1.17.0)


# FizzBuzz tests
add_executable(fizzbuzz_tests_run
        cyber_dojo/fizzbuzz/fizzbuzz_take_01/src/test_fizzbuzz.cpp
)

target_include_directories(fizzbuzz_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(fizzbuzz_tests_run
        PRIVATE
        fizzbuzz_lib
        gtest_main
        gtest
)

# FizzBuzz Plus tests
add_executable(fizzbuzz_plus_tests_run
        cyber_dojo/fizzbuzz_plus/fizzbuzz_plus_take_01/src/test_fizzbuzz_plus.cpp
)

target_include_directories(fizzbuzz_plus_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(fizzbuzz_plus_tests_run
        PRIVATE
        fizzbuzz_plus_lib
        gtest_main
        gtest
)

# Balanced Parentheses tests
add_executable(balanced_parentheses_tests_run
        cyber_dojo/balanced_parentheses/balanced_parentheses_take_01/src/test_balanced_parentheses.cpp
)

target_include_directories(balanced_parentheses_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(balanced_parentheses_tests_run
        PRIVATE
        balanced_parentheses_lib
        gtest_main
        gtest
)


# Filename Range tests
add_executable(filename_range_tests_run
        cyber_dojo/filename_range/filename_range_take_01/src/test_filename_range.cpp
)

target_include_directories(filename_range_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(filename_range_tests_run
        PRIVATE
        filename_range_lib
        gtest_main
        gtest
)


# Game of life
add_executable(game_of_life_tests_run
        cyber_dojo/game_of_life/game_of_life_take_01/src/test_game_of_life.cpp
)

target_include_directories(game_of_life_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(game_of_life_tests_run
        PRIVATE
        game_of_life_lib
        gtest_main
        gtest
)

# ISBN tests
add_executable(isbn_tests_run
        cyber_dojo/isbn/isbn_take_01/src/test_isbn.cpp
)

target_include_directories(isbn_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(isbn_tests_run
        PRIVATE
        isbn_lib
        gtest_main
        gtest
)

# Leap Year tests
add_executable(leap_year_tests_run
        cyber_dojo/leap_year/leap_year_take_01/src/test_leap_year.cpp
)

target_include_directories(leap_year_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(leap_year_tests_run
        PRIVATE
        leap_year_lib
        gtest_main
        gtest
)

# Print Diamond tests
add_executable(print_diamond_tests_run
        cyber_dojo/print_diamond/print_diamond_take_01/src/test_print_diamond.cpp
)

target_include_directories(print_diamond_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(print_diamond_tests_run
        PRIVATE
        print_diamond_lib
        gtest_main
        gtest
)

# LCD Digits tests
add_executable(lcd_digits_tests_run
        cyber_dojo/lcd_digits/lcd_digits_take_01/src/test_lcd_digits.cpp
)

target_include_directories(lcd_digits_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(lcd_digits_tests_run
        PRIVATE
        lcd_digits_lib
        gtest_main
        gtest
)

# Roman Numerals Full tests
add_executable(roman_numerals_full_tests_run
        various/roman_numerals_full/roman_numerals_full_take_01/src/test_roman_numerals_full.cpp
)

target_include_directories(roman_numerals_full_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(roman_numerals_full_tests_run
        PRIVATE
        roman_numerals_full_lib
        gtest_main
        gtest
)

# Roman Numerals tests
add_executable(roman_numerals_tests_run
        cyber_dojo/roman_numerals/roman_numerals_take_01/src/test_roman_numerals.cpp
)

target_include_directories(roman_numerals_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(roman_numerals_tests_run
        PRIVATE
        roman_numerals_lib
        gtest_main
        gtest
)

# Reverse Roman tests
add_executable(reverse_roman_tests_run
        cyber_dojo/reverse_roman/reverse_roman_take_01/src/test_reverse_roman.cpp
)

target_include_directories(reverse_roman_tests_run
        PRIVATE ${gtest_SOURCE_DIR}/include
        PRIVATE ${gtest_SOURCE_DIR}
)

target_link_libraries(reverse_roman_tests_run
        PRIVATE
        reverse_roman_lib
        gtest_main
        gtest
)
