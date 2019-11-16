#include "../token_headers/counting.hpp"

TokenProcessor_counting::TokenProcessor_counting() {
    keyword_amount = 0;
    char_consts_amount = 0;
    comment_amount = 0;
    identifier_amount = 0;
    number_amount = 0;
    punctuator_amount = 0;
    string_literal_amount = 0;
}

void TokenProcessor_counting::process_token(Token *token) {
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


void TokenProcessor_counting::print_token() const {
    printf("\n\nSTATISTICS:");
    printf("\nComments amount: %d\n", this->comment_amount);
    printf("Keywords amount: %d\n", this->keyword_amount);
    printf("Identifiers amount: %d\n", this->identifier_amount);
    printf("Numbers amount: %d\n", this->number_amount);
    printf("Char consts amount: %d\n", this->char_consts_amount);
    printf("Punctuators amount: %d\n", this->punctuator_amount);
    printf("String literals amount: %d\n", this->string_literal_amount);
}