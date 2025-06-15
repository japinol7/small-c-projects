#include <stdio.h>
#include "balanced_parentheses.h"

int main(void) {
    printf("Start app Balanced Parentheses\n");

    const char* input_str = "((()))";
    bool res = are_parentheses_balanced(input_str);
    printf("Are parentheses balanced for : '%s' ? %s\n",
           input_str, res ? "true" : "false");

    input_str = "(()))";
    res = are_parentheses_balanced(input_str);
    printf("Are parentheses balanced for : '%s' ? %s\n",
           input_str, res ? "true" : "false");

    printf("End app Balanced Parentheses\n");

    return 0;
}
