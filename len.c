#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    printf("%ld\n", strlen(argv[1]));
    return 0;
}
