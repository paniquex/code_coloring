#ifndef CODE_COLORER_TOKEN_PROCESSING_H
#define CODE_COLORER_TOKEN_PROCESSING_H
#include "token.hpp"


class TokenProcessor {
public:
    virtual void process_token(Token *token) = 0;
    virtual void print_token() const {}
    virtual ~TokenProcessor() = default;
};

#endif
