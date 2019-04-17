//
// Created by paniquex on 11.04.19.
//

#ifndef CODE_COLORER_TOKEN_H
#define CODE_COLORER_TOKEN_H

enum {KEYWORD = 1, IDENTIFIER, NUMBER, CHAR_CONST, STRING_LITERAL, PUNCTUATOR, COMMENT};

typedef struct Token Token;

struct Token {
    char *buffer;
    int type;
};

#endif //CODE_COLORER_TOKEN_H
