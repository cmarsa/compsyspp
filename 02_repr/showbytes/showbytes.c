// casting.c
/*
Procedures show_int, show_float, and show_pointer demonstrate how to
use procedure show_bytes to print the byte representations of C program objects
of type int, float, and void *, respectively. Observe that they simply pass show_
bytes a pointer &x to their argument x, casting the pointer to be of type unsigned
char *. This cast indicates to the compiler that the program should consider the
pointer to be to a sequence of bytes rather than to an object of the original data
type. This pointer will then be to the lowest byte address occupied by the object.
*/

#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;
    printf(" |");
    for (i = 0; i < len; i++) {
        printf(" %.2x |", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}

void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

int main() {
    test_show_bytes(12345);
}