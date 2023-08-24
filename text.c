#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
void walk(char *path, char *text) {
  DIR *dp = opendir(path);
  if (dp != NULL) {
    struct dirent *current;
    while ((current = readdir(dp)) != NULL) {
      char buf[strlen(path) + strlen(current->d_name) + 2];
      strcpy(buf, path);
      strcat(buf, "/");
      strcat(buf, current->d_name);
      buf[strlen(buf)] = '\0';
      struct stat st;
      stat(buf, &st);
      switch (st.st_mode & S_IFMT) {
        case S_IFREG:
          {
            int fd = open(buf, O_RDONLY);
            if (fd != -1) {
              printf("%s\n", buf);
              size_t size = lseek(fd, 0, SEEK_END);
              char buffer[size];
              lseek(fd, 0, SEEK_SET);
              read(fd, buffer, size);
              if (strstr(buffer, text) != NULL) {
                printf("%s\n", buf);
              }
            }
            close(fd);
          }
          break;
        case S_IFDIR:
          if (strcmp(current->d_name, ".") != 0 && strcmp(current->d_name, "..") != 0) {
            walk(buf, text);
          }
          break;
      }
    }
    closedir(dp);
  }
}
int main(int argc, char **argv) {
  if (argc != 3) {
    printf("format: direcotry text\n");
    return 1;
  }
  walk(argv[1], argv[2]);
  return 0;
}
