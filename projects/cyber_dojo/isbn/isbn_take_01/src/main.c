#include "isbn.h"
#include <stdio.h>

int main() {
    const char* app_name = "Validate ISBN-13 and ISBN-10";
    printf("Start app %s\n", app_name);

    char result[10];

    // Check valid isbn-13
    const char* isbn = "978-0-262-13472-9";
    validate_isbn(isbn, result, sizeof(result));
    printf("Should be true.  Is '%s' a valid isbn?: %s\n", isbn, result);

    // Check invalid isbn-13
    isbn = "978-0-262-13472-1";
    validate_isbn(isbn, result, sizeof(result));
    printf("Should be false. Is '%s' a valid isbn?: %s\n", isbn, result);

    // Check valid isbn-10
    isbn = "0-8044-2957-X";
    validate_isbn(isbn, result, sizeof(result));
    printf("Should be true.  Is '%s' a valid isbn?: %s\n", isbn, result);

    // Check invalid isbn-10
    isbn = "0-4A0-84525-2";
    validate_isbn(isbn, result, sizeof(result));
    printf("Should be false. Is '%s' a valid isbn?: %s\n", isbn, result);

    printf("End app %s\n", app_name);

    return 0;
}
