#include <stdio.h>
#define gettype(array) _Generic(array, char *: 1, short *: 2, int *: 3, float *: 4, long *: 5, double *: 6)
int main(void) {
    int a[] = {1, 2, 3, 4};
    switch (gettype(a)) {
        case 1:
            printf("char * type\n");
            break;
        case 2:
            printf("short * type\n");
            break;
        case 3:
            printf("int * type\n");
            break;
        case 4:
            printf("float * type\n");
            break;
        case 5:
            printf("long * type\n");
            break;
        case 6:
            printf("double * type\n");
            break;
    }
}
