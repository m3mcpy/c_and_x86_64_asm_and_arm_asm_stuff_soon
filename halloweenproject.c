#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
int main(void) {
  char pumpkin[] =
      "     z\n"
      "***********\n**xxx*xxx**\n**xxx*xxx**\n***********\n****xxx****\n****"
      "xxx****\n***********\n\0";
  char *colors[] = {"\x1b[40m", "\x1b[41m", "\x1b[42m", "\x1b[43m",
                    "\x1b[44m", "\x1b[45m", "\x1b[46m", "\x1b[47m"};
  while (1) {
    srand(time(NULL));
    char *color = colors[rand() % 8];
    for (size_t i = 0; i < strlen(pumpkin); i++) {
      if (pumpkin[i] == '*') {
        printf("\033[48:5:166m \033[m");
      } else if (pumpkin[i] == 'x') {
        printf("%s \x1b[0m", color);
      } else if (pumpkin[i] == 'z') {
        printf("\033[42m \x1b[0m");
      } else {
        printf("%c", pumpkin[i]);
      }
    }
    usleep(600);
    printf("\x1B[2J\x1B[1;1H");
    fflush(stdout);
  }
}
