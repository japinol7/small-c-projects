#include "leap_year.h"

// IsLeapYear determines if a given year is a leap year
int IsLeapYear(const int year) {
    if (year < 1) {
        return 0;
    }
    if (year % 400 == 0) {
        return 1;
    }
    if (year % 4 == 0) {
        return year % 100 != 0;
    }
    return 0;
}
