#ifndef CODE_COLORER_COUNTING_H
#define CODE_COLORER_COUNTING_H

#include "analysing.h"

int
token_init_count();

Token *
token_counting(Token *token);

int
token_destruct_count();

#endif
