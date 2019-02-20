#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/* Keywords array for keyword_colorer func */
enum {KEYWORDS_AMOUNT = 14, KEYWORD_MAX_LENGTH = 14};
const char KEYWORDS[KEYWORDS_AMOUNT][KEYWORD_MAX_LENGTH] = {
        {'u', 'n', 's', 'i', 'g', 'n', 'e', 'd', '0', '0', '0', '0', '0', '0'},
        {'v', 'o', 'i', 'd', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'v', 'o', 'l', 'o', 't', 'i', 'l', 'e', '0', '0', '0', '0', '0', '0'},
        {'w', 'h', 'i', 'l', 'e', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'_', 'A', 'l', 'i', 'g', 'n', 'a', 's', '0', '0', '0', '0', '0', '0'},
        {'_', 'A', 'l', 'i', 'g', 'n', 'o', 'f', '0', '0', '0', '0', '0', '0'},
        {'_', 'A', 't', 'o', 'm', 'i', 'c', '0', '0', '0', '0', '0', '0', '0'},
        {'_', 'B', 'o', 'o', 'l', '0', '0', '0', '0', '0', '0', '0', '0', '0'},
        {'_', 'C', 'o', 'm', 'p', 'l', 'e', 'x', '0', '0', '0', '0', '0', '0'},
        {'_', 'G', 'e', 'n', 'e', 'r', 'i', 'c', '0', '0', '0', '0', '0', '0'},
        {'_', 'I', 'm', 'a', 'g', 'i', 'n', 'a', 'r', 'y', '0', '0', '0', '0'},
        {'_', 'N', 'o', 'r', 'e', 't', 'u', 'r', 'n', '0', '0', '0', '0', '0'},
        {'_', 'S', 't', 'a', 't', 'i', 'c', '_', 'a', 's', 's', 'e', 'r', 't'},
        {'_', 'T', 'h', 'r', 'e', 'a', 'd', '_', 'l', 'o', 'c', 'a', 'l', '0'},
                                                        };

/* Punctuators array for punctuator_colorer func */
enum {PUNCTUATORS_AMOUNT = 43, PUNCTUATOR_MAX_LENGTH = 4};
const char PUNCTUATORS[PUNCTUATORS_AMOUNT][PUNCTUATOR_MAX_LENGTH] = {
                            {'-', '-', '0', '0'},
                            {'&', '0', '0', '0'},
                            {'*', '0', '0', '0'},
                            {'+', '0', '0', '0'},
                            {'+', '+', '0', '0'},
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
                                                                      };

int 
number_colorer(int color);

int 
comment_colorer(int color);

int
punctuator_colorer(const char PUNCTUATORS[PUNCTUATORS_AMOUNT][PUNCTUATOR_MAX_LENGTH]);

int
keyword_colorer(const char KEYWORDS[KEYWORDS_AMOUNT][KEYWORD_MAX_LENGTH]);

int
identifier_colorer(int color);

int
is_white_space(int symb);

int
white_space_print_skip();

int
is_nondigit(int symb);

int
string_literal_colorer(int color);

int
char_consts_colorer(int color);

int main() {
    int flag = 0;
    int fd = open("//home/paniquex/CLionProjects/code_colorer/input.txt", O_RDONLY);
    int fd1 = open("//home/paniquex/CLionProjects/code_colorer/input.txt", O_WRONLY | O_APPEND);
    char space = ' ';
    write(fd1, &space, sizeof(space));
    close(fd1);
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
    while (getchar() != EOF) {
        fseek(stdin, -1, SEEK_CUR);
        while (white_space_print_skip() == 0);
        if (white_space_print_skip() == 1) {
            break;
        }
        flag = comment_colorer(0);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***Comment colorer***");
            return 2;
        }

        flag = string_literal_colorer(0);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***String literal colorer***");
            return 2;
        }

        flag = char_consts_colorer(0);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***Char consts colorer***");
            return 2;
        }

        flag = keyword_colorer(KEYWORDS);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***Keyword colorer***");
            return 2;
        }

        flag = identifier_colorer(0);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***Identifier colorer***");
            return 2;
        }

        flag = number_colorer(0);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***Number colorer***");
            return 2;
        }

        flag = punctuator_colorer(PUNCTUATORS);
        if (flag == 0) {
            continue;
        } else if (flag == 2) {
            perror("***Punctuator colorer***");
            return 2;
        }
        putchar(getchar());
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
                printf("\033[1;36m");
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
        if ((curr_symb == '/') && (state1 == 0)) {
            state1 = 1;
            state2 = 1;
            continue;
        } else if ((state1 == 0) && (state2 == 0)) {
            if (fseek(stdin, -1, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        }
        if ((state1 == 1) || (state2 == 1)) {
            if ((curr_symb != '/') && (curr_symb != '*')) {
                state1 = 0;
                state2 = 0;
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                return 3;
            }
            else {
                printf("\033[4;33m");
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

        if (state1 == 2) {
            if (curr_symb == '\n') {
                state1 = 0;
                printf("\033[0m");
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
        if (fseek(stdin, -1, SEEK_CUR) == -1) {
            return 2;
        }
        return 0;
        printf("\033[0m");
    }
    printf("\033[0m");
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
            if ((PUNCTUATORS[i][j] == curr_symb) && (PUNCTUATORS[i][j] != '0') && (indexes[i] == 1)) {
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
    if (!is_first_punc) {
        printf("\033[0m");
        return 0;
    }
    return 3;
}


int
keyword_colorer(const char KEYWORDS[KEYWORDS_AMOUNT][KEYWORD_MAX_LENGTH]) {

/* 0, if keyword was found and printed
 * 1, if EOF was reached
 * 2, if somekind of error was found
 * 3, if no keyword was found
 *
 * at the end of keyword must be at least one white space, if keyword ends without white spaces - don't print
 * EXAMPLE:
 * 1)*EOF* - end of file
 * input:_Imaginary*EOF*
 * output:
 * 2)*WHITESPACE* - white space symbol
 * input:_Imaginary*WHITESPACE**EOF*
 * output:_Imaginary*WHITESPACE*
 */


    short int indexes[KEYWORDS_AMOUNT];          /* 1, if start of keyword matches with KEYWORDS i-th row
                                                    0, else*/
    for (int i=0; i < KEYWORDS_AMOUNT; i++) {
        indexes[i] = 1;
    }
    int keyword_to_print[KEYWORD_MAX_LENGTH];
    for (int i=0; i < KEYWORD_MAX_LENGTH; i++) {
        keyword_to_print[i] = 0;
    }
    int curr_symb;
    char is_first_keyword = 1;
    char is_at_least_one_full_keyword = 0;
    char was_printed = 0; // if on symb_was_read-step one symbol of keyword was printed
    int amount_symb_was_read = 0;
    int length_of_current_keyword = 0;
    int is_indexes_array_of_zeros = 0;
    for (amount_symb_was_read; amount_symb_was_read < KEYWORD_MAX_LENGTH; amount_symb_was_read++) {
        is_indexes_array_of_zeros = 1; // for check if there is at leats one 1
        for (int i = 0; i < KEYWORDS_AMOUNT; i++) {
            if (indexes[i] != 0) {
                is_indexes_array_of_zeros = 0;
            }
        }
        if (is_indexes_array_of_zeros) {
            printf("\033[0m");
            if (fseek(stdin, -amount_symb_was_read, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        }
        was_printed = 0;
        if ((curr_symb = getchar()) == EOF) {
            if (is_at_least_one_full_keyword) {
                for (int i = 0; i < length_of_current_keyword; i++) {
                    printf("%c", keyword_to_print[i]);
                }
            } else {
                printf("\033[0m");
            }
            if (fseek(stdin, -amount_symb_was_read + length_of_current_keyword, SEEK_CUR) == -1) {
                return 2;
            }
            if (!is_first_keyword) printf("\033[0m");
            return 1;
        }
        for (int i=0; i < KEYWORDS_AMOUNT; i++) {
            if ((KEYWORDS[i][amount_symb_was_read] == curr_symb) && (KEYWORDS[i][amount_symb_was_read] != '0') && (indexes[i] == 1)) {
                if ((amount_symb_was_read == 0) && (is_first_keyword)) {
                    is_first_keyword = 0;
                    printf("\033[0;34m");
                }
                if (!was_printed) {
                    //putchar(curr_symb);
                    keyword_to_print[length_of_current_keyword] = curr_symb;
                    length_of_current_keyword++;
                    was_printed = 1;
                }
            } else {
                if ((is_white_space(curr_symb)) && (KEYWORDS[i][amount_symb_was_read] == '0') && (indexes[i] != 0)) {
                    for (int k = 0; k < length_of_current_keyword; k++) {
                        putchar(keyword_to_print[k]);
                    }
                    putchar(curr_symb);
                    if (!is_first_keyword) printf("\033[0m");
                    return 0;
                }
                indexes[i] = 0;
            }
        }
    }
    if (fseek(stdin, -amount_symb_was_read + length_of_current_keyword, SEEK_CUR) == -1) {
        return 2;
    }
}




int identifier_colorer(int color) {
    int curr_symb;
    int amount_symb_was_read = 0;
    int state1 = 0;
    while ((curr_symb = getchar()) != EOF) {
        amount_symb_was_read++;
        if (state1 == 0) {
            if (is_nondigit(curr_symb)) {
//                printf("\033[0;95m");
//                putchar(curr_symb);
                state1 = 1;
                continue;
            } else {
                if (fseek(stdin, -amount_symb_was_read, SEEK_CUR) == -1) {
                    return 2;
                }
                return 3;
            }
        }
        if (state1 == 1) {
            if ((is_nondigit(curr_symb)) || (isdigit(curr_symb)))  {

            } else {
                if (fseek(stdin, -amount_symb_was_read, SEEK_CUR) == -1) {
                    return 2;
                }
                printf("\033[0;95m");
                for(int i = 0; i < amount_symb_was_read-1; i++) {
                    putchar(getchar());
                }
                printf("\033[0m");
                return 0;
//            } else {
//                if (fseek(stdin, -amount_symb_was_read, SEEK_CUR) == -1) {
//                    return 2;
//                }
//                return 3;
            }
        }
    }
    if (fseek(stdin, -amount_symb_was_read - 1, SEEK_CUR) == -1) {
        return 2;
    }
    return 1;
}


int
is_white_space(int symb) {
    /* 0, if it is not white_space
     * 1  else
     */
    enum { WHITE_SPACE_AMOUNT = 6 };
    const char WHITE_SPACE_ARRAY[WHITE_SPACE_AMOUNT] = {' ', '\t', '\n', '\v', '\f', '\r'};
    for (int i=0; i < WHITE_SPACE_AMOUNT; i++) {
        if (symb == WHITE_SPACE_ARRAY[i]) {
            return 1;
        }
    }
    return 0;
}

int
white_space_print_skip() {
    /* 0, if this symb is white_space
     * 1, if EOF
     * 2, if some kind of error was found
     * 3, if symb is not white_space*/
    int curr_symb;
    if ((curr_symb = getchar()) != EOF) {
        if (!is_white_space(curr_symb)) {
            if (fseek(stdin, -1, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        } else {
            putchar(curr_symb);
        }
    } else return 1;
    return 0;
}


int is_nondigit(int symb) {
    if ((isalpha(symb)) || (symb == '_')) return 1;
    else return 0;
}


int
string_literal_colorer(int color) {
    int curr_symb;
    int state = 0;
    while ((curr_symb = getchar()) != EOF) {
        if (state == 0) {
            if (curr_symb == '\"') {
                printf("\033[0;32m");
                putchar(curr_symb);
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                if ((curr_symb == 'L') || (curr_symb == 'U')) {
                    curr_symb = getchar();
                    if (curr_symb != '\"') {
                        if (fseek(stdin, -2, SEEK_CUR) == -1) {
                            return 2;
                        }
                        printf("\033[0m");
                        return 3;
                    } else {
                        printf("\033[0;32m");
                        printf("%c\"", curr_prefix);
                        state = 1;
                        continue;
                    }
                } else { //curr_symb == u
                    curr_symb = getchar();
                    if ((curr_symb != '8') && (curr_symb != '\"')) {
                        if (fseek(stdin, -2, SEEK_CUR) == -1) {
                            return 2;
                        }
                        printf("\033[0m");
                        return 3;
                    } else {
                        if (curr_symb == '\"') {
                            printf("\033[0;32m");
                            printf("%c\"", curr_prefix);
                            state = 1;
                            continue;
                        }
                        if (curr_symb == '8') {
                            curr_symb = getchar();
                            if (curr_symb == '\"') {
                                printf("\033[0;32m");
                                printf("%c8\"", curr_prefix);
                                state = 1;
                                continue;
                            } else {
                                if (fseek(stdin, -2, SEEK_CUR) == -1) {
                                    return 2;
                                }
                                printf("\033[0m");
                                return 3;
                            }
                        }
                    }
                }
            } else {
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                printf("\033[0m");
                return 3;
            }
        }
        if (state == 1) {
            if (curr_symb == '\\') {
                putchar(curr_symb);
                state = 1;
                continue;
            } else if (curr_symb == '\"') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            } else if (curr_symb == '\n') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            } else {
                putchar(curr_symb);
                state = 2;
                continue;
            }
        }
        if (state == 2) {
            if (curr_symb == '\\') {
                putchar(curr_symb);
                state = 2;
                continue;
            } else if (curr_symb == '\"') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            } else {
                putchar(curr_symb);
                state = 1;
                continue;
            }
        }
    }
    printf("\033[0m");
    return 1;
}

int
char_consts_colorer(int color) {
    int curr_symb;
    int state = 0;
    while ((curr_symb = getchar()) != EOF) {
        if (state == 0) {
            if (curr_symb == '\'') {
                printf("\033[1;33m");
                putchar(curr_symb);
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                curr_symb = getchar();
                if (curr_symb == '\'') {
                    printf("\033[1;33m");
                    printf("%c\'", curr_prefix);
                    state = 1;
                    continue;
                } else {
                    if (fseek(stdin, -2, SEEK_CUR) == -1) {
                        return 2;
                    }
                    return 3;
                }
            } else {
                if (fseek(stdin, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                return 3;
            }
        }
        if (state == 1) {
            if (curr_symb == '\\') {
                state = 2;
                continue;
            } else if (curr_symb == '\'') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            } else if (curr_symb == '\n') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            } else {
                putchar(curr_symb);
                state = 1;
                continue;
            }
        }
        if (state == 2) {
            if (curr_symb == '\\') {
                putchar(curr_symb);
                state = 2;
                continue;
            } else if (curr_symb == '\'') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            } else {
                putchar(curr_symb);
                state = 1;
                continue;
            }
        }
    }
    return 1;
}