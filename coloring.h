#ifndef COLORING
#define COLORING
#include "analysing.h"

const char *BLACK;
const char *DARKGRAY;
const char *RED;
const char *LIGHTRED;
const char *GREEN;
const char *LIGHTGREEN;
const char *BROWN;
const char *YELLOW;
const char *BLUE;
const char *LIGHTBLUE;
const char *PURPLE;
const char *LIGHTPURPLE;
const char *CYAN;
const char *LIGTHCYAN;
const char *LIGHTGRAY;
const char *WHITE;
const char *NOCOLOR;

Token *
token_coloring(Token *token, const char *color);
/* DESCRIPTION:
    * token_coloring takes 2 parameters, first - Token struct, second - color in which we need to color our Token
    *
 * RETURN VALUES:
    * token struct with colored buffer, if everything was correct
    * NULL, if buffer or token is NULL
 */

#endif 