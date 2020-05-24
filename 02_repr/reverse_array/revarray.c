#include <stdio.h>
#include <stdlib.h>


void inplace_swap(int *x, int *y) {
    /*
     * changes the variable values without an intermediate
     * local variable to be created. There's no computational
     * advantage when impmenting this. Pure study purpouses.
     */
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}


void reverse_array(int a[], int count) {
    for (int first = 0, last = count - 1; first < last; first++, last--) {
        inplace_swap(&a[first], &a[last]);
    }
}

int main (int argc, char *argv[]) {

    int array_size = atoi(argv[1]);
    int array[array_size];

    // fill array
    for (int i = 0; i < array_size; i++) {
        array[i] = i;
    }

    // print the array
    printf("Ordered array:\n");
    for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
        if (i % 10 == 0 & i != 0)
            printf("\n");
        printf("%2d ", array[i]);
    }
    printf("\n");

    reverse_array(array, array_size);

    // print the array
    printf("Reversed array:\n");
    for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
        if (i % 10 == 0 & i != 0)
            printf("\n");
        printf("%2d ", array[i]);
    }
    printf("\n");

    return 0;
}