#include "counting.h"
#include "token_processing.h"

struct TokenProcessor_counting {
    Token * (* process_token)(Token *, TokenProcessor_counting *);
    int comment_amount;
    int string_literal_amount;
    int char_consts_amount;
    int keyword_amount;
    int number_amount;
    int punctuator_amount;
    int identifier_amount;
};


int
token_init_count(struct TokenProcessor_counting **token_struct_count) {
    TokenProcessor_counting *tmp = malloc(sizeof(*tmp));
    if (tmp == NULL) {
        return 1;
    }
    tmp->keyword_amount = 0;
    tmp->char_consts_amount = 0;
    tmp->comment_amount = 0;
    tmp->identifier_amount = 0;
    tmp->number_amount = 0;
    tmp->punctuator_amount = 0;
    tmp->string_literal_amount = 0;
    tmp->process_token = token_counting;
    *token_struct_count = tmp;
    return 0;
}

void
output_count_statistics(TokenProcessor_counting *token_struct_count) {
    printf("\n\nSTATISTICS:");
    printf("\nComments amount: %d\n", token_struct_count->comment_amount);
    printf("Keywords amount: %d\n", token_struct_count->keyword_amount);
    printf("Identifiers amount: %d\n", token_struct_count->identifier_amount);
    printf("Numbers amount: %d\n", token_struct_count->number_amount);
    printf("Char consts amount: %d\n", token_struct_count->char_consts_amount);
    printf("Punctuators amount: %d\n", token_struct_count->punctuator_amount);
    printf("String literals amount: %d\n", token_struct_count->string_literal_amount);
}

Token *
token_counting(Token *token, TokenProcessor_counting *token_struct_count) {
    switch (token->type) {
        case 1:
            token_struct_count->keyword_amount++;
            break;
        case 2:
            token_struct_count->identifier_amount++;
            break;
        case 3:
            token_struct_count->number_amount++;
            break;
        case 4:
            token_struct_count->char_consts_amount++;
            break;
        case 5:
            token_struct_count->string_literal_amount++;
            break;
        case 6:
            token_struct_count->punctuator_amount++;
            break;
        case 7:
            token_struct_count->comment_amount++;
            break;
    }
    return token;
}

void
token_destruct_count(struct TokenProcessor_counting *token_struct_count) {
    free(token_struct_count);
}

