#ifndef CODE_COLORER_INPUT_STDIN_TYPE_H
#define CODE_COLORER_INPUT_STDIN_TYPE_H

#include "input_file.hpp"

std::fstream *
input_stdin_type(std::string input_file_name, std::fstream *input_file);
/* DESCRIPTION:
* input_stage takes:
* 1) input_file_name. It is name of input file..
* 2) input_file - file stream to input.

* RETURN VALUES:
* pointer to stdin file stream - if function works correctly
* nullptr - if somekind of error was found
*/
#endif
