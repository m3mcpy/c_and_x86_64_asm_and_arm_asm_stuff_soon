#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>
typedef struct {
	short y;
	short x;
} size;
int main(void) {
  if (fork() > 0) {
    setsid();
    return 0;
  }
  srandom(0xdecaf);
  size s;
  ioctl(1, 0x5413, &s);
  char *letters = "`~1!2@3#4$5%6^7&8*9(0)-_=+qQwWeErRtTyYuUiIoOpP[{}]\\|aAsSdDfFgGhHjJkKlL;:'zZxXcCvVbBnNmM,<.>/?";
  char *colors[] = {"\x1b[40m \x1b[0m", "\x1b[41m \x1b[0m", "\x1b[42m \x1b[0m", "\x1b[43m \x1b[0m", "\x1b[44m \x1b[0m", "\x1b[45m \x1b[0m", "\x1b[46m \x1b[0m", "\x1b[47m \x1b[0m"};
  while (1) {
    short termx = random() % s.x;
    short termy = random() % s.y;
    char buf[4 + termx + termy];
    sprintf(buf, "\033[%d;%dH", termy, termx);
    if (rand() % 2 == 0) {
      printf("%s%s", buf, colors[rand() % 7]);
    } else {
      printf("%s%c", buf, letters[rand() % 26]);
    }
    fflush(stdout);
    usleep(70000);
  }
}
