#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char **argv) {
  if (argc != 2) {
    return 1;
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd != -1) {
    printf("%ld\n", lseek(fd, 0, SEEK_END));
    close(fd);
  }
  return 0;
}
