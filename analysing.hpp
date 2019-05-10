#ifndef ANALYSING
#define ANALYSING


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include "headers/input_file.hpp"
#include "token_headers/token.hpp"




Token *
analysing_stage(std::fstream *input_file);
/* DESCRIPTION:
    * сoloring_stage takes 4 parameters, which are needed for punctuator_analyser and keyword_analyser functions.
    * analysing_stage() contains all analyser functions:
    * 0) white_space_print_skip
    * 1) comment_analyser
    * 2) sting_literal_analyser
    * 3) char_consts_analyser
    * 4) keyword_analyser
    * 5) identifier_analyser(with ucn analyser)
    * 6) number_analyser
    * 7) punctuator_analyser
    * 8) just putchar(curr_symb), if symbol don't match any pattern
 * RETURN VALUES:
    * token with right type, if everything was correct
    * token pointer with type -1, if fgetc(input_file) occurs an error
    * token pointer with type -2, if some of analysers occurs an error
 */


#endif        