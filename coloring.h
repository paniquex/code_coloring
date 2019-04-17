#ifndef COLORING
#define COLORING
#include "analysing.h"
#include "token.h"

typedef struct TokenProcessor_coloring TokenProcessor_coloring;

struct TokenProcessor_coloring;

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
token_init_color(struct TokenProcessor_coloring **);

int
token_destruct_color(struct TokenProcessor_coloring *);