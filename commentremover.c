#include <stdio.h>
#include <string.h>
int main(int argc, char **argv) {
  if (argc == 2) {
    FILE *fp = fopen(argv[1], "r+");
    if (fp != NULL) {
      fseek(fp, 0, SEEK_END);
      size_t size = ftell(fp);
      rewind(fp);
      char buf[size];
      fread(buf, 1, size, fp);
      char end = 0;
      char thing[3];
      thing[2] = '\0';
      for (size_t i = 0; buf[i] != 0; i++) {
        if (end == 2) {
          end = 0;
          if (strcmp(thing, "//") == 0 || strcmp(thing, "/*") == 0 || strcmp(thing, "*/") == 0) {
            for (size_t x = i - 2; buf[x] != 0; x++) {
              buf[x] = buf[x + 1];
            }
            for (size_t x = i - 2; buf[x] != 0; x++) {
              buf[x] = buf[x + 1];
            }
            size--;
          }
        } else {
          thing[end] = buf[i];
          end++;
        }
      }
      fclose(fopen(argv[1], "w"));
      rewind(fp);
      fwrite(buf, 1, size - 1, fp);
      fclose(fp);
    } else {
      printf("file is not valid\n");
    }
  }
  return 0;
}
