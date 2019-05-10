#ifndef CODE_COLORER_TOKEN_PROCESSING_H
#define CODE_COLORER_TOKEN_PROCESSING_H
#include "token.hpp"


class TokenProcessor {
/* DESCRIPTION:
 *  TokenProcessor is abstract class, which has 2 virtual methods and 1 virtual destructor
*/
public:
    virtual void process_token(Token *token) = 0;
/* DESCRIPTION:
 * process_token takes Token and do something with Token class
 */
    virtual void print_token() const {}
    virtual ~TokenProcessor() = default;
};

#endif
