#include "analysing.h"
#include "input.h"
#include "coloring.h"
#include "output.h"
#include "token_processing.h"
#include "counting.h"

 /* COMPONENT-FUNCTIONS BLOCK */

 static int
 is_white_space(int symb) {
     /* DESCRIPTION:
  * is_white_space() checks symb, if it is white_space character or not
  * RETURN VALUES:
     * 0, if it is not white_space
     * 1  else
 */
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

static int
is_nondigit(int symb) {
    /*
* RETURN VALUES:
   * 1, if symb is nondigit
   * 0, else
*/
    if ((isalpha(symb)) || (symb == '_')) return 1;
    else return 0;
}


static char **
keywords_array_init(int *keyword_max_length) {
/* DESCRIPTION:
    * keywords_array_init takes pointer to int and changes it to
    * max length of keywords
 * RETURN VALUES:
    * pointer to array of keywords
    * NULL, if somekind of error was found
 */

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


static char **
punctuators_array_init(int *punctuator_max_length) {
    /* DESCRIPTION:
   * punctuator_array_init takes pointer to int and changes it to
   * max length of punctuators
* RETURN VALUES:
   * pointer to array of punctuators
   * NULL, if somekind of error was found
*/

    char *punctuators_arr[PUNCTUATORS_AMOUNT] =
            {
                    "<",
                    "<<",
                    "<=",
                    "<<=",
                    ">",
                    ">>",
                    ">=",
                    ">>=",
                    "=",
                    "==",
                    "|",
                    "||",
                    "|=",
                    "&",
                    "&&",
                    "&=",
                    "!",
                    "!=",
                    "*",
                    "*=",
                    "+",
                    "++",
                    "+=",
                    "^",
                    "^=",
                    "/",
                    "/=",
                    "%",
                    "%=",
                    "-",
                    "--",
                    "-=",
                    "~",
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


static Token *
number_analyser() {
    /*
 * DESCRIPTION:
 * number_analyser() attempts to read symbols from stdin until EOF
 * if first digit has reached, then saves it in Token->buffer, and changes Token->type
 * after first digit was found, if current symbol != digit, then saves it in Token->buffer, and changes Token->type
 * "standard color key".
 * RETURN VALUES:
     * 0 - if digit was found
     * 1 - if EOF was found
     * 2 - if some kind of error was found
     * 3 - if digit was not found
*/
    char curr_symb, is_first_digit = 1;
    size_t buffer_size = 0;
    Token *number_token = calloc(1, sizeof(*number_token));
    char *buffer = calloc(1, sizeof(*buffer));
    while ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
        buffer_size++;
        if (isdigit(curr_symb)) {
            if (is_first_digit) {
                is_first_digit = 0;
            }
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
        } else {
            if (!is_first_digit) {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    number_token->type = -2;
                    free(buffer);
                    return number_token;
                }
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                number_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(number_token->buffer, buffer, buffer_size);
                number_token->type = 3;
                free(buffer);
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
     buffer_size++;
     buffer = realloc(buffer, buffer_size);
     buffer[buffer_size-1] = '\0';
     number_token->buffer = calloc(buffer_size, sizeof(char));
     strncpy(number_token->buffer, buffer, buffer_size);
     number_token->type = 3;
     free(buffer);
    return number_token;
}


static Token *
comment_analyser() {
    /*
 * DESCRIPTION:
    * comment_analyser() attempts to read symbols from stdin until EOF
    * if it has found "comment token(or pattern)", then saves it in Token->buffer, and changes Token->type
 * RETURN VALUES:
    * 0, if somekind of comment was found
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if comment was not found
*/

    char curr_symb;
    int state1 = 0, state2 = 0;
    size_t buffer_size = 0;
    char *buffer = calloc(1, sizeof(buffer));
    Token *comment_token = calloc(1, sizeof(*comment_token));
    while ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
        buffer_size++;
        if ((curr_symb == '/') && (state1 == 0) && (state2 == 0)) {
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
                if (fseek(input_file, -buffer_size, SEEK_CUR) == -1) {
                    comment_token->type = -2;
                    free(buffer);
                    return comment_token;
                }
                comment_token->type = -3;
                free(buffer);
                return comment_token;
            }
            else {
                if (curr_symb == '/') {
                    state1 = 2;
                    state2 = 0;
                    buffer = realloc(buffer, buffer_size);
                    buffer[buffer_size - 2] = '/';
                    buffer[buffer_size - 1] = '/';
                }
                else {
                    state1 = 0;
                    state2 = 2;
                    buffer = realloc(buffer, buffer_size);
                    buffer[buffer_size - 2] = '/';
                    buffer[buffer_size - 1] = '*';
                }
            }
            continue;
        }

        if (state1 == 2) {
            if (curr_symb == '\n') {
                state1 = 0;
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    comment_token->type = -2;
                    free(buffer);
                    return comment_token;
                }
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                comment_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(comment_token->buffer, buffer, buffer_size);
                free(buffer);
                comment_token->type = 7;
                return comment_token;
            } else if (curr_symb == '\\') {
                state1 = 3;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = (char) curr_symb;
            } else {
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = (char) curr_symb;
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
            continue;
        }
        if (state1 == 3) {
            state1 = 2;
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
            continue;
        }
        if (state2 == 3) {
            if (curr_symb == '/') {
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = '/';
                state2 = 0;
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                comment_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(comment_token->buffer, buffer, buffer_size);
                comment_token->type = 7;
                free(buffer);
                return comment_token;
            }
            if (curr_symb != '*') {
                state2 = 2;
            }
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
            continue;
        }
        if (fseek(input_file, -1, SEEK_CUR) == -1) {
            comment_token->type = -2;
            free(buffer);
            return comment_token;
        }
        comment_token->type = -3;
        free(buffer);
        return comment_token;
    }
    if (buffer_size == 0) {
        comment_token->type = -3;
        return comment_token;
    }
    if (buffer_size < 2) {
        if (fseek(input_file, -buffer_size, SEEK_CUR) == -1) {
            comment_token->type = -2;
            free(buffer);
            return comment_token;
        }
        comment_token->type = -3;
        free(buffer);
        return comment_token;
    }
    buffer_size++;
    buffer = realloc(buffer, buffer_size);
    buffer[buffer_size-1] = '\0';
    comment_token->buffer = calloc(buffer_size, sizeof(char));
    strncpy(comment_token->buffer, buffer, buffer_size);
    comment_token->type = 7;
    free(buffer);
    return comment_token;
}


static Token *
punctuator_analyser(char **PUNCTUATORS, int punctuator_max_length) {
    /*
 * DESCRIPTION:
    * punctuator_analyser() attempts to read symbols from stdin until EOF
    * it uses PUNCTUATORS array, which contains all available pattern of punctuators
    * if it has found "punctuator token(or pattern)" then saved it in Token->buffer, and changes Token->type
 * RETURN VALUES:
     * 0, if punctuator was found and printed
     * 1, if EOF was reached
     * 2, if somekind of error was found
     * 3, if no punctuator was found
*/
    size_t buffer_size = 0;
    char *buffer = calloc(punctuator_max_length, sizeof(buffer));
    Token *punctuator_token = calloc(1, sizeof(*punctuator_token));
    buffer_size = fread(buffer, sizeof(char), punctuator_max_length, input_file);
    if (buffer_size == 0) {
        punctuator_token->type = -3;
        free(buffer);
        if (fseek(input_file, -buffer_size, SEEK_CUR) == -1) {
            punctuator_token->type = -2;
            return punctuator_token;
        }
        return punctuator_token;
    }
    int punctuator_curr_length = buffer_size;
    for (int i = 0; i < punctuator_curr_length; i++) {
        for (int k = 0; k < PUNCTUATORS_AMOUNT; k++) {
            if (strncmp(PUNCTUATORS[k], buffer, (size_t) punctuator_curr_length - i) == 0) {
                buffer_size = punctuator_curr_length - i;
                if (fseek(input_file, -punctuator_curr_length + buffer_size, SEEK_CUR) == -1) {
                    punctuator_token->type = -2;
                    return punctuator_token;
                }
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = '\0';
                punctuator_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(punctuator_token->buffer, buffer, buffer_size);
                punctuator_token->type = 6;
                free(buffer);
                return punctuator_token;
            }
        }
    }
        punctuator_token->type = -3;
        free(buffer);
        if (fseek(input_file, -buffer_size, SEEK_CUR) == -1) {
            punctuator_token->type = -2;
            return punctuator_token;
        }
        return punctuator_token;
}


static Token *
keyword_analyser(char **KEYWORDS, int keyword_max_length) {
    /* DESCRIPTION:
    * keyword_analyser() attempts to read symbols from stdin until EOF
    * it uses KEYWORDS array, which contains all available pattern of punctuators
    * if it has found "keyword token(or pattern)" then saves it in Token->buffer, and changes Token->type
 * RETURN VALUES:
     * 0, if keyword was found and printed
     * 1, if EOF was reached
     * 2, if somekind of error was found
     * 3, if no keyword was found
  Important:
    * at the end of keyword must be at least one white space, if keyword ends without white spaces - don't print
  EXAMPLE:
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
    int keyword_to_print[keyword_max_length];
    for (int i=0; i < keyword_max_length; i++) {
        keyword_to_print[i] = 0;
    }
    char curr_symb;
    char is_first_keyword = 1;
    char is_at_least_one_full_keyword = 0;
    char was_printed = 0; // if on symb_was_read-step one symbol of keyword was printed
    int amount_symb_was_read = 0;
    int length_of_current_keyword = 0;
    int is_indexes_array_of_zeros = 0;
    size_t buffer_size = 0;
    char *buffer = calloc(1, sizeof(buffer));
    Token *keyword_token = calloc(1, sizeof(*keyword_token));
    for (; amount_symb_was_read < keyword_max_length + 1; amount_symb_was_read++) {
        is_indexes_array_of_zeros = 1; // for check if there is at leats one 1
        for (int i = 0; i < KEYWORDS_AMOUNT; i++) {
            if (indexes[i] != 0) {
                is_indexes_array_of_zeros = 0;
            }
        }
        if (is_indexes_array_of_zeros) {
            if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                keyword_token->type = -2;
                free(buffer);
                return keyword_token;
            }
            keyword_token->type = -3;
            free(buffer);
            return keyword_token;
        }
        was_printed = 0;
        if ((fread(&curr_symb, 1, sizeof(char), input_file)) == 0) {
            if (is_at_least_one_full_keyword) {
                buffer_size = length_of_current_keyword;
                buffer = realloc(buffer, length_of_current_keyword);
                for (int i = 0; i < length_of_current_keyword; i++) {
                    buffer[i] = (char) keyword_to_print[i];
                }
            } else {

            }
            if (fseek(input_file, -amount_symb_was_read + length_of_current_keyword, SEEK_CUR) == -1) {
                keyword_token->type = -2;
                free(buffer);
                return keyword_token;
            }
            buffer_size++;
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size-1] = '\0';
            keyword_token->buffer = calloc(buffer_size, sizeof(char));
            strncpy(keyword_token->buffer, buffer, buffer_size);
            keyword_token->type = 1;
            free(buffer);
            return keyword_token;
        }
        for (int i=0; i < KEYWORDS_AMOUNT; i++) {
            int curr_length = strlen(KEYWORDS[i]);
            if ((KEYWORDS[i][amount_symb_was_read] == curr_symb) && (curr_length >= amount_symb_was_read) && (indexes[i] == 1)) {
                if ((amount_symb_was_read == 0) && (is_first_keyword)) {
                    is_first_keyword = 0;
                }
                if (strlen(KEYWORDS[i]) == (amount_symb_was_read + 1)) {
                    is_at_least_one_full_keyword = 1;
                }
                if (!was_printed) {
                    keyword_to_print[length_of_current_keyword] = curr_symb;
                    length_of_current_keyword++;
                    was_printed = 1;
                }
            } else {
                if ((is_white_space(curr_symb)) && (curr_length >= amount_symb_was_read) && (indexes[i] != 0)) {
                    buffer_size = length_of_current_keyword;
                    buffer = realloc(buffer, buffer_size);
                    for (int k = 0; k < length_of_current_keyword; k++) {
                        buffer[k] = (char) keyword_to_print[k];
                    }
                    if (fseek(input_file, -1, SEEK_CUR) == -1) {
                        keyword_token->type = -2;
                        free(buffer);
                        return keyword_token;
                    }
                    buffer_size++;
                    buffer = realloc(buffer, buffer_size);
                    buffer[buffer_size-1] = '\0';
                    keyword_token->buffer = calloc(buffer_size, sizeof(char));
                    strncpy(keyword_token->buffer, buffer, buffer_size);
                    keyword_token->type = 1;
                    free(buffer);
                    return keyword_token;
                }
                indexes[i] = 0;
            }
        }
    }
    if (fseek(input_file, -amount_symb_was_read + length_of_current_keyword, SEEK_CUR) == -1) {
        keyword_token->type = -2;
        free(buffer);
        return keyword_token;
    }
    if (buffer_size == 0) {
        keyword_token->type = -3;
        free(buffer);
        return keyword_token;
    }
    return NULL;
}




static Token *
identifier_analyser() {
    /* DESCRIPTION:
 * identifier_analyser() attempts to read symbols from stdin until EOF
 * if it has found "identifier token(or pattern)" then saves it in Token->buffer, and changes Token->type
 *
 * RETURN VALUES:
    * 0, if identifier was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no identifier was found
*/

    char curr_symb;
    int amount_symb_was_read = 0;
    int state1 = 0;
    Token *identifier_token = calloc(1, sizeof(*identifier_token));
    char *buffer = calloc(1, sizeof(*buffer));
    while ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
        amount_symb_was_read++;
        if (state1 == 0) {
            if (is_nondigit(curr_symb)) {
                state1 = 1;
                continue;
            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    identifier_token->type = -2;
                    free(buffer);
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
                identifier_token->buffer = calloc(amount_symb_was_read, sizeof(char));
                identifier_token->type = 2;
                for(int i = 0; i < amount_symb_was_read-1; i++) {
                    fread(&identifier_token->buffer[i], 1, sizeof(char), input_file);
                }
                identifier_token->buffer[amount_symb_was_read-1] = '\0';
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
        identifier_token->buffer = calloc((size_t) amount_symb_was_read + 1, sizeof(char));
        identifier_token->type = 2;
        for (int i = 0; i < amount_symb_was_read; i++) {
            fread(&identifier_token->buffer[i], 1, sizeof(char), input_file);
        }
        identifier_token->buffer[amount_symb_was_read] = '\0';
        free(buffer);
        return identifier_token;
    }
    if (amount_symb_was_read == 0) {
        identifier_token->type = -3;
        free(buffer);
        return identifier_token;
    }
    free(buffer);
    identifier_token->type = -3;
    return identifier_token;
}


static int
is_hexadecimal_digit(int symb) {
    /* DESCRIPTION:
        * is_hexadecimal_digit checks symb, if it is hexadecimal digit or not
    * RETURN VALUES:
        * 0, if it is not white_space
        * 1,  else
    */
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


static Token *
ucn_analyser() {
    /* DESCRIPTION:
 * ucn_analyser() attempts to read symbols from stdin until EOF
 * if it has found "universal character token(or pattern)" then saves it in Token->buffer, and changes Token->type
 *
 * RETURN VALUES:
    * 0, if Universal character name was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no Universal character name was found
*/
    char curr_symb;
    int amount_symb_was_read = 0;
    int print_u_or_U = 'u'; // if 'u' - print u, if 1 - print 'U'
    int state1 = 0;
    Token *ucn_token = calloc(1, sizeof(*ucn_token));
    char *buffer = calloc(1, sizeof(char));
    while ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
        amount_symb_was_read++;
        if (state1 == 0) {
            if (curr_symb == '\\') {
                state1 = 1;
                continue;
            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    ucn_token->type = -2;
                    free(buffer);
                    return ucn_token;
                }
                ucn_token->type = -3;
                free(buffer);
                return ucn_token;
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
                ucn_token->type = -2;
                free(buffer);
                return ucn_token;
            }
            ucn_token->type = -3;
            free(buffer);
            return ucn_token;
        }
        if (state1 == 2) {
            if (is_hexadecimal_digit(curr_symb)) {
                buffer = realloc(buffer, amount_symb_was_read);
                buffer[amount_symb_was_read - 3] = '\\';
                buffer[amount_symb_was_read - 2] = (char) print_u_or_U;
                buffer[amount_symb_was_read - 1] = curr_symb;
                state1 = 3;
                continue;
            } else {
                if (fseek(input_file, -amount_symb_was_read, SEEK_CUR) == -1) {
                    ucn_token->type = -2;
                    free(buffer);
                    return ucn_token;
                }
                ucn_token->type = -3;
                free(buffer);
                return ucn_token;
            }
        }
        if (state1 == 3) {
            if (is_hexadecimal_digit(curr_symb)) {
                buffer = realloc(buffer, amount_symb_was_read);
                buffer[amount_symb_was_read - 1] = curr_symb;
            } else {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    ucn_token->type = -2;
                    free(buffer);
                    return ucn_token;
                }
                buffer = realloc(buffer, amount_symb_was_read);
                buffer[amount_symb_was_read - 1] = '\0';
                ucn_token->buffer = calloc(amount_symb_was_read, sizeof(char));
                strncpy(ucn_token->buffer, buffer, amount_symb_was_read);
                ucn_token->type = 8;
                free(buffer);
                return ucn_token;
            }
        }
    }
    amount_symb_was_read++;
    buffer = realloc(buffer, amount_symb_was_read);
    buffer[amount_symb_was_read - 1] = '\0';
    ucn_token->buffer = calloc((size_t) amount_symb_was_read, sizeof(char));
    strncpy(ucn_token->buffer, buffer, amount_symb_was_read);
    ucn_token->type = -3;
    free(buffer);
    return ucn_token;
}


static int
white_space_print_skip() {
    /* DESCRIPTION:
 * white_space_print_skip() attempts to read one symbol from stdin
 * and checks if it is white_space character, then prints it
 * RETURN VALUES:
    * 0, if this symb is white_space
    * 1, if EOF
    * 2, if some kind of error was found
    * 3, if symb is not white_space
*/
    /* 0, if this symb is white_space
     * 1, if EOF
     * 2, if some kind of error was found
     * 3, if symb is not white_space*/
    char curr_symb;
    if ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
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



static Token *
string_literal_analyser() {
    /* DESCRIPTION:
    * string_literal_analyser() attempts to read symbols from stdin until EOF
    * if it has found "string_literal token(or pattern)" then saves it in Token->buffer, and changes Token->type
 * RETURN VALUES:
    * 0, if string_literal was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no string_literal was found
 * */

    char curr_symb;
    int state = 0;
    size_t buffer_size = 0;
    Token *string_literal_token = calloc(1, sizeof(*string_literal_token));
    char *buffer = calloc(1, sizeof(*buffer));
    while ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
        buffer_size++;
        if (state == 0) {
            if (curr_symb == '\"') {
                buffer[buffer_size - 1] = (char) curr_symb;

                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                if ((curr_symb == 'L') || (curr_symb == 'U')) {
                    fread(&curr_symb, 1, sizeof(char), input_file);
                    buffer_size++;
                    if (curr_symb != '\"') {
                        if (fseek(input_file, -2, SEEK_CUR) == -1) {
                            string_literal_token->type = -2;
                            free(buffer);
                            return string_literal_token;
                        }
                        string_literal_token->type = -3;
                        free(buffer);
                        return string_literal_token;
                    } else {
                        buffer = realloc(buffer, buffer_size);
                        buffer[buffer_size - 2] = (char) curr_prefix;
                        buffer[buffer_size - 1] = '\"';
                        state = 1;
                        continue;
                    }
                } else { //curr_symb == u
                    fread(&curr_symb, 1, sizeof(char), input_file);
                    buffer_size++;
                    if ((curr_symb != '8') && (curr_symb != '\"')) {
                        if (fseek(input_file, -2, SEEK_CUR) == -1) {
                            string_literal_token->type = -2;
                            free(buffer);
                            return string_literal_token;
                        }
                        string_literal_token->type = -3;
                        free(buffer);
                        return string_literal_token;
                    } else {
                        if (curr_symb == '\"') {
                            buffer = realloc(buffer, buffer_size);
                            buffer[buffer_size - 2] = (char) curr_prefix;
                            buffer[buffer_size - 1] = '\"';
                            state = 1;
                            continue;
                        }
                        if (curr_symb == '8') {
                            fread(&curr_symb, 1, sizeof(char), input_file);
                            buffer_size++;
                            if (curr_symb == '\"') {
                                buffer = realloc(buffer, buffer_size);
                                buffer[buffer_size - 3] = (char) curr_prefix;
                                buffer[buffer_size - 2] = '8';
                                buffer[buffer_size - 1] = '\"';
                                state = 1;
                                continue;
                            } else {
                                if (fseek(input_file, -buffer_size, SEEK_CUR) == -1) {
                                    string_literal_token->type = -2;
                                    free(buffer);
                                    return string_literal_token;
                                }
                                string_literal_token->type = -3;
                                free(buffer);
                                return string_literal_token;
                            }
                        }
                    }
                }
            } else {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    string_literal_token->type = -2;
                    free(buffer);
                    return string_literal_token;
                }
                string_literal_token->type = -3;
                free(buffer);
                return string_literal_token;
            }
        }
        if (state == 1) {
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            } else if (curr_symb == '\"') {
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                string_literal_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(string_literal_token->buffer, buffer, buffer_size);
                string_literal_token->type = 5;
                free(buffer);
                return string_literal_token;
            } else if (curr_symb == '\n') {
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                string_literal_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(string_literal_token->buffer, buffer, buffer_size);
                string_literal_token->type = 5;
                free(buffer);
                return string_literal_token;
            } else {
                state = 1;
                continue;
            }
        }
        if (state == 2) {
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            }
            else if (curr_symb == '\n') {
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                string_literal_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(string_literal_token->buffer, buffer, buffer_size);
                string_literal_token->type = 5;
                free(buffer);
                return string_literal_token;
            }
            else {
                state = 1;
                continue;
            }
        }
    }
    string_literal_token->type = 5;
    buffer_size++;
    buffer = realloc(buffer, buffer_size);
    buffer[buffer_size-1] = '\0';
    string_literal_token->buffer = calloc(buffer_size, sizeof(char));
    strncpy(string_literal_token->buffer, buffer, buffer_size);
    free(buffer);
    return string_literal_token;
}

static Token *
char_consts_analyser() {
    /* DESCRIPTION:
   * char_consts_analyser() attempts to read symbols from stdin until EOF
   * if it has found "char_consts token(or pattern)" then saves it in Token->buffer, and changes Token->type
* RETURN VALUES:
   * 0, if char_consts was found and printed
   * 1, if EOF was reached
   * 2, if somekind of error was found
   * 3, if no char_consts was found
* */
    char curr_symb;
    int state = 0;
    size_t buffer_size = 0;
    Token *char_consts_token = calloc(1, sizeof(*char_consts_token));
    char *buffer = calloc(1, sizeof(*buffer));
    while ((fread(&curr_symb, 1, sizeof(char), input_file)) > 0) {
        buffer_size++;
        if (state == 0) {
            if (curr_symb == '\'') {
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size - 1] = (char) curr_symb;
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                fread(&curr_symb, 1, sizeof(char), input_file);
                buffer_size++;
                if (curr_symb == '\'') {
                    buffer = realloc(buffer, buffer_size);
                    buffer[buffer_size - 2] = (char) curr_prefix;
                    buffer[buffer_size - 1] = '\'';
                    state = 1;
                    continue;
                } else {
                    if (fseek(input_file, -2, SEEK_CUR) == -1) {
                        char_consts_token->type = -2;
                        free(buffer);
                        return char_consts_token;
                    }
                    char_consts_token->type = -3;
                    free(buffer);
                    return char_consts_token;
                }
            } else {
                if (fseek(input_file, -1, SEEK_CUR) == -1) {
                    char_consts_token->type = -2;
                    free(buffer);
                    return char_consts_token;
                }
                char_consts_token->type = -3;
                free(buffer);
                return char_consts_token;
            }
        }
        if (state == 1) {
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            } else if (curr_symb == '\'') {
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                char_consts_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(char_consts_token->buffer, buffer, buffer_size);
                char_consts_token->type = 4;
                free(buffer);
                return char_consts_token;
            } else if (curr_symb == '\n') {
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                char_consts_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(char_consts_token->buffer, buffer, buffer_size);
                char_consts_token->type = 4;
                free(buffer);
                return char_consts_token;
            } else {
                state = 1;
                continue;
            }
        }
        if (state == 2) {
            buffer = realloc(buffer, buffer_size);
            buffer[buffer_size - 1] = (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            }
            else if (curr_symb == '\n') {
                buffer_size++;
                buffer = realloc(buffer, buffer_size);
                buffer[buffer_size-1] = '\0';
                char_consts_token->buffer = calloc(buffer_size, sizeof(char));
                strncpy(char_consts_token->buffer, buffer, buffer_size);
                char_consts_token->type = 4;
                free(buffer);
                return char_consts_token;
            }
            else {
                state = 1;
                continue;
            }
        }
    }
    //EOF
    char_consts_token->type = 4;
    buffer_size++;
    buffer = realloc(buffer, buffer_size);
    buffer[buffer_size-1] = '\0';
    char_consts_token->buffer = calloc(buffer_size, sizeof(char));
    strncpy(char_consts_token->buffer, buffer, buffer_size);
    char_consts_token->type = 4;
    free(buffer);
    return char_consts_token;
}



int
processing_stage(char *type_of_processing) {
    char symb;
    int check;
    Token *current_token;

    if (strcmp(type_of_processing, "coloring") == 0) {
        token_processing_type = token_coloring;
        token_init = token_init_color;
        token_destruct = token_destruct_color;
    } else if (strcmp(type_of_processing, "counting") == 0) {
        token_processing_type = token_counting;
        token_init = token_init_count;
        token_destruct = token_destruct_count;
    }
    token_init();

    int keyword_max_length = 0;
    char **keywords;
    keywords = keywords_array_init(&keyword_max_length); //keywords array initializer

    int punctuator_max_length = 0;
    char **punctuators;
    punctuators = punctuators_array_init(&punctuator_max_length); //punctuators array initialize


    while (fread(&check, 1, sizeof(char), input_file) > 0) {
        if (fseek(input_file, -1, SEEK_CUR) == -1) {
            perror("fseek error: ");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        while (white_space_print_skip() == 0);
        if (white_space_print_skip() == 1) {
            break;
        }

        current_token = comment_analyser();
        if (current_token->type == 7) {
            comment_token->buffer = current_token->buffer;
            token_processing_type(comment_token);
            output_stage(*comment_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            free(current_token);
            perror("***Comment analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = string_literal_analyser();
        if (current_token->type == 5) {
            string_literal_token->buffer = current_token->buffer;
            token_processing_type(string_literal_token);
            output_stage(*string_literal_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
            perror("***String literal analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = char_consts_analyser();
        if (current_token->type == 4) {
//            token_coloring(current_token, YELLOW);
            char_consts_token->buffer = current_token->buffer;
            token_processing_type(char_consts_token);
            output_stage(*char_consts_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {\
            free(current_token);
            perror("***Char consts analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = keyword_analyser(keywords, keyword_max_length);
        if (current_token->type == 1) {
//            token_coloring(current_token, BLUE);
            keyword_token->buffer = current_token->buffer;
            token_processing_type(keyword_token);
            output_stage(*keyword_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            free(current_token);
            perror("***Keyword analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = ucn_analyser();
        if (current_token->type == 8) {
            output_stage(*current_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            free(current_token);
            perror("***Ucn analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = identifier_analyser();
        if (current_token->type == 2) {
            identifier_token->buffer = current_token->buffer;
            token_processing_type(identifier_token);
            output_stage(*identifier_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            free(current_token);
            perror("***Identifier analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = number_analyser();
        if (current_token->type == 3) {
            number_token->buffer = current_token->buffer;
            token_processing_type(number_token);
            output_stage(*number_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            free(current_token);
            perror("***Number analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        current_token = punctuator_analyser(punctuators, punctuator_max_length);
        if (current_token->type == 6) {
            punctuator_token->buffer = current_token->buffer;
            token_processing_type(punctuator_token);
            output_stage(*punctuator_token);
            free(current_token->buffer);
            free(current_token);
            continue;
        } else if (current_token->type == -2) {
            free(current_token);
            perror("***Punctuator analyser***");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 2;
        }
        if (current_token != NULL) {
            if (current_token->buffer != NULL) {
                free(current_token->buffer);
            }
            free(current_token);
        }

        /* if not of the 7 patterns, then print without color */
        if ((fread(&symb, 1, sizeof(char), input_file)) == 0) {
            perror("getchar error: ");
            token_destruct();
            free(punctuators);
            free(keywords);
            return 1;
        }
        putchar(symb);
    }
    if (strcmp(type_of_processing, "counting") == 0) {
        printf("\n\nSTATISTICS:");
        printf("\nComments amount: %d\n", comment_token->amount_in_text);
        printf("Keywords amount: %d\n", keyword_token->amount_in_text);
        printf("Identifiers amount: %d\n", identifier_token->amount_in_text);
        printf("Numbers amount: %d\n", number_token->amount_in_text);
        printf("Char consts amount: %d\n", char_consts_token->amount_in_text);
        printf("Punctuators amount: %d\n", punctuator_token->amount_in_text);
    }
    free(punctuators);
    free(keywords);
    token_destruct();

    return 0;
}