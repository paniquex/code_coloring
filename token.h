//
// Created by paniquex on 11.04.19.
//

#ifndef CODE_COLORER_TOKEN_H
#define CODE_COLORER_TOKEN_H
#include <string>

enum {KEYWORD = 1, IDENTIFIER, NUMBER, CHAR_CONST, STRING_LITERAL, PUNCTUATOR, COMMENT};

class Token {
private:
    std::string buffer;
    int type;
public:
    std::string get_buffer() const;
    void set_buffer(std::string buffer);
    int get_type() const;
    void set_type(int type);


};

#endif //CODE_COLORER_TOKEN_H
