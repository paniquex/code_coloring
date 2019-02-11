#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

/* Punctuators array for punctuator_colorer func */
enum {PUNCTUATORS_AMOUNT = 54, PUNCTUATOR_MAX_LENGTH = 4};
const char PUNCTUATORS[PUNCTUATORS_AMOUNT][PUNCTUATOR_MAX_LENGTH] = {
                            {'[', '0', '0', '0'},
                            {']', '0', '0', '0'},
                            {'(', '0', '0', '0'},
                            {')', '0', '0', '0'},
                            {'{', '0', '0', '0'},
                            {'}', '0', '0', '0'},
                            {'.', '0', '0', '0'},
                            {'-', '>', '0', '0'},
                            {'+', '+', '0', '0'},
                            {'-', '-', '0', '0'},
                            {'&', '0', '0', '0'},
                            {'*', '0', '0', '0'},
                            {'+', '0', '0', '0'},
                            {'-', '0', '0', '0'},
                            {'~', '0', '0', '0'},
                            {'!', '0', '0', '0'},
                            {'/', '0', '0', '0'},
                            {'%', '0', '0', '0'},
                            {'<', '<', '0', '0'},
                            {'>', '>', '0', '0'},
                            {'<', '0', '0', '0'},
                            {'>', '0', '0', '0'},
                            {'<', '=', '0', '0'},
                            {'>', '=', '0', '0'},
                            {'=', '=', '0', '0'},
                            {'!', '=', '0', '0'},
                            {'^', '0', '0', '0'},
                            {'|', '0', '0', '0'},
                            {'&', '&', '0', '0'},
                            {'|', '|', '0', '0'},
                            {'?', '0', '0', '0'},
                            {':', '0', '0', '0'},
                            {';', '0', '0', '0'},
                            {'.', '.', '.', '0'},
                            {'=', '0', '0', '0'},
                            {'*', '=', '0', '0'},
                            {'/', '=', '0', '0'},
                            {'%', '=', '0', '0'},
                            {'+', '=', '0', '0'},
                            {'-', '=', '0', '0'},
                            {'<', '<', '=', '0'},
                            {'>', '>', '=', '0'},
                            {'&', '=', '0', '0'},
                            {'^', '=', '0', '0'},
                            {'|', '=', '0', '0'},
                            {',', '0', '0', '0'},
                            {'#', '0', '0', '0'},
                            {'#', '#', '0', '0'},
                            {'<', ':', '0', '0'},
                            {':', '>', '0', '0'},
                            {'<', '%', '0', '0'},
                            {'%', '>', '0', '0'},
                            {'%', ':', '0', '0'},
                            {'%', ':', '%', ':'},
                                                                      };

int 
number_colorer(int color);

int 
comment_colorer(int color);

int
punctuator_colorer(const char PUNCTUATORS[PUNCTUATORS_AMOUNT][PUNCTUATOR_MAX_LENGTH]);


int main() {
    int flag = 0;
    while (!flag) {
        //flag = comment_colorer(1);
        //if (flag == 1) break;
        flag = number_colorer(1);
        //if (flag == 1) break;
        //flag = punctuator_colorer(PUNCTUATORS);
        //if (flag == 1) break;
        // putchar(getchar());
        // putchar(fgetc(0));
    }
    return 0;
}


int 
number_colorer(int color) {
    int curr_symb, is_first_symb = 1;
    while ((curr_symb = getchar()) != EOF) {
        if (isdigit(curr_symb) && (is_first_symb)) {
            printf("\033[1;31m");
            is_first_symb = 0;
        } else if (!(isdigit(curr_symb))) {
            if (!is_first_symb) {
                printf("\033[0m");
            } else {
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                return 0;
            }
        }
        putchar(curr_symb);
    }
    return 1;
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
                printf("/");
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
                    return 2;
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
                    return 2;
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
        if (fseek(stdin, -1, SEEK_CUR) == -1) {
            return 2;
        }
        return 0;
    }
    return 1;
}


int
punctuator_colorer(const char PUNCTUATORS[PUNCTUATORS_AMOUNT][PUNCTUATOR_MAX_LENGTH]) {
    short int indexes[PUNCTUATORS_AMOUNT];          /* 1, if start of punctuator matches with PUNCTUATORS i-th row
                                                    0, else*/
    for (int i=0; i < PUNCTUATORS_AMOUNT; i++) {
        indexes[i] = 1;
    }
    int curr_symb;
    char is_first_punc = 1;
    char was_printed = 0; // if on j-step one symbol of punctuator was printed
    int j=0;
    for (j; j < PUNCTUATOR_MAX_LENGTH; j++) {
        was_printed = 0;
        if ((curr_symb = getchar()) == EOF) {
            if (fseek(stdin, -j - 1, SEEK_CUR) == -1) {
                return 2;
            }
            if (!is_first_punc) printf("\033[0m");
            return 1;
        }
        for (int i=0; i < PUNCTUATORS_AMOUNT; i++) {
            if ((PUNCTUATORS[i][j] == curr_symb) && (indexes[i] == 1)) {
                if ((j == 0) && (is_first_punc)) {
                    is_first_punc = -1;
                    printf("\033[0;31m");
                }
                if (!was_printed) {
                    putchar(curr_symb);
                    was_printed = 1;
                }
            } else {
                indexes[i] = 0;
            }
        }
    }
    if (fseek(stdin, -j - 1, SEEK_CUR) == -1) {
        return 2;
    }
}