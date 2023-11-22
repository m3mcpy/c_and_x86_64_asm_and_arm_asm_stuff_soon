#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv) {
  if (argc == 2) {
    size_t size = 1;
    size_t sum = 0;
    for (size_t i = strlen(argv[1]) - 1; i != -1; i--) {
      if (argv[1][i] == '1') {
        sum += size;
      } else if (argv[1][i] != '0') {
        return 0;
      }
      size *= 2;
    }
    char *hex = NULL;
    size_t hexsize = 0;
    while (sum != 0) {
      char mode = 0;
      char value = sum % 16;
      switch (sum % 16) {
      case 10:
        value = 'a';
        break;
      case 11:
        value = 'b';
        break;
      case 12:
        value = 'c';
        break;
      case 13:
        value = 'd';
        break;
      case 14:
        value = 'e';
        break;
      case 15:
        value = 'f';
        break;
      default:
        value += '0';
        break;
      }
      hex = realloc(hex, hexsize + 1);
      hex[hexsize++] = value;
      sum /= 16;
    }
    for (size_t i = strlen(hex); i != -1; i--) {
      printf("%c", hex[i]);
    }
    printf("\n");
    free(hex);
  }
  return 0;
}
