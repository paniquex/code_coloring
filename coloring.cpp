#include "coloring.h"
#include "token_processing.h"
#include <stdio.h>
#include "token.h"
#include <string>

const std::string BLACK = "\033[0;30m";
const std::string DARKGRAY = "\033[1;30m";
const std::string RED = "\033[;31m";
const std::string LIGHTRED = "\033[1;31m";
const std::string GREEN = "\033[0;32m";
const std::string LIGHTGREEN = "\033[1;32m";
const std::string BROWN = "\033[0;33m";
const std::string YELLOW = "\033[1;33m";
const std::string BLUE = "\033[0;34m";
const std::string LIGHTBLUE = "\033[1;34m";
const std::string PURPLE = "\033[0;35m";
const std::string LIGHTPURPLE = "\033[1;35m";
const std::string CYAN = "\033[0;36m";
const std::string LIGTHCYAN = "\033[1;36m";
const std::string LIGHTGRAY = "\033[0;37m";
const std::string WHITE = "\033[1;37m";
const std::string NOCOLOR = "\033[0m";


struct TokenProcessor_coloring {
    Token * (* token_state_changer)(Token *);
};


Token *
token_coloring(Token *token) {
    if ((token == nullptr) || (token->buffer.length() == 0)) {
        return nullptr;
    }
    std::string color;
    switch (token->type) {
        case 1: color = BLUE;
            break;
        case 2: color = LIGHTPURPLE;
            break;
        case 3: color = LIGHTBLUE;
            break;
        case 4: color = YELLOW;
            break;
        case 5: color = GREEN;
            break;
        case 6: color = RED;
            break;
        case 7: color = DARKGRAY;
            break;
    }
    token->buffer = color + token->buffer;
    token->buffer = token->buffer + NOCOLOR;
    return token;
}


int
token_init_color(TokenProcessor_coloring **token_struct_color) {
    TokenProcessor_coloring *tmp = malloc(sizeof *tmp);
    if (tmp == nullptr) {
        return 1;
    }
    tmp->token_state_changer = token_coloring;
    *token_struct_color = tmp;
    return 0;
}


void
token_destruct_color(TokenProcessor_coloring *token_struct_color) {
    free(token_struct_color);
}
