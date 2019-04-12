#ifndef CODE_COLORER_COUNTING_H
#define CODE_COLORER_COUNTING_H

#include "analysing.h"

typedef struct Token_processing_counting Token_processing_counting;

struct Token_processing_counting;

int
token_init_count(Token_processing_counting **token_struct_count);

int
output_count_statistics(Token_processing_counting *);

Token *
token_counting(Token *token, Token_processing_counting *token_struct_count);

int
token_destruct_count(Token_processing_counting *token_struct_count);

#endif
