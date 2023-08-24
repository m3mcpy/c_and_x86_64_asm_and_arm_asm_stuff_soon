#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
typedef struct {
    short y;
    short x;
} size;
char *input(void) {
    char *str = NULL;
    char c;
    size_t size = 0;
    while ((c = getchar()) != '\n') {
        str = realloc(str, size + 1);
        str[size++] = c;
    }
    if (size > 0) {
        str[size] = '\0';
    }
    return str;
}
void movetoend(size_t *index, char way, char *str, size_t len) {
    size_t count = 0;
    if (str[*index] == '\n') {
        *index -= 1;
    }
    while ((*index < len + 1 || *index > 0) && count != 1) {
        if (str[*index] == '\n') {
            count++;
        }
        *index += way;
    }
}
int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }
    int fp = open(argv[1], O_CREAT | O_RDWR | O_APPEND, 0644);
    if (fp == -1) {
        return 1;
    }
    size s;
    struct termios old, new;
    tcgetattr(0, &old);
    new = old;
    new.c_lflag = 2 & 8;
    tcsetattr(0, 0, &new);
    ioctl(1, 0x5413, &s);
    size_t len = lseek(fp, 0, SEEK_END);
    size_t pointer = 0;
    lseek(fp, 0, SEEK_SET);
    len--;
    char *str = malloc(len + 2);
    if (len != (size_t)-1) {
        read(fp, str, len + 1);
        str[len] = ' ';
        str[len + 1] = '\0';
        len += 2;
    } else {
        str = realloc(str, 2);
        str[0] = ' ';
        str[1] = '\0';
        len = 2;
    }
    char buf;
    len--;
    size_t start = 0;
    size_t count = 0;
    size_t end;
    for (end = 0; end < len + 1 && count < (size_t)s.y-2; end++) {
        if (str[end] == '\n') {
            count++;
        }
    }
    while (1) {
        if (pointer >= end) {
            movetoend(&start, 1, str, len);
            movetoend(&end, 1, str, len);
        } else if (pointer < start) {
            movetoend(&start, -1, str, len);
            movetoend(&end, -1, str, len);
        }
        if (end >= len + 1) {
            end = len;
        }
        if (str[start - 1] > 0 && str[start - 1] != '\n') {
            for (size_t i = start; i > 0 && str[i] !='\n'; i--) {
                start--;
            }
        }
        if (start < 1) {
            start = 0;
        }
        printf("\x1B[2J\x1B[1;1H");
        for (size_t i = start; i < end; i++) {
            if (i == pointer) {
                printf("\x1b[41m%c\x1b[0m", str[i]);
            } else {
                printf("%c", str[i]);
            }
        }
        printf("\n");
        switch (buf = getchar()) {
            case 2:
                {
                    char *temp1 = str;
                    for (size_t i = len; i > 0; i--) {
                        temp1[i] = str[i];
                    }
                    char *inp = input();
                    char *temp2 = inp;
                    for (size_t i = strlen(inp); i > 0; i--) {
                        temp2[i] = inp[i];
                    }
                    char *ss = strstr(temp1, temp2);
                    if (ss != NULL) {
                        pointer = ss - temp1;
                    }
                }
                break;
            case 5:
                {
                    size_t current = 0;
                    for (size_t i = pointer; i != (size_t)-1 && str[i] != '\n'; i--) {
                        current++;
                    }
                    for (size_t i = pointer; i < len && str[i] != '\n'; i++) {
                        current++;
                    }
                    size_t p = pointer;
                    size_t temp = 0;
                    for (size_t i = pointer; i < pointer + current && temp != 2 && i != len - 1; i++) {
                        if (str[i] == '\n') {
                            temp++;
                        }
                        p++;
                    }
                    if (temp == 2) {
                        p -= 2;
                    }
                    if (temp >= 1) {
                        pointer = p;
                    }
                }
                break;
            case 6:
                {
                    char *ss = strstr(str, input());
                    if (ss != NULL) {
                        pointer = ss - str;
                    }
                }
                break;
            case 18:
                if (pointer > 0) {
                    pointer--;
                }
                break;
            case 20:
                if (pointer < len - 1) {
                    pointer++;
                }
                break;
            case 23:
                {
                    size_t current = 0;
                    for (size_t i = pointer; i != (size_t)-1 && str[i] != '\n'; i--) {
                        current++;
                    }
                    for (size_t i = pointer; i < len && str[i] != '\n'; i++) {
                        current++;
                    }
                    size_t thing = 0;
                    size_t check = 0;
                    for (size_t i = pointer; i != (size_t)-1 && check != 2; i--) {
                        if (str[i] == '\n') {
                            check++;
                        }
                        if (check == 1) {
                            thing++;
                        }
                    }
                    if (pointer >= thing && pointer >= current) {
                        if (current > thing) {
                            pointer -= current;
                        } else {
                            pointer -= thing;
                        }
                        if (str[pointer] == '\n') {
                            pointer--;
                        }
                    }
                }
                break;
            case 24:
                free(str);
                close(fp);
                tcsetattr(0, 0, &old);
                return 0;
            case 26:
                {
                    int f = open(argv[1], O_WRONLY | O_TRUNC);
                    close(f);
                    write(fp, str, len - 1);
                    write(fp, "\n", 1);
                    lseek(fp, 0, SEEK_SET);
                }
                break;
            case 127:
                {
                    if (pointer > 0 && len > 0) {
                        str = realloc(str, len - 1);
                        for (size_t i = pointer - 1; i < len + 1; i++) {
                            str[i] = str[i + 1];
                        }
                        len--;
                        end--;
                        pointer--;
                        str[len] = '\0';
                        break;
                    }
                }
            default:
                if (buf == 10 || (buf >= 32 && buf <= 126)) {
                    str = realloc(str, len + 2);
                    for (size_t i = len + 1; i > pointer; i--) {
                        str[i] = str[i - 1];
                    }
                    str[pointer] = buf;
                    str[len + 1] = '\0';
                    len++;
                    pointer++;
                    end++;
                    break;
                }
        }
    }
}
