#ifndef CODE_COLORER_TOKEN_PROCESSING_H
#define CODE_COLORER_TOKEN_PROCESSING_H
#include "analysing.h"
#include "token.h"


class TokenProcessor {
public:
    virtual void process_token(Token *token) = 0;
};

#endif
