#include "../token_headers/coloring.hpp"
#include <iostream>

void TokenProcessor_coloring::process_token(Token *token) {
    /* DESCRIPTION:
* token_coloring takes 1 parameter, first - Token struct
*
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


void TokenProcessor_coloring::print_token() const {
    std::cout << KEYWORD << '-' << BLUE;
    std::cout << IDENTIFIER << '-' << LIGHTPURPLE;
    std::cout << NUMBER << '-' << LIGHTBLUE;
    std::cout << CHAR_CONST << '-' << YELLOW;
    std::cout << STRING_LITERAL << '-' << GREEN;
    std::cout << PUNCTUATOR << '-' << RED;
    std::cout << COMMENT << '-' << DARKGRAY;
}