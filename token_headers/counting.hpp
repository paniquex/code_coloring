#ifndef CODE_COLORER_COUNTING_H
#define CODE_COLORER_COUNTING_H

#include "token.hpp"

class TokenProcessor_counting {
    /* DESCRIPTION:
      * It is  child class of TokenProcessor, which counts statistics about
      * every type of token with process_token function
  */

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
    void process_token(Token *token);
    void print_token() const;
};
#endif
