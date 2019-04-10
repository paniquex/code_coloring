#ifndef CODE_COLORER_TOKEN_PROCESSING_H
#define CODE_COLORER_TOKEN_PROCESSING_H
#include "analysing.h"

Token *comment_token;
Token *string_literal_token;
Token *char_consts_token;
Token *keyword_token;
Token *number_token;
Token *punctuator_token;
Token *identifier_token;

Token *
(* token_processing_type) (Token *token);

int
(* token_init) ();

int
(* token_destruct) ();
#endif
