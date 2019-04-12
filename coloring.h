#ifndef COLORING
#define COLORING
#include "analysing.h"
#include "token.h"

typedef struct Token_processing_coloring Token_processing_coloring;

struct Token_processing_coloring;

Token *
token_coloring(Token *token);
/* DESCRIPTION:
    * token_coloring takes 2 parameters, first - Token struct, second - color in which we need to color our Token
    *
 * RETURN VALUES:
    * token struct with colored buffer, if everything was correct
    * NULL, if buffer or token is NULL
 */

#endif

int
token_init_color(struct Token_processing_coloring **);

int
token_destruct_color(struct Token_processing_coloring *);