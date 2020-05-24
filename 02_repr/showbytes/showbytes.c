// casting.c
/*
Procedures show_int, show_float, and show_pointer demonstrate how to
use procedure show_bytes to print the byte representations of C program objects
of type int, float, and void *, respectively. Observe that they simply pass show_
bytes a pointer &x to their argument x, casting the pointer to be of type unsigned
char *. This cast indicates to the compiler that the program should consider the
pointer to be to a sequence of bytes rather than to an object of the original data
type. This pointer will then be to the lowest byte address occupied by the object.

In function show_bytes, we see the close connection between pointers and arrays, as will
be discussed in detail in Section 3.8. We see that this function has an argument start of type byte_
pointer (which has been defined to be a pointer to unsigned char), but we see the array reference
start[i] on line 8. In C, we can dereference a pointer with array notation, and we can reference array
elements with pointer notation. In this example, the reference start[i] indicates that we want to read
the byte that is i positions beyond the location pointed to by start.
*/

#include <stdio.h>
#include <string.h>

typedef unsigned char *byte_pointer;


/*
 * function denitions
 */
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

void show_string(const char *m) {
    show_bytes((byte_pointer) m, strlen(m));
}

/*
 * tester functions
 */
void test_show_bytes(int val) {
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    show_int(ival);
    show_float(fval);
    show_pointer(pval);
}

void test_show_string(char* str) {
    show_string(str);
}


/*
 * main
 */
int main() {
    test_show_string("mnopqr");
}