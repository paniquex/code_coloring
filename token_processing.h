#ifndef CODE_COLORER_TOKEN_PROCESSING_H
#define CODE_COLORER_TOKEN_PROCESSING_H
#include "analysing.h"
#include "token.h"


typedef struct Token_processing Token_processing;

struct Token_processing {
    int (* token_state_changer)(Token *, Token_processing *);
};

Token *
(* token_processing_type) (Token *token, Token_processing *);

int
(* token_init) (Token_processing **);

int
(* token_destruct) (Token_processing *);
#endif
