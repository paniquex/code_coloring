#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

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

int
space_print_skip();


int main() {
    int flag = 0;
    int fd = open("//home/paniquex/CLionProjects/code_colorer/input.txt", O_RDONLY);
    dup2(fd, 0);
    close(fd);
    int symb;
    const int AMOUNT_OF_COLORERS = 7;
    int is_input_has_not_pattern[AMOUNT_OF_COLORERS];
    int is_step_was_sucessfull[AMOUNT_OF_COLORERS];
    for (int i = 0; i < 7; i++) {
        is_input_has_not_pattern[i] = 0;
        is_step_was_sucessfull[i] = 0;
    }
    while (!flag) {
        while (!is_input_has_not_pattern[0]) {
            int result;
            result = comment_colorer(1);
            if ((result == 3) || (result == 1)) {
                is_input_has_not_pattern[0] = 1;
            }
            if (result == 0) {
                is_step_was_sucessfull[0] = 1;
            }
            flag = space_print_skip();
        }

        while (!is_input_has_not_pattern[1]) {
            int result;
            result = number_colorer(1);
            if ((result == 3) || (result == 1)) {
                is_input_has_not_pattern[1] = 1;
            }
            if (result == 0) {
                is_step_was_sucessfull[1] = 1;
            }
            flag = space_print_skip();
        }
        if (is_step_was_sucessfull[1]) {
            is_input_has_not_pattern[0] = 0;
            is_input_has_not_pattern[1] = 0;
            is_step_was_sucessfull[1] = 0;
            continue;
        }
        //if (punctuator_colorer(PUNCTUATORS) == 3) {
        //    flag = space_print_skip();
        //    continue;
        //}
        punctuator_colorer(PUNCTUATORS);
        flag = space_print_skip();
        for (int i = 0; i < 7; i++) {
            is_input_has_not_pattern[i] = 0;
        }
    }
    return 0;
}


int 
number_colorer(int color) {
 /* 0 - if digit was found
  * 1 - if EOF was found
  * 2 - if some kind of error was found
  * 3 - if digit was not found*/

    int curr_symb, is_first_digit = 1;
    while ((curr_symb = getchar()) != EOF) {
        if (isdigit(curr_symb)) {
            if (is_first_digit) {
                printf("\033[1;31m");
                is_first_digit = 0;
            }
            putchar(curr_symb);
        } else {
            if (!is_first_digit) {
                printf("\033[0m");
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                return 0;
            }
            if (fseek(stdin, -1, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
            }
        }
    return 1;
}


int
comment_colorer(int color) {
    /*0, if somekind of comment was found
     *1, if EOF was reached
     *2, if somekind of error was found
     *3, if comment was not found
     */
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
        } else {
            if (fseek(stdin, -1, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        }
//        if (fseek(stdin, -1, SEEK_CUR) == -1) {
//            return 2;
//        }
//        return 0;
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
    int length_of_current_punctuator = 0;
    for (j; j < PUNCTUATOR_MAX_LENGTH; j++) {
        was_printed = 0;
        if ((curr_symb = getchar()) == EOF) {
            if (fseek(stdin, -j + length_of_current_punctuator, SEEK_CUR) == -1) {
                return 2;
            }
            if (!is_first_punc) printf("\033[0m");
            return 1;
        }
        for (int i=0; i < PUNCTUATORS_AMOUNT; i++) {
            if ((PUNCTUATORS[i][j] == curr_symb) && (indexes[i] == 1)) {
                if ((j == 0) && (is_first_punc)) {
                    is_first_punc = 0;
                    printf("\033[0;31m");
                }
                if (!was_printed) {
                    putchar(curr_symb);
                    length_of_current_punctuator++;
                    was_printed = 1;
                }
            } else {
                indexes[i] = 0;
            }
        }
    }
    if (fseek(stdin, -j + length_of_current_punctuator, SEEK_CUR) == -1) {
        return 2;
    }
}


int
space_print_skip() {
    int curr_symb;
    if ((curr_symb = getchar()) != EOF) {
        if (curr_symb != ' ') {
            if (fseek(stdin, -1, SEEK_CUR) == -1) {
                return 2;
            }
        } else {
            putchar(' ');
        }
    } else return 1;
    return 0;
}
