#include "token.h"


std::string Token::get_buffer() const {
    return this->buffer;
}

void Token::set_buffer(std::string buffer) {
    this->buffer = buffer;
}

int Token::get_type() const {
    return this->type;

}

void Token::set_type(int type) {
    this->type = type;
}

