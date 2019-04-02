#include "coloring.h"

const char *BLACK = "\033[0;30m";
const char *DARKGRAY = "\033[1;30m";
const char *RED = "\033[;31m";
const char *LIGHTRED = "\033[1;31m";
const char *GREEN = "\033[0;32m";
const char *LIGHTGREEN = "\033[1;32m";
const char *BROWN = "\033[0;33m";
const char *YELLOW = "\033[1;33m";
const char *BLUE = "\033[0;34m";
const char *LIGHTBLUE = "\033[1;34m";
const char *PURPLE = "\033[0;35m";
const char *LIGHTPURPLE = "\033[1;35m";
const char *CYAN = "\033[0;36m";
const char *LIGTHCYAN = "\033[1;36m";
const char *LIGHTGRAY = "\033[0;37m";
const char *WHITE = "\033[1;37m";
const char *NOCOLOR = "\033[0m";

#include <stdio.h>

Token *
token_coloring(Token *token, const char *color) {
    if ((token == NULL) || (token->buffer == NULL)) {
        return NULL;
    }
    size_t color_size = strlen(color);
    size_t nocolor_size = strlen(NOCOLOR);
    size_t buffer_size_old = strlen(token->buffer);
    size_t buffer_size_cur = buffer_size_old + color_size + nocolor_size + 1;
    char *buffer = calloc(buffer_size_cur, sizeof(char));
    strncat(buffer, color, color_size);
    strncat(buffer + color_size - 1, token->buffer, buffer_size_old);
    strncat(buffer + color_size + buffer_size_old, NOCOLOR, nocolor_size);
    buffer[buffer_size_cur - 1] = '\0';
    token->buffer = realloc(token->buffer, buffer_size_cur);
    strncpy(token->buffer, buffer, buffer_size_cur);
    free(buffer);
    return token;
}