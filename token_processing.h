#ifndef CODE_COLORER_TOKEN_PROCESSING_H
#define CODE_COLORER_TOKEN_PROCESSING_H
#include "analysing.h"
#include "token.h"


typedef struct TokenProcessor TokenProcessor;

struct TokenProcessor {
    int (* process_token)(Token *, TokenProcessor *);
};

Token *
(* token_processing_type) (Token *token, TokenProcessor *);

int
(* token_init) (TokenProcessor **);

int
(* token_destruct) (TokenProcessor *);
#endif
