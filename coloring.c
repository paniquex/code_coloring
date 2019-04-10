#include "coloring.h"
#include "token_processing.h"

#define BLACK "\033[0;30m"
#define DARKGRAY = "\033[1;30m"
#define RED "\033[;31m"
#define LIGHTRED "\033[1;31m"
#define GREEN "\033[0;32m"
#define LIGHTGREEN "\033[1;32m"
#define BROWN "\033[0;33m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define LIGHTBLUE "\033[1;34m"
#define PURPLE "\033[0;35m"
#define LIGHTPURPLE "\033[1;35m"
#define CYAN "\033[0;36m"
#define LIGTHCYAN "\033[1;36m"
#define LIGHTGRAY "\033[0;37m"
#define WHITE "\033[1;37m"
#define NOCOLOR "\033[0m"

static int init_state = 0;

#include <stdio.h>


Token *
token_coloring(Token *token) {
    if ((token == NULL) || (token->buffer == NULL)) {
        return NULL;
    }
    if (init_state == 0) {

    }
    size_t color_size = strlen(token->color);
    size_t nocolor_size = strlen(NOCOLOR);
    size_t buffer_size_old = strlen(token->buffer);
    size_t buffer_size_cur = buffer_size_old + color_size + nocolor_size + 1;
    char *buffer = calloc(buffer_size_cur, sizeof(char));
    strncat(buffer, token->color, color_size);
    strncat(buffer + color_size - 1, token->buffer, buffer_size_old);
    strncat(buffer + color_size + buffer_size_old, NOCOLOR, nocolor_size);
    buffer[buffer_size_cur - 1] = '\0';
    token->buffer = realloc(token->buffer, buffer_size_cur);
    strncpy(token->buffer, buffer, buffer_size_cur);
    free(buffer);
    return token;
}


int
token_init_color() {
    comment_token = calloc(1, sizeof(Token));
    comment_token->color = LIGHTGRAY;
    string_literal_token = calloc(1, sizeof(Token));
    string_literal_token->color = GREEN;
    char_consts_token = calloc(1, sizeof(Token));
    char_consts_token->color = YELLOW;
    keyword_token = calloc(1, sizeof(Token));
    keyword_token->color = BLUE;
    number_token = calloc(1, sizeof(Token));
    number_token->color = LIGHTBLUE;
    punctuator_token = calloc(1, sizeof(Token));
    punctuator_token->color = RED;
    identifier_token = calloc(1, sizeof(Token));
    identifier_token->color = LIGHTPURPLE;
    return 0;
}

int
token_destruct_color() {
    free(comment_token);
    free(string_literal_token);
    free(char_consts_token);
    free(keyword_token);
    free(number_token);
    free(punctuator_token);
    free(identifier_token);

    return 0;

}