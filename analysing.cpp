#include "analysing.hpp"



/* keywords_amount for keyword_analyser func */
enum {KEYWORDS_AMOUNT = 14, KEYWORDS_MAX_LENGTH = 14};

std::string keywords[KEYWORDS_AMOUNT] =
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


/* punctuators_amount for punctuator_analyser func */
enum {PUNCTUATORS_AMOUNT = 33, PUNCTUATOR_MAX_LENGTH = 4};

std::string punctuators[PUNCTUATORS_AMOUNT] =
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




static Token *
number_analyser(std::fstream *input_file) {
    /*
 * DESCRIPTION:
 * number_analyser() attempts to read symbols from stdin until EOF
 * if first digit has reached, then saves it in Token->buffer, and changes Token->type
 * after first digit was found, if current symbol != digit, then saves it in Token->buffer, and changes Token->type
 * "standard color key".
 * RETURN VALUES:
     * token with type 0- if digit was found
     * token with type 1 - if EOF was found
     * token with type 2 - if some kind of error was found
     * token with type 3 - if digit was not found
*/
    char curr_symb, is_first_digit = 1;
    auto *number_token = new Token;
    std::string buffer;
    while (input_file->peek() != EOF) {
        input_file->read(&curr_symb, sizeof(char));
        if (isdigit(curr_symb)) {
            if (is_first_digit) {
                is_first_digit = 0;
            }
            buffer += (char) curr_symb;
        } else {
            if (!is_first_digit) {
                input_file->seekg(-1, std::fstream::cur);
                number_token->set_buffer(buffer);;
                number_token->set_type(NUMBER);
                return number_token;
            }
            input_file->seekg(-1, std::fstream::cur);
            number_token->set_type(-3);
            return number_token;
        }
    }
    number_token->set_buffer(buffer);
    number_token->set_type(NUMBER);
    return number_token;
}


static Token *
comment_analyser(std::fstream *input_file) {
    /*
 * DESCRIPTION:
    * comment_analyser() attempts to read symbols from stdin until EOF
    * if it has found "comment token(or pattern)", then saves it in Token->buffer, and changes Token->type
 * RETURN VALUES:
    * token with type 0, if somekind of comment was found
    * token with type 1, if EOF was reached
    * token with type 2, if somekind of error was found
    * token with type 3, if comment was not found
*/

    char curr_symb;
    int state1 = 0, state2 = 0;
    std::string buffer;
    auto *comment_token = new Token;
    while (input_file->peek() != EOF) {
        input_file->read(&curr_symb, sizeof(char));
        if ((curr_symb == '/') && (state1 == 0) && (state2 == 0)) {
            state1 = 1;
            state2 = 1;
            continue;
        } else if ((state1 == 0) && (state2 == 0)) {
            input_file->seekg(-1, std::fstream::cur);
            comment_token->set_type(-3);
            return comment_token;
        }
        if ((state1 == 1) || (state2 == 1)) {
            if ((curr_symb != '/') && (curr_symb != '*')) {
                state1 = 0;
                state2 = 0;
                input_file->seekg(-1, std::fstream::cur);
                comment_token->set_type(-3);
                return comment_token;
            } else {
                if (curr_symb == '/') {
                    state1 = 2;
                    state2 = 0;
                    buffer += '/';
                    buffer += '/';
                } else {
                    state1 = 0;
                    state2 = 2;
                    buffer += '/';
                    buffer += '*';
                }
            }
            continue;
        }

        if (state1 == 2) {
            if (curr_symb == '\n') {
                state1 = 0;
                input_file->seekg(-1, std::fstream::cur);
                comment_token->set_buffer(buffer);
                comment_token->set_type(COMMENT);
                return comment_token;
            } else if (curr_symb == '\\') {
                state1 = 3;
                buffer += (char) curr_symb;
            } else {
                buffer += (char) curr_symb;
            }
            continue;
        }
        if (state2 == 2) {
            if (curr_symb == '*') {
                state2 = 3;
                state1 = -1;
            }
            buffer += (char) curr_symb;
            continue;
        }
        if (state1 == 3) {
            state1 = 2;
            buffer += (char) curr_symb;
            continue;
        }
        if (state2 == 3) {
            if (curr_symb == '/') {
                buffer += '/';
                state2 = 0;
                comment_token->set_buffer(buffer);
                comment_token->set_type(COMMENT);
                return comment_token;
            }
            if (curr_symb != '*') {
                state2 = 2;
            }
            buffer += (char) curr_symb;
            continue;
        }
        input_file->seekg(-1, std::fstream::cur);
        comment_token->set_type(-3);
        return comment_token;
    }
        if (buffer.length() == 0) {
            comment_token->set_type(-3);
            return comment_token;
        }
        if (buffer.length() < 2) {
            input_file->seekg(-1, std::fstream::cur);
            comment_token->set_type(-3);
            return comment_token;
        }
        comment_token->set_buffer(buffer);
        comment_token->set_type(COMMENT);
        return comment_token;
}


static Token *
punctuator_analyser(std::string *PUNCTUATORS, int PUNCTUATOR_MAX_LENGTH, std::fstream *input_file) {
    /*
 * DESCRIPTION:
    * punctuator_analyser() attempts to read symbols from stdin until EOF
    * it uses PUNCTUATORS array, which contains all available pattern of punctuators
    * if it has found "punctuator token(or pattern)" then saved it in Token->buffer, and changes Token->type
 * RETURN VALUES:
     * token with type 0, if punctuator was found and printed
     * token with type 1, if EOF was reached
     * token with type 2, if somekind of error was found
     * token with type 3, if no punctuator was found
*/
    std::string buffer;
    char buffer_read;
    auto *punctuator_token = new Token;
    for (int i = 0; i < PUNCTUATOR_MAX_LENGTH; i++) {
        if (input_file->peek() == EOF) {
            break;
        }
        input_file->read(&buffer_read, sizeof(char));
        if (buffer_read == '\0') {
            punctuator_token->set_type(-3);
            return punctuator_token;
        }
        buffer += buffer_read;
    }
    if (buffer.length() == 0) {
        punctuator_token->set_type(-3);
        return punctuator_token;
    }
    if (buffer.length() == 0) {
        punctuator_token->set_type(-3);
        return punctuator_token;
    }
    unsigned long punctuator_curr_length = buffer.length();
    for (unsigned long i = 0; i < punctuator_curr_length; i++) {
        for (int k = 0; k < PUNCTUATORS_AMOUNT; k++) {
            if (strncmp(PUNCTUATORS[k].c_str(), buffer.c_str(), (size_t) punctuator_curr_length - i) == 0) {
                input_file->seekg(-i, std::fstream::cur);
                punctuator_token->set_buffer(buffer.substr(0, punctuator_curr_length - i));
                punctuator_token->set_type(PUNCTUATOR);
                return punctuator_token;
            }
        }
    }
    punctuator_token->set_type(-3);
    input_file->seekg(-buffer.length(), std::fstream::cur);
    return punctuator_token;
}


static Token *
keyword_analyser(std::string *KEYWORDS, int KEYWORDS_MAX_LENGTH, std::fstream *input_file) {
    /* DESCRIPTION:
    * keyword_analyser() attempts to read symbols from stdin until EOF
    * it uses KEYWORDS array, which contains all available pattern of punctuators
    * if it has found "keyword token(or pattern)" then saves it in Token->buffer, and changes Token->type
 * RETURN VALUES:
     * token with type 0, if keyword was found and printed
     * token with type 1, if EOF was reached
     * token with type 2, if somekind of error was found
     * token with type 3, if no keyword was found
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

    std::string buffer;

    char buffer_read;
    auto *keyword_token = new Token;
    for (int i = 0; i < KEYWORDS_MAX_LENGTH; i++) {
        if (input_file->peek() == EOF) {
            break;
        }
        input_file->read(&buffer_read, sizeof(char));
        if (buffer_read == '\0') {
            keyword_token->set_type(-3);
            return keyword_token;
        }
        buffer += buffer_read;
    }
    if (buffer.length() == 0) {
        keyword_token->set_type(-3);
        return keyword_token;
    }
    if (buffer.length() == 0) {
        keyword_token->set_type(-3);
        return keyword_token;
    }
    unsigned long keyword_curr_length = buffer.length();
    for (unsigned long i = 0; i < keyword_curr_length; i++) {
        for (int k = 0; k < KEYWORDS_AMOUNT; k++) {
            if (strncmp(KEYWORDS[k].c_str(), buffer.c_str(), (size_t) keyword_curr_length - i) == 0) {
                input_file->seekg(-i, std::fstream::cur);
                keyword_token->set_buffer(buffer.substr(0, keyword_curr_length - i));
                keyword_token->set_type(KEYWORD);
                return keyword_token;
            }
        }
    }
    keyword_token->set_type(-3);
    input_file->seekg(-buffer.length(), std::fstream::cur);
    return keyword_token;
}



static Token *
identifier_analyser(std::fstream *input_file) {
    /* DESCRIPTION:
 * identifier_analyser() attempts to read symbols from stdin until EOF
 * if it has found "identifier token(or pattern)" then saves it in Token->buffer, and changes Token->type
 *
 * RETURN VALUES:
    * token with type 0, if identifier was found and printed
    * token with type 1, if EOF was reached
    * token with type 2, if somekind of error was found
    * token with type 3, if no identifier was found
*/

    char curr_symb;
    int amount_symb_was_read = 0;
    int state1 = 0;
    auto *identifier_token = new Token;
    std::string buffer;
    while (input_file->peek() != EOF) {
        input_file->get(curr_symb);
        amount_symb_was_read++;
        if (state1 == 0) {
            if (is_nondigit(curr_symb)) {
                state1 = 1;
                continue;
            } else {
                input_file->seekg(-amount_symb_was_read, std::fstream::cur);
                identifier_token->set_type(-3);
                return identifier_token;
            }
        }
        if (state1 == 1) {
            if ((is_nondigit(curr_symb)) || (isdigit(curr_symb)))  {
                continue;
            } else {
                input_file->seekg(-amount_symb_was_read, std::fstream::cur);
                identifier_token->set_type(IDENTIFIER);
                char curr_tok_symb;
                for (int i = 0; i < amount_symb_was_read; i++) {
                    input_file->read(&curr_tok_symb, sizeof(char));
                    identifier_token->set_buffer(identifier_token->get_buffer() + curr_tok_symb);
                }
                return identifier_token;
            }
        }
    }
    input_file->seekg(-amount_symb_was_read, std::fstream::cur);
    if (state1 == 1) {
        identifier_token->set_type(IDENTIFIER);
        char curr_tok_symb;
        for (int i = 0; i < amount_symb_was_read; i++) {
            input_file->get(curr_tok_symb);
            identifier_token->set_buffer(identifier_token->get_buffer() + curr_tok_symb);
        }
        return identifier_token;
    }
    if (amount_symb_was_read == 0) {
        identifier_token->set_type(-3);
        return identifier_token;
    }
    identifier_token->set_type(-3);
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
ucn_analyser(std::fstream *input_file) {
    /* DESCRIPTION:
 * ucn_analyser() attempts to read symbols from stdin until EOF
 * if it has found "universal character token(or pattern)" then saves it in Token->buffer, and changes Token->type
 *
 * RETURN VALUES:
    * token with type 0, if Universal character name was found and printed
    * token with type 1, if EOF was reached
    * token with type 2, if somekind of error was found
    * token with type 3, if no Universal character name was found
*/
    char curr_symb;
    int amount_symb_was_read = 0;
    int print_u_or_U = 'u'; // if 'u' - print u, if 1 - print 'U'
    int state1 = 0;
    auto *ucn_token = new Token;
    std::string buffer;
    while (input_file->peek() != EOF) {
        input_file->get(curr_symb);
        amount_symb_was_read++;
        if (state1 == 0) {
            if (curr_symb == '\\') {
                state1 = 1;
                continue;
            } else {
                input_file->seekg(-amount_symb_was_read, std::fstream::cur);
                ucn_token->set_type(-3);
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
            input_file->seekg(-amount_symb_was_read, std::fstream::cur);
            ucn_token->set_type(-3);
            return ucn_token;
        }
        if (state1 == 2) {
            if (is_hexadecimal_digit(curr_symb)) {
                buffer += '\\';
                buffer += (char) print_u_or_U;
                buffer += curr_symb;
                state1 = 3;
                continue;
            } else {
                input_file->seekg(-amount_symb_was_read, std::fstream::cur);
                ucn_token->set_type(-3);
                return ucn_token;
            }
        }
        if (state1 == 3) {
            if (is_hexadecimal_digit(curr_symb)) {
                buffer += curr_symb;
            } else {
                input_file->seekg(-amount_symb_was_read, std::fstream::cur);
                ucn_token->set_buffer(buffer);
                ucn_token->set_type(8);
                return ucn_token;
            }
        }
    }
    amount_symb_was_read++;
    ucn_token->set_buffer(buffer);
    ucn_token->set_type(8);
    return ucn_token;
}


static int
white_space_print_skip(std::fstream *input_file) {
    /* DESCRIPTION:
 * white_space_print_skip() attempts to read one symbol from stdin
 * and checks if it is white_space character, then prints it
 * RETURN VALUES:
    * token with type 0, if this symb is white_space
    * token with type 1, if EOF
    * token with type 2, if some kind of error was found
    * token with type 3, if symb is not white_space
*/
    /* token with type 0, if this symb is white_space
     * token with type 1, if EOF
     * token with type 2, if some kind of error was found
     * token with type 3, if symb is not white_space*/
    char curr_symb;
    if (input_file->peek() != EOF) {
        input_file->get(curr_symb);
        if (!is_white_space(curr_symb)) {
            input_file->seekg(-1, std::fstream::cur);
            return 3;
        } else {
            putchar(curr_symb);
        }
    } else return 1;
    return 0;
}



static Token *
string_literal_analyser(std::fstream *input_file) {
    /* DESCRIPTION:
    * string_literal_analyser() attempts to read symbols from stdin until EOF
    * if it has found "string_literal token(or pattern)" then saves it in Token->buffer, and changes Token->type
 * RETURN VALUES:
    * token with type 0, if string_literal was found and printed
    * token with type 1, if EOF was reached
    * token with type 2, if somekind of error was found
    * token with type 3, if no string_literal was found
 * */

    char curr_symb;
    int state = 0;
    auto *string_literal_token = new Token;
    std::string buffer;
    while (input_file->peek() != EOF) {
        input_file->get(curr_symb);
        if (state == 0) {
            if (curr_symb == '\"') {
                buffer += curr_symb;
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                if ((curr_symb == 'L') || (curr_symb == 'U')) {
                    input_file->get(curr_symb);
                    if (curr_symb != '\"') {
                        input_file->seekg(-2, std::fstream::cur);
                        string_literal_token->set_type(-3);
                        return string_literal_token;
                    } else {
                        buffer += (char) curr_prefix;
                        buffer += '\"';
                        state = 1;
                        continue;
                    }
                } else { //curr_symb == u
                    input_file->get(curr_symb);
                    if ((curr_symb != '8') && (curr_symb != '\"')) {
                        input_file->seekg(-2, std::fstream::cur);
                        string_literal_token->set_type(-3);
                        return string_literal_token;
                    } else {
                        if (curr_symb == '\"') {
                            buffer += (char) curr_prefix;
                            buffer += '\"';
                            state = 1;
                            continue;
                        }
                        if (curr_symb == '8') {
                            input_file->get(curr_symb);
                            if (curr_symb == '\"') {
                                buffer += (char) curr_prefix;
                                buffer += '8';
                                buffer += '\"';
                                state = 1;
                                continue;
                            } else {
                                input_file->seekg(-buffer.length(), std::fstream::cur);
                                string_literal_token->set_type(-3);
                                return string_literal_token;
                            }
                        }
                    }
                }
            } else {
                input_file->seekg(-1, std::fstream::cur);
                string_literal_token->set_type(-3);
                return string_literal_token;
            }
        }
        if (state == 1) {
            buffer += (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            } else if (curr_symb == '\"') {
                string_literal_token->set_buffer(buffer);
                string_literal_token->set_type(STRING_LITERAL);
                return string_literal_token;
            } else if (curr_symb == '\n') {
                string_literal_token->set_buffer(buffer);
                string_literal_token->set_type(STRING_LITERAL);
                return string_literal_token;
            } else {
                state = 1;
                continue;
            }
        }
        if (state == 2) {
            buffer += (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            }
            else if (curr_symb == '\n') {
                string_literal_token->set_buffer(buffer);
                string_literal_token->set_type(STRING_LITERAL);
                return string_literal_token;
            }
            else {
                state = 1;
                continue;
            }
        }
    }
    string_literal_token->set_type(STRING_LITERAL);
    string_literal_token->set_buffer(buffer);
    return string_literal_token;
}

static Token *
char_consts_analyser(std::fstream *input_file) {
    /* DESCRIPTION:
   * char_consts_analyser() attempts to read symbols from stdin until EOF
   * if it has found "char_consts token(or pattern)" then saves it in Token->buffer, and changes Token->type
* RETURN VALUES:
   * token with type 0, if char_consts was found and printed
   * token with type 1, if EOF was reached
   * token with type 2, if somekind of error was found
   * token with type 3, if no char_consts was found
* */
    char curr_symb;
    int state = 0;
    auto *char_consts_token = new Token;
    std::string buffer;
    while (input_file->peek() != EOF) {
        input_file->get(curr_symb);
        if (state == 0) {
            if (curr_symb == '\'') {
                buffer += (char) curr_symb;
                state = 1;
                continue;
            } else if ((curr_symb == 'L') || (curr_symb == 'U') || (curr_symb == 'u')) {
                int curr_prefix = curr_symb;
                input_file->get(curr_symb);
                if (curr_symb == '\'') {
                    buffer += (char) curr_prefix;
                    buffer += '\'';
                    state = 1;
                    continue;
                } else {
                    input_file->seekg(-2, std::fstream::cur);
                    char_consts_token->set_type(-3);
                    return char_consts_token;
                }
            } else {
                input_file->seekg(-1, std::fstream::cur);
                char_consts_token->set_type(-3);
                return char_consts_token;
            }
        }
        if (state == 1) {
            buffer += (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            } else if (curr_symb == '\'') {
                char_consts_token->set_buffer(buffer);
                char_consts_token->set_type(CHAR_CONST);
                return char_consts_token;
            } else if (curr_symb == '\n') {
                char_consts_token->set_buffer(buffer);
                char_consts_token->set_type(CHAR_CONST);
                return char_consts_token;
            } else {
                state = 1;
                continue;
            }
        }
        if (state == 2) {
            buffer += (char) curr_symb;
            if (curr_symb == '\\') {
                state = 2;
                continue;
            }
            else if (curr_symb == '\n') {
                char_consts_token->set_buffer(buffer);
                char_consts_token->set_type(CHAR_CONST);
                return char_consts_token;
            }
            else {
                state = 1;
                continue;
            }
        }
    }
    //EOF
    char_consts_token->set_buffer(buffer);
    char_consts_token->set_type(CHAR_CONST);
    return char_consts_token;
}



Token *
analysing_stage(std::fstream *input_file) {
    char symb;
    char check;
    Token *current_token;
    while (input_file->peek() != EOF) {
        input_file->get(check);
        input_file->seekg(-1, std::fstream::cur);
        while (white_space_print_skip(input_file) == 0);
        if (white_space_print_skip(input_file) == 1) {
            break;
        }

        current_token = comment_analyser(input_file);
        if (current_token->get_type() == 7) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Comment analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        current_token = string_literal_analyser(input_file);
        if (current_token->get_type() == 5) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            if (current_token != nullptr) {
                delete current_token;
            }
            free(current_token);
            perror("***String literal analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        current_token = char_consts_analyser(input_file);
        if (current_token->get_type() == 4) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Char consts analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

       current_token = keyword_analyser(keywords, KEYWORDS_MAX_LENGTH, input_file);
        if (current_token->get_type() == 1) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Keyword analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        current_token = ucn_analyser(input_file);
        if (current_token->get_type() == 8) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Ucn analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        current_token = identifier_analyser(input_file);
        if (current_token->get_type() == 2) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Identifier analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        current_token = number_analyser(input_file);
        if (current_token->get_type() == 3) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Number analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        current_token = punctuator_analyser(punctuators, PUNCTUATOR_MAX_LENGTH, input_file);
        if (current_token->get_type() == 6) {
            return current_token;
        } else if (current_token->get_type() == -2) {
            free(current_token);
            perror("***Punctuator analyser***");
            return nullptr;
        }
        if (current_token != nullptr) {
            delete current_token;
        }

        /* if not of the 7 patterns, then print without color */
        if (input_file->peek() == EOF) {
            perror("getchar error: ");
            return nullptr;
        }
        input_file->get(symb);
        putchar(symb);
    }
    current_token = new Token;
    current_token->set_type(0);
    return current_token;
}