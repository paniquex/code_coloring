#include "coloring.h"
#include "input.h"

 /* COMPONENT-FUNCTIONS BLOCK */

Token *
number_colorer() {
    int curr_symb, is_first_digit = 1;
    size_t buffer_size = 0;
    char *buffer;
    Token *number_token = calloc(1, sizeof(*number_token));
     buffer = calloc(1, sizeof(*buffer));
    while ((curr_symb = fgetc(input_file)) != EOF) {
        buffer_size++;
        if (isdigit(curr_symb)) {
            if (is_first_digit) {
//                printf("\033[1;36m");
                is_first_digit = 0;
            }
//            putchar(curr_symb);
            buffer[buffer_size - 1] = (char) curr_symb;
        } else {
            if (!is_first_digit) {
//                printf("\033[0m");
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    number_token->type = -2;
                    free(buffer);
                    return number_token;
                }
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                number_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(number_token->buffer, buffer, buffer_size);
                free(buffer);
                number_token->type = 3;
                number_token->amount_in_text++;
                return number_token;
            }
            if (fseek(input_file, -1, SEEK_CUR) == -1) {
                number_token->type = -2;
                free(buffer);
                return number_token;
            }
            number_token->type = -3;
            free(buffer);
            return number_token;
        }
    }
    number_token->type = -1;
    free(buffer);
    return number_token;
}


Token *
comment_colorer() {
    int curr_symb;
    int state1 = 0, state2 = 0;
    size_t buffer_size = 0;
    char *buffer = calloc(1, sizeof(buffer));
    Token *comment_token = calloc(1, sizeof(*comment_token));
    while ((curr_symb = fgetc(input_file)) != EOF) {
        buffer_size++;
        if ((curr_symb == '/') && (state1 == 0)) {
            state1 = 1;
            state2 = 1;
            continue;
        } else if ((state1 == 0) && (state2 == 0)) {
            if (fseek(input_file, -1, SEEK_CUR) == -1) {
                comment_token->type = -2;
                free(buffer);
                return comment_token;
            }
            comment_token->type = -3;
            free(buffer);
            return comment_token;
        }
        if ((state1 == 1) || (state2 == 1)) {
            if ((curr_symb != '/') && (curr_symb != '*')) {
                state1 = 0;
                state2 = 0;
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    comment_token->type = -2;
                    free(buffer);
                    return comment_token;
                }
                comment_token->type = -3;
                free(buffer);
                return comment_token;
            }
            else {
//                printf("\033[4;33m");
                if (curr_symb == '/') {
                    state1 = 2;
                    state2 = 0;
                    buffer = realloc(buffer, buffer_size);
                    buffer[buffer_size - 2] = '/';
                    buffer[buffer_size - 1] = '/';
//                    printf("//");
                }
                else {
                    state1 = 0;
                    state2 = 2;
                    buffer = realloc(buffer, buffer_size);
                    buffer[buffer_size - 2] = '/';
                    buffer[buffer_size - 1] = '*';
//                    printf("/*");
                }
            }
            continue;
        }

        if (state1 == 2) {
            if (curr_symb == '\n') {
                state1 = 0;
//                printf("\033[0m");
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    comment_token->type = -2;
                    free(buffer);
                    return comment_token;
                }
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                comment_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(comment_token->buffer, buffer, buffer_size);
                free(buffer);
                comment_token->type = 7;
                comment_token->amount_in_text++;
                return comment_token;
            } else if (curr_symb == '\\') {
                state1 = 3;
            } else {
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = (char) curr_symb;
//                putchar(curr_symb);
            }
            continue;
        }
        if (state2 == 2) {
            if (curr_symb == '*') {
                state2 = 3;
                state1 = -1;
            }
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
//            putchar(curr_symb);
            continue;
        }
        if (state1 == 3) {
            state1 = 2;
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
//            putchar(curr_symb);
            continue;
        }
        if (state2 == 3) {
            if (curr_symb == '/') {
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = '/';
//                printf("/");
//                printf("\033[0m");
                state2 = 0;
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                comment_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(comment_token->buffer, buffer, buffer_size);
                free(buffer);
                comment_token->type = 7;
                comment_token->amount_in_text++;
                free(buffer);
                return comment_token;
            }
            if (curr_symb != '*') {
                state2 = 2;
            }
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
//            putchar(curr_symb);
            continue;
        }
        if (fseek(input_file, -1, SEEK_CUR) == -1) {
            comment_token->type = -2;
            free(buffer);
            return comment_token;
        }
        buffer_size++;
        buffer = realloc(buffer, buffer_size);
        buffer[buffer_size-1] = '\0';
        comment_token->buffer = calloc(buffer_size, sizeof(char));
        strncpy(comment_token->buffer, buffer, buffer_size);
        free(buffer);
        comment_token->type = 7;
        comment_token->amount_in_text++;
        free(buffer);
        return comment_token;
//        printf("\033[0m");
    }
//    printf("\033[0m");
    comment_token->type = -1;
    free(buffer);
    return comment_token;
}


int
punctuator_colorer(char **PUNCTUATORS, int punctuator_max_length) {
    short int indexes[PUNCTUATORS_AMOUNT];          /* 1, if start of punctuator matches with KEYWORDS i-th row
                                                    0, else*/
    for (int i=0; i < PUNCTUATORS_AMOUNT; i++) {
        indexes[i] = 1;
    }
    int punctuator_to_print[punctuator_max_length];
    for (int i=0; i < punctuator_max_length; i++) {
        punctuator_to_print[i] = 0;
    }
    int curr_symb;
    char is_first_punctuator = 1;
    char is_at_least_one_full_punctuator = 0;
    char was_printed = 0; // if on symb_was_read-step one symbol of punctuator was printed
    int amount_symb_was_read = 0;
    int length_of_current_punctuator = 0;
    int is_indexes_array_of_zeros = 0;
    for (amount_symb_was_read; amount_symb_was_read < punctuator_max_length; amount_symb_was_read++) {
        is_indexes_array_of_zeros = 1; // for check if there is at least one 1
        for (int i = 0; i < PUNCTUATORS_AMOUNT; i++) {
            if (indexes[i] != 0) {
                is_indexes_array_of_zeros = 0;
            }
        }
        if (is_indexes_array_of_zeros) {
            printf("\033[0m");
            if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        }
        was_printed = 0;
        if ((curr_symb = fgetc(input_file)) == EOF) {
            if (is_at_least_one_full_punctuator) {
                for (int i = 0; i < length_of_current_punctuator; i++) {
                    printf("%c", punctuator_to_print[i]);
                }
            } else {
                printf("\033[0m");
            }
            if (fseek(input_file, -amount_symb_was_read + length_of_current_punctuator, SEEK_CUR) == -1) {
                return 2;
            }
            if (!is_first_punctuator) printf("\033[0m");
            return 1;
        }
        for (int i=0; i < PUNCTUATORS_AMOUNT; i++) {
            int curr_length = strlen(PUNCTUATORS[i]);
            if ((PUNCTUATORS[i][amount_symb_was_read] == curr_symb) && (curr_length >= amount_symb_was_read) && (indexes[i] == 1)) {
                if ((amount_symb_was_read == 0) && (is_first_punctuator)) {
                    is_first_punctuator = 0;
                    printf("\033[0;31m");
                }
                if (!was_printed) {
                    punctuator_to_print[length_of_current_punctuator] = curr_symb;
                    length_of_current_punctuator++;
                    was_printed = 1;
                }
            } else {
                if ((is_white_space(curr_symb)) && (curr_length >= amount_symb_was_read) && (indexes[i] != 0)) {
                    for (int k = 0; k < length_of_current_punctuator; k++) {
                        putchar(punctuator_to_print[k]);
                    }
                    if (fseek(input_file, -1, SEEK_CUR) == -1) {
                        return 2;
                    }
                    if (!is_first_punctuator) printf("\033[0m");
                    return 0;
                } else if ((curr_length == amount_symb_was_read) && (indexes[i] != 0)) {
                    printf("%s", PUNCTUATORS[i]);
                    if (!is_first_punctuator) printf("\033[0m");
                    if (fseek(input_file, -1, SEEK_CUR) == -1) {
                        return 2;
                    }
                    return 0;
                }
                indexes[i] = 0;
            }
        }
    }
    if (fseek(input_file, -amount_symb_was_read + length_of_current_punctuator, SEEK_CUR) == -1) {
        return 2;
    }
    return 0;
}


int
keyword_colorer(char **KEYWORDS, int keyword_max_length) {
    short int indexes[KEYWORDS_AMOUNT];          /* 1, if start of keyword matches with KEYWORDS i-th row
                                                    0, else*/
    for (int i=0; i < KEYWORDS_AMOUNT; i++) {
        indexes[i] = 1;
    }
    int keyword_to_print[keyword_max_length];
    for (int i=0; i < keyword_max_length; i++) {
        keyword_to_print[i] = 0;
    }
    int curr_symb;
    char is_first_keyword = 1;
    char is_at_least_one_full_keyword = 0;
    char was_printed = 0; // if on symb_was_read-step one symbol of keyword was printed
    int amount_symb_was_read = 0;
    int length_of_current_keyword = 0;
    int is_indexes_array_of_zeros = 0;
    for (amount_symb_was_read; amount_symb_was_read < keyword_max_length; amount_symb_was_read++) {
        is_indexes_array_of_zeros = 1; // for check if there is at leats one 1
        for (int i = 0; i < KEYWORDS_AMOUNT; i++) {
            if (indexes[i] != 0) {
                is_indexes_array_of_zeros = 0;
            }
        }
        if (is_indexes_array_of_zeros) {
            printf("\033[0m");
            if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        }
        was_printed = 0;
        if ((curr_symb = fgetc(input_file)) == EOF) {
            if (is_at_least_one_full_keyword) {
                for (int i = 0; i < length_of_current_keyword; i++) {
                    printf("%c", keyword_to_print[i]);
                }
            } else {
                printf("\033[0m");
            }
            if (fseek(input_file, -amount_symb_was_read + length_of_current_keyword, SEEK_CUR) == -1) {
                return 2;
            }
            if (!is_first_keyword) printf("\033[0m");
            return 1;
        }
        for (int i=0; i < KEYWORDS_AMOUNT; i++) {
            int curr_length = strlen(KEYWORDS[i]);
            if ((KEYWORDS[i][amount_symb_was_read] == curr_symb) && (curr_length >= amount_symb_was_read) && (indexes[i] == 1)) {
                if ((amount_symb_was_read == 0) && (is_first_keyword)) {
                    is_first_keyword = 0;
                    printf("\033[0;34m");
                }
                if (!was_printed) {
                    keyword_to_print[length_of_current_keyword] = curr_symb;
                    length_of_current_keyword++;
                    was_printed = 1;
                }
            } else {
                if ((is_white_space(curr_symb)) && (curr_length >= amount_symb_was_read) && (indexes[i] != 0)) {
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
    if (fseek(input_file, -amount_symb_was_read + length_of_current_keyword, SEEK_CUR) == -1) {
        return 2;
    }
    return 0;
}




Token *
identifier_colorer() {
    int curr_symb;
    int amount_symb_was_read = 0;
    int state1 = 0;
    Token *identifier_token = calloc(1, sizeof(*identifier_token));
    char *buffer = calloc(1, sizeof(*buffer));
    while ((curr_symb = fgetc(input_file)) != EOF) {
        amount_symb_was_read++;
        if (state1 == 0) {
            if (is_nondigit(curr_symb)) {
                state1 = 1;
                continue;
            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    identifier_token->type = -2;
                    return identifier_token;
                }
                identifier_token->type = -3;
                free(buffer);
                return identifier_token;
            }
        }
        if (state1 == 1) {
            if ((is_nondigit(curr_symb)) || (isdigit(curr_symb)))  {

            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    identifier_token->type = -2;
                    free(buffer);
                    return identifier_token;
                }
//                printf("\033[0;95m");
                identifier_token->buffer = calloc(amount_symb_was_read, sizeof(char));
                identifier_token->type = 2;
                for(int i = 0; i < amount_symb_was_read-1; i++) {
                    identifier_token->buffer[i] = (char) fgetc(input_file);
                }
//                printf("\033[0m");
                free(buffer);
                return identifier_token;
            }
        }
    }
    if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
        identifier_token->type = -2;
        free(buffer);
        return identifier_token;
    }
    if (state1 == 1) {
        identifier_token->buffer = calloc(amount_symb_was_read, sizeof(char));
        identifier_token->type = 2;
        for (int i = 0; i < amount_symb_was_read; i++) {
//            printf("\033[0;95m");
//            putchar(fgetc(input_file));
//            printf("\033[0m");
            identifier_token->buffer[i] = (char) fgetc(input_file);
        }
        free(buffer);
        return identifier_token;
    }
    identifier_token->type = -1;
    free(buffer);
    return identifier_token;
}


int
is_hexadecimal_digit(int symb) {
    enum {HEXADECIMAL_DIGITS_AMOUNT = 22};
    const char HEXADECIMAL_DIGITS[HEXADECIMAL_DIGITS_AMOUNT] = {
            '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', 'a',
            'b', 'c', 'd', 'e', 'f', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    for (int i=0; i < HEXADECIMAL_DIGITS_AMOUNT; i++) {
        if (symb == HEXADECIMAL_DIGITS[i]) {
            return 1;
        }
    }
    return 0;
}


int
ucn_colorer() {
    int curr_symb;
    int amount_symb_was_read = 0;
    int print_u_or_U = 'u'; // if 'u' - print u, if 1 - print 'U'
    int state1 = 0;
    while ((curr_symb = fgetc(input_file)) != EOF) {
        amount_symb_was_read++;
        if (state1 == 0) {
            if (curr_symb == '\\') {
                state1 = 1;
                continue;
            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    return 2;
                }
                return 3;
            }
        }
        if (state1 == 1) {
            if (curr_symb == 'u') {
                print_u_or_U = 'u';
                state1 = 2;
                continue;
            }
            if (curr_symb == 'U') {
                print_u_or_U = 1;
                state1 = 2;
                continue;
            }
            if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                return 2;
            }
            return 3;
        }
        if (state1 == 2) {
            if (is_hexadecimal_digit(curr_symb)) {
                printf("\033[0;95m");
                putchar('\\');
                putchar(print_u_or_U);
                putchar(curr_symb);
                state1 = 3;
                continue;
            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    return 2;
                }
                return 3;
            }
        }
        if (state1 == 3) {
            if (is_hexadecimal_digit(curr_symb)) {
                putchar(curr_symb);
            } else {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                return 0;
            }
        }
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
    if ((curr_symb = fgetc(input_file)) != EOF) {
        if (!is_white_space(curr_symb)) {
            if (fseek(input_file, -1, SEEK_CUR) == -1) {
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
string_literal_colorer() {
    int curr_symb;
    int state = 0;
    while ((curr_symb = fgetc(input_file)) != EOF) {
        if (state == 0) {
            if (curr_symb == '\"') {
                printf("\033[0;32m");
                putchar(curr_symb);
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                if ((curr_symb == 'L') || (curr_symb == 'U')) {
                    curr_symb = fgetc(input_file);
                    if (curr_symb != '\"') {
                        if (fseek(input_file, -2, SEEK_CUR) == -1) {
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
                    curr_symb = fgetc(input_file);
                    if ((curr_symb != '8') && (curr_symb != '\"')) {
                        if (fseek(input_file, -2, SEEK_CUR) == -1) {
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
                            curr_symb = fgetc(input_file);
                            if (curr_symb == '\"') {
                                printf("\033[0;32m");
                                printf("%c8\"", curr_prefix);
                                state = 1;
                                continue;
                            } else {
                                if (fseek(input_file, -2, SEEK_CUR) == -1) {
                                    return 2;
                                }
                                printf("\033[0m");
                                return 3;
                            }
                        }
                    }
                }
            } else {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                printf("\033[0m");
                return 3;
            }
        }
        if (state == 1) {
            if (curr_symb == '\\') {
                putchar(curr_symb);
                state = 2;
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
            }
            else if (curr_symb == '\n') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            }
            else {
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
char_consts_colorer() {
    int curr_symb;
    int state = 0;
    while ((curr_symb = fgetc(input_file)) != EOF) {
        if (state == 0) {
            if (curr_symb == '\'') {
                printf("\033[1;33m");
                putchar(curr_symb);
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                curr_symb = fgetc(input_file);
                if (curr_symb == '\'') {
                    printf("\033[1;33m");
                    printf("%c\'", curr_prefix);
                    state = 1;
                    continue;
                } else {
                    if (fseek(input_file, -2, SEEK_CUR) == -1) {
                        return 2;
                    }
                    return 3;
                }
            } else {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    return 2;
                }
                return 3;
            }
        }
        if (state == 1) {
            if (curr_symb == '\\') {
                putchar(curr_symb);
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
                state = 2;
                continue;
            }
        }
        if (state == 2) {
            if (curr_symb == '\\') {
                putchar(curr_symb);
                state = 2;
                continue;
            }
            else if (curr_symb == '\n') {
                putchar(curr_symb);
                printf("\033[0m");
                return 0;
            }
            else {
                putchar(curr_symb);
                state = 1;
                continue;
            }
        }
    }
    return 1;
}



int
coloring_stage(char **punctuators, int punctuator_max_length, char **keywords, int keyword_max_length) {
    int flag;
    int symb;
    Token *current_token;
    while (fgetc(input_file) != EOF) {
        if (fseek(input_file, -1, SEEK_CUR) == -1) {
            perror("fseek error: ");
            return 2;
        }
        while (white_space_print_skip() == 0);
        if (white_space_print_skip() == 1) {
            break;
        }

//        current_token = comment_colorer();
//        if (current_token->type == 7) {
//            printf("%s", current_token->buffer);
//            free(current_token->buffer);
//            free(current_token);
//            continue;
//        } else if (current_token->type == -2) {
//            perror("***Comment colorer***");
//            return 2;
//        }
//        if (current_token != NULL) {
//            free(current_token);
//        }
//
//        flag = string_literal_colorer();
//        if (flag == 0) {
//            continue;
//        } else if (flag == 2) {
//            perror("***String literal colorer***");
//            return 2;
//        }
//
//        flag = char_consts_colorer();
//        if (flag == 0) {
//            continue;
//        } else if (flag == 2) {
//            perror("***Char consts colorer***");
//            return 2;
//        }
//
//        flag = keyword_colorer(keywords, keyword_max_length);
//        if (flag == 0) {
//            continue;
//        } else if (flag == 2) {
//            perror("***Keyword colorer***");
//            return 2;
//        }
//
//        flag = ucn_colorer();
//        if (flag == 0) {
//            continue;
//        } else if (flag == 2) {
//            perror("***Ucn colorer***");
//            return 2;
//        }
//
        current_token = identifier_colorer();
        if (current_token->type == 2) {
            printf("%s", current_token->buffer);
            fflush(stdin);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            perror("***Identifier colorer***");
            return 2;
        }
        if (current_token != NULL) {
            free(current_token);
        }

//        current_token = number_colorer();
//        if (current_token->type == 3) {
//            printf("%s", current_token->buffer);
//            fflush(stdin);
//            free(current_token->buffer);
//            free(current_token);
//            continue;
//        } else if (current_token->type == -2) {
//            perror("***Number colorer***");
//            return 2;
//        }
//        if (current_token != NULL) {
//            free(current_token);
//        }
//
//        flag = punctuator_colorer(punctuators, punctuator_max_length);
//        if (flag == 0) {
//            continue;
//        } else if (flag == 2) {
//            perror("***Punctuator colorer***");
//            return 2;
//        }
        /* if not of the 7 patterns, then print without color */
        if ((symb = fgetc(input_file)) <= 0) {
            perror("getchar error: ");
            return 1;
        }
        putchar(symb);
    }
    return 0;
}


char **
keywords_array_init(int *keyword_max_length) {
    char *keywords_arr[KEYWORDS_AMOUNT] =
            {
                    "unsigned",
                    "void",
                    "volatile",
                    "while",
                    "_Alignas",
                    "_Alignof",
                    "_Atomic",
                    "_Bool",
                    "_Complex",
                    "_Generic",
                    "_Imaginary",
                    "_Noreturn",
                    "_Static_assert",
                    "_Thread_local"
            };
    *keyword_max_length = -1;
    int symbols_amount_in_keywords = 0;
    int curr_length = 0;
    for (int i = 0; i < KEYWORDS_AMOUNT; i++) {
        curr_length = strlen(keywords_arr[i]);
        symbols_amount_in_keywords += curr_length;
        if (curr_length > *keyword_max_length) {
            *keyword_max_length = curr_length;
        }
    }
    char **keywords;
    keywords = calloc(symbols_amount_in_keywords + KEYWORDS_AMOUNT, sizeof(char));
    for (int i = 0; i < KEYWORDS_AMOUNT; i++) {
        keywords[i] = keywords_arr[i];
    }
    return keywords;
}



char **
punctuators_array_init(int *punctuator_max_length) {
    char *punctuators_arr[PUNCTUATORS_AMOUNT] =
            {
                    "--",
                    "&",
                    "*",
                    "+",
                    "++",
                    "-",
                    "~",
                    "!",
                    "/",
                    "%",
                    "<<",
                    ">>",
                    "<",
                    ">",
                    "<=",
                    ">=",
                    "==",
                    "!=",
                    "^",
                    "|",
                    "&&",
                    "||",
                    "=",
                    "*=",
                    "/=",
                    "%=",
                    "+=",
                    "-=",
                    "<<=",
                    ">>=",
                    "&=",
                    "^=",
                    "|="
            };
    *punctuator_max_length = -1;
    int symbols_amount_in_punctuators = 0;
    int curr_length = 0;
    for (int i = 0; i < PUNCTUATORS_AMOUNT; i++) {
        curr_length = strlen(punctuators_arr[i]);
        symbols_amount_in_punctuators += curr_length;
        if (curr_length > *punctuator_max_length) {
            *punctuator_max_length = curr_length;
        }
    }
    char **punctuators;
    punctuators = calloc(symbols_amount_in_punctuators + PUNCTUATORS_AMOUNT, sizeof(int));
    if (punctuators == NULL) {
        perror("Punc init");
    }
    for (int i = 0; i < PUNCTUATORS_AMOUNT; i++) {
        punctuators[i] = punctuators_arr[i];
    }
    return punctuators;
}