#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
void walk(char *path, char *name) {
  DIR *dp = opendir(path);
  if (dp != NULL) {
    struct dirent *current;
    while ((current = readdir(dp)) != NULL) {
      char buf[strlen(path) + strlen(current->d_name) + 2];
      strcpy(buf, path);
      strcat(buf, "/");
      strcat(buf, current->d_name);
      buf[strlen(buf)] = '\0';
      if (strstr(buf, name) != NULL) {
        printf("%s\n", buf);
      }
      struct stat st;
      stat(buf, &st);
      switch (st.st_mode & S_IFMT) {
        case S_IFDIR:
          if (strcmp(current->d_name, ".") != 0 && strcmp(current->d_name, "..") != 0) {
            walk(buf, name);
          }
          break;
      }
    }
    closedir(dp);
  }
}
int main(int argc, char **argv) {
  if (argc != 3) {
    return 1;
  }
  walk(argv[1], argv[2]);
  return 0;
}
