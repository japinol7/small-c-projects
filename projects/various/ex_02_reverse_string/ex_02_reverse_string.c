#include <stdio.h>

void reverse_str(char str[], int size);
int str_len(const char str[]);


/*Reverse str*/
void reverse_str(char str[], const int size) {
    char tmp;
    for (int i = 0; i < size / 2; ++i) {
        tmp = str[i];
        str[i] = str[size - 1 - i];
        str[size - 1 - i] = tmp;
    }
}

int str_len(const char str[]) {
    for (int i = 0;; ++i) {
        if (str[i] == '\0')
            return i;
    }
}

int main(void) {
    char str[] = "Hello 123456789";
    const int len = str_len(str);

    printf("%s\n", str);

    printf(" ------- Reversed -------\n");
    reverse_str(str, len);

    printf("%s\n", str);
}
