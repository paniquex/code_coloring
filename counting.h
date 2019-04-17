#ifndef CODE_COLORER_COUNTING_H
#define CODE_COLORER_COUNTING_H

#include "analysing.h"

typedef struct TokenProcessor_counting TokenProcessor_counting;

struct TokenProcessor_counting;

int
token_init_count(TokenProcessor_counting **token_struct_count);

void
output_count_statistics(TokenProcessor_counting *);

Token *
token_counting(Token *token, TokenProcessor_counting *token_struct_count);

void
token_destruct_count(TokenProcessor_counting *token_struct_count);

#endif
