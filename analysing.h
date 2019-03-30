#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>


struct Token {
    char *buffer;
    int type;
    int amount_in_text;
};

typedef struct Token Token;


 /* keywords_amount for keyword_analyser func */
enum {KEYWORDS_AMOUNT = 14};


/* punctuators_amount for punctuator_analyser func */
enum {PUNCTUATORS_AMOUNT = 33, PUNCTUATOR_MAX_LENGTH = 4};


Token *
number_analyser();
/*
 * DESCRIPTION:
 * number_analyser() attempts to read symbols from stdin until EOF
 * if first digit has reached, then it prints to stdout "color key"
 * after first digit was found, if current symbol != digit, then prints to stdout
 * "standard color key".
 * RETURN VALUES:
     * 0 - if digit was found
     * 1 - if EOF was found
     * 2 - if some kind of error was found
     * 3 - if digit was not found
*/


Token *
comment_analyser();
/*
 * DESCRIPTION:
    * comment_analyser() attempts to read symbols from stdin until EOF
    * if it has found "comment token(or pattern)", then prints it with brown(yellow) color
 * RETURN VALUES:
    * 0, if somekind of comment was found
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if comment was not found
*/


Token *
punctuator_analyser(char *PUNCTUATORS[PUNCTUATORS_AMOUNT], int punctuator_max_length);
/*
 * DESCRIPTION:
    * punctuator_analyser() attempts to read symbols from stdin until EOF
    * it uses PUNCTUATORS array, which contains all available pattern of punctuators
    * if it has found "punctuator token(or pattern)" then it prints it with red color
 * RETURN VALUES:
     * 0, if punctuator was found and printed
     * 1, if EOF was reached
     * 2, if somekind of error was found
     * 3, if no punctuator was found
*/


Token *
keyword_analyser(char *KEYWORDS[KEYWORDS_AMOUNT], int keyword_max_length);
/* DESCRIPTION:
    * keyword_analyser() attempts to read symbols from stdin until EOF
    * it uses KEYWORDS array, which contains all available pattern of punctuators
    * if it has found "keyword token(or pattern)" then it prints it with blue color
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


Token *
identifier_analyser();
/* DESCRIPTION:
 * identifier_analyser() attempts to read symbols from stdin until EOF
 * if it has found "identifier token(or pattern)" then it prints it with pink color
 *
 * RETURN VALUES:
    * 0, if identifier was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no identifier was found
*/


int
is_hexadecimal_digit(int symb);
/* DESCRIPTION:
 * is_hexadecimal_digit checks symb, if it is hexadecimal digit or not
 * RETURN VALUES:
    * 0, if it is not white_space
    * 1,  else
*/


Token *
ucn_analyser();
/* DESCRIPTION:
 * ucn_analyser() attempts to read symbols from stdin until EOF
 * if it has found "universal character token(or pattern)" then it prints it with pink color
 *
 * RETURN VALUES:
    * 0, if Universal character name was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no Universal character name was found
*/


int
is_white_space(int symb);
/* DESCRIPTION:
 * is_white_space() checks symb, if it is white_space character or not
 * RETURN VALUES:
    * 0, if it is not white_space
    * 1  else
*/


int
white_space_print_skip();
/* DESCRIPTION:
 * white_space_print_skip() attempts to read one symbol from stdin
 * and checks if it is white_space character, then prints it
 * RETURN VALUES:
    * 0, if this symb is white_space
    * 1, if EOF
    * 2, if some kind of error was found
    * 3, if symb is not white_space
*/


int
is_nondigit(int symb);
/*
 * RETURN VALUES:
    * 1, if symb is nondigit
    * 0, else
 */


Token *
string_literal_analyser();
/* DESCRIPTION:
    * string_literal_analyser() attempts to read symbols from stdin until EOF
    * if it has found "string_literal token(or pattern)" then it prints it with green color
 * RETURN VALUES:
    * 0, if string_literal was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no string_literal was found
 * */


Token *
char_consts_analyser();
/* DESCRIPTION:
    * char_consts_analyser() attempts to read symbols from stdin until EOF
    * if it has found "char_consts token(or pattern)" then it prints it with green color
 * RETURN VALUES:
    * 0, if char_consts was found and printed
    * 1, if EOF was reached
    * 2, if somekind of error was found
    * 3, if no char_consts was found
 * */


int
analysing_stage(char **punctuators, int punctuator_max_length, char **keywords, int keyword_max_length);
/* DESCRIPTION:
    * сoloring_stage takes 4 parameters, which are needed for punctuator_analyser and keyword_analyser functions.
    * analysing_stage() contains all analyser functions:
    * 0) white_space_print_skip()
    * 1) comment_analyser()
    * 2) sting_literal_analyser()
    * 3) char_consts_analyser()
    * 4) keyword_analyser()
    * 5) identifier_analyser()
    * 6) number_analyser()
    * 7) punctuator_analyser()
    * 8) just putchar(curr_symb), if symbol don't match any pattern
 * RETURN VALUES:
    * 0, if everything was correct
    * 1, if fgetc(input_file) occurs an error
    * 2, if some of analysers occurs an error
 */


char **
keywords_array_init(int *keyword_max_length);
/* DESCRIPTION:
    * keywords_array_init takes pointer to int and changes it to
    * max length of keywords
 * RETURN VALUES:
    * pointer to array of keywords
    * NULL, if somekind of error was found
 */


char **
punctuators_array_init(int *punctuator_max_length);
/* DESCRIPTION:
    * punctuator_array_init takes pointer to int and changes it to
    * max length of punctuators
 * RETURN VALUES:
    * pointer to array of punctuators
    * NULL, if somekind of error was found
*/

