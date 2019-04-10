#include "counting.h"
#include "token_processing.h"

int
token_init_count() {
    comment_token = calloc(1, sizeof(Token));
    comment_token->amount_in_text = 0;
    string_literal_token = calloc(1, sizeof(Token));
    string_literal_token->amount_in_text = 0;
    char_consts_token = calloc(1, sizeof(Token));
    char_consts_token->amount_in_text = 0;
    keyword_token = calloc(1, sizeof(Token));
    keyword_token->amount_in_text = 0;
    number_token = calloc(1, sizeof(Token));
    number_token->amount_in_text = 0;
    punctuator_token = calloc(1, sizeof(Token));
    punctuator_token->amount_in_text = 0;
    identifier_token = calloc(1, sizeof(Token));
    identifier_token->amount_in_text = 0;
    return 0;
}


Token *
token_counting(Token *token) {
    token->amount_in_text++;
    return token;
}

int
token_destruct_count() {
    free(comment_token);
    free(string_literal_token);
    free(char_consts_token);
    free(keyword_token);
    free(number_token);
    free(punctuator_token);
    free(identifier_token);

    return 0;
}
