#include <stdio.h>

void reverse_array(int array[], int size);
void print_array(int array[], int size);


/*Reverse array*/
void reverse_array(int array[], int size) {
    int tmp;
    for (int i = 0; i < size / 2; ++i) {
        tmp = array[i];
        array[i] = array[size - 1 - i];
        array[size - 1 - i] = tmp;
    }
}

void print_array(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%3d\n", array[i]);
    }
}

int main(void) {
    const int N = 13;
    int nums[N];

    /*Fill nums*/
    for (int i = 0; i < N; ++i) {
        nums[i] = (i + 1) * 5;
    }

    print_array(nums, N);

    printf(" ------- Reversed -------\n");
    reverse_array(nums, N);

    print_array(nums, N);
}
