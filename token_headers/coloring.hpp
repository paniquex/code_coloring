#ifndef COLORING
#define COLORING
#include "../token_headers/token.hpp"

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

class TokenProcessor_coloring {
    /* DESCRIPTION:
        * It is  child class of TokenProcessor, which is coloring token with process_token function
    */
public:
    void process_token(Token *token);
    void print_token() const;
};

#endif