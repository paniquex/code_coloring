#ifndef CODE_COLORER_COUNTING_H
#define CODE_COLORER_COUNTING_H

#include "token_processing.h"

class TokenProcessor_counting: public TokenProcessor  {
private:
    unsigned int keyword_amount;
    unsigned int identifier_amount;
    unsigned int number_amount;
    unsigned int char_consts_amount;
    unsigned int string_literal_amount;
    unsigned int punctuator_amount;
    unsigned int comment_amount;


public:
    TokenProcessor_counting();
    void process_token(Token *token) {
        switch (token->get_type()) {
            case KEYWORD:
                keyword_amount++;
                break;
            case IDENTIFIER:
                identifier_amount++;
                break;
            case NUMBER:
                number_amount++;
                break;
            case CHAR_CONST:
                char_consts_amount++;
                break;
            case STRING_LITERAL:
                string_literal_amount++;
                break;
            case PUNCTUATOR:
                punctuator_amount++;
                break;
            case COMMENT:
                comment_amount++;
                break;
        }
    }
    void output_count_statistics() const;
};

int
token_init_count(TokenProcessor_counting **token_struct_count);

void
output_count_statistics(TokenProcessor_counting *);

Token *
token_counting(Token *token, TokenProcessor_counting *token_struct_count);

void
token_destruct_count(TokenProcessor_counting *token_struct_count);

#endif
