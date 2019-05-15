#ifndef COLORING
#define COLORING
#include "token.hpp"
#include "token_processing.hpp"

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

class TokenProcessor_coloring: public TokenProcessor  {
    /* DESCRIPTION:
        * It is  child class of TokenProcessor, which is coloring token with process_token function
    */
public:
    void process_token(Token *token) {
/* DESCRIPTION:
    * token_coloring takes 1 parameter, first - Token struct
    * by token type it colors token in the right color
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
            case 8: color = LIGHTPURPLE;
                break;
        }
        token->set_buffer(color + token->get_buffer());
        token->set_buffer(token->get_buffer() + NOCOLOR);
    }
};

#endif