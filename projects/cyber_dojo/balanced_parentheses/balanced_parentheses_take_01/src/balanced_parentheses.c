#include "balanced_parentheses.h"
#include <string.h>

// Define opening and closing marks
static const char open_marks[] = {'(', '{', '['};
static const char close_marks[] = {')', '}', ']'};

/**
 * Checks if the input string has balanced parentheses, brackets, and braces.
 */
bool are_parentheses_balanced(const char* str) {
    // Stack to keep track of opening marks
    // We won't need more stack space than the length of the string
    char stack[strlen(str) + 1];
    int stack_top = -1; // Empty stack

    for (int i = 0; str[i] != '\0'; ++i) {
        char ch = str[i];

        // Check if it's an opening mark
        bool is_open = false;
        for (int j = 0; j < 3; ++j) {
            if (ch == open_marks[j]) {
                // Push the corresponding closing mark to the stack
                stack[++stack_top] = close_marks[j];
                is_open = true;
                break;
            }
        }

        if (is_open) {
            continue;
        }

        // Check if it's a closing mark
        for (int j = 0; j < 3; ++j) {
            if (ch == close_marks[j]) {
                // If stack is empty or top doesn't match, not balanced
                if (stack_top == -1 || ch != stack[stack_top]) {
                    return false;
                }
                // Pop from stack
                stack_top--;
                break;
            }
        }
    }

    // Stack should be empty for balanced parentheses
    return stack_top == -1;
}
