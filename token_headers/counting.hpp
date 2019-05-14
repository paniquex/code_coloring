#ifndef CODE_COLORER_COUNTING_H
#define CODE_COLORER_COUNTING_H
#include "token_processing.hpp"

class TokenProcessor_counting: public TokenProcessor  {
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
    void process_token(Token *token) {
/* DESCRIPTION:
*  process_token takes pointer to Token
 *  It adds amount by the type of Token.
*/
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
    void print_token() const;
};
#endif
