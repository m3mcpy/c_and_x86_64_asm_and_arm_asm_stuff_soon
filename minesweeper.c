#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
void showspikes(char *map, int *random) {
    for (size_t i = 0; i < 10; i++) {
        map[random[i]] = '^';
    }
}
int main(void) {
    srand(time(NULL));
    printf("\x1B[2J\x1B[1;1H");
    struct termios old, new;
    tcgetattr(0, &old);
    new = old;
    new.c_lflag = 2 & 8;
    tcsetattr(0, 0, &new);
    char map[] = "> < | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\n| | | | | | | | | | |\0";
    size_t len = strlen(map);
    int random[10] = {rand() % len, rand() % len, rand() % len, rand() % len, rand() % len, rand() % len, rand() % len, rand() % len, rand() % len};
    for (size_t i = 0; i < 10; i++) {
        if (random[i] == 0) {
            random[i]++;
        } else if (map[random[i]] == '\n') {
            random[i] -= 2;
        } else if (map[random[i]] == '|') {
            random[i]--;
            if (map[random[i]] == '\n') {
                random[i] -= 2;
            }
        }
    }
    size_t start = 0;
    char won = 0;
    while (1) {
        printf("%s\n", map);
        switch (getchar()) {
            case 10:
                if (map[start + 1] == ' ') {
                    for (size_t i = 0; i < 10; i++) {
                        if (random[i] == start + 1) {
                            showspikes(map, random);
                            system("clear");
                            printf("%s\n", map);
                            tcsetattr(0, 0, &old);
                            return 1;
                        }
                    }
                    map[start + 1] = '*';
                }
                break;
            case 'w':
                if (start > 18) {
                    map[start] = '|';
                    map[start + 2] = '|';
                    start -= 22;
                    map[start] = '>';
                    map[start + 2] = '<';
                }
                break;
            case 'a':
                if (start > 0) {
                    map[start] = '|';
                    map[start + 2] = '|';
                    if (map[start - 1] == '\n') {
                        start -= 4;
                    } else {
                        start -= 2;
                    }
                    map[start] = '>';
                    map[start + 2] = '<';
                }
                break;
            case 's':
                if (start + 22 <= strlen(map)) {
                    map[start] = '|';
                    map[start + 2] = '|';
                    start += 22;
                    map[start] = '>';
                    map[start + 2] = '<';
                }
                break;
            case 'd':
                if (start + 4 <= strlen(map)) {
                    map[start] = '|';
                    map[start + 2] = '|';
                    if (map[start + 3] == '\n') {
                        start += 4;
                    } else {
                        start += 2;
                    }
                    map[start] = '>';
                    map[start + 2] = '<';
                }
                break;
            case 'q':
                tcsetattr(0, 0, &old);
                return 1;
        }
        printf("\x1B[2J\x1B[1;1H");
        won = 1;
        for (size_t i = 0; i < strlen(map); i++) {
            for (size_t x = 0; x < 10; x++) {
                if (i != random[x] && map[i] == ' ') {
                    won = 0;
                }
            }
        }
        if (won) {
            printf("%s\n", map);
            tcsetattr(0, 0, &old);
            return 1;
        }
    }
}

