#include <stdio.h>
#define typecmp(t1, t2) (_Generic((t1)0, char: 0, short: 1, int: 2, float: 3, long: 4, double: 5) == _Generic((t2)0, char: 0, short: 1, int: 2, float: 3, long: 4, double: 5))
int main(void) {
  printf("%d\n", typecmp(int, double));
}
