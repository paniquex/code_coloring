#ifndef COLORING
#define COLORING
#include "token.h"
#include "token_processing.h"

class TokenProcessor_coloring: public TokenProcessor  {
private:
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


public:
    void process_token(Token *token) {
        /* DESCRIPTION:
    * token_coloring takes 2 parameters, first - Token struct, second - color in which we need to color our Token
    *
 * RETURN VALUES:
    * token struct with colored buffer, if everything was correct
    * NULL, if buffer or token is NULL
 */
        std::string color;
        switch (token->get_type()) {
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
        token->set_buffer(color + token->get_buffer());
        token->set_buffer(token->get_buffer() + NOCOLOR);
    }
};

#endif