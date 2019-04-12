//
// Created by paniquex on 11.04.19.
//

#ifndef CODE_COLORER_TOKEN_H
#define CODE_COLORER_TOKEN_H

typedef struct Token Token;

struct Token {
    char *buffer;
    int type;
};

#endif //CODE_COLORER_TOKEN_H
