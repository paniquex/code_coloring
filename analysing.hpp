#ifndef ANALYSING
#define ANALYSING


#include "input_file.hpp"
#include "token.hpp"




Token *
analysing_stage(std::fstream *input_file);
/* DESCRIPTION:
    * analysing stage takes 1 parameter.
    * analysing_stage contains all analyser functions:
    * 0) white_space_print_skip
    * 1) comment_analyser
    * 2) sting_literal_analyser
    * 3) char_consts_analyser
    * 4) keyword_analyser
    * 5) identifier_analyser(with ucn analyser)
    * 6) number_analyser
    * 7) punctuator_analyser
    *
 * RETURN VALUES:
    * token pointer with right type, if everything was correct
    * token pointer with type 8, if no token was found
    * token pointer with type -1, if fgetc(input_file) occurs an error
    * token pointer with type -2, if some of analysers occurs an error
 */


#endif        