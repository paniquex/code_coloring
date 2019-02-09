#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

int 
number_colorer(int color);

int 
comment_colorer(int color);


int main() {
    int a;
    comment_colorer(1);
   // putchar(getchar());
   // putchar(fgetc(0));
    return 0;
}


int 
number_colorer(int color) {
    int curr_symb, is_first_symb = 1;
    while ((curr_symb = getchar()) != EOF) {
        if (isdigit(curr_symb) && (is_first_symb)) {
            printf("\033[0;31m");
            is_first_symb = 0;
        } else if (!(isdigit(curr_symb))) {
            break;
        }
        putchar(curr_symb);
    }
    if (!is_first_symb) {
        printf("\033[0m");
    }
    if (fseek(stdin, -1, SEEK_CUR) == -1) {
        return 1;
    }
    return 0;
}


int
comment_colorer(int color) {
    int curr_symb;
    int state1 = 0, state2 = 0;
    while ((curr_symb = getchar()) != EOF) {
        if (state1 == 3) {
            state1 = 2;
            putchar(curr_symb);
            continue;
        }
        if (state2 == 3) {
            if (curr_symb == '/') {
                printf("\\");
                printf("\033[0m");
                state2 = 0;
                return 0;
            }
            if (curr_symb != '*') {
                state2 = 2;
            }
            putchar(curr_symb);
            continue;
        }
        if (state1 == 2) {
            if (curr_symb == '\n') {
                state1 = 0;
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 1;
                }
                return 0;
            } else if (curr_symb == '\\') {
                state1 = 3;
            } else {
                putchar(curr_symb);
            }
            continue;
        }
        if (state2 == 2) {
            if (curr_symb == '*') {
                state2 = 3;
            }
            putchar(curr_symb);
            continue;
        }
        if ((state1 == 1) || (state2 == 1)) {
            if ((curr_symb != '/') && (curr_symb != '*')) {
                state1 = 0;
                state2 = 0;
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 1;
                }
                return 0;
            }
            else {
                printf("\033[0;33m");
                if (curr_symb == '/') {
                    state1 = 2;
                    state2 = 0;
                    printf("//");
                }
                else {
                    state1 = 0;
                    state2 = 2;
                    printf("/*");
                }
            }
            continue;
        }
        if ((curr_symb == '/') && (state1 == 0)) {
            state1 = 1;
            state2 = 1;
            continue;
        }
    }
}