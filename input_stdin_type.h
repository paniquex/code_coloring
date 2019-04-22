#ifndef CODE_COLORER_INPUT_STDIN_TYPE_H
#define CODE_COLORER_INPUT_STDIN_TYPE_H
#include "input_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

std::fstream *
input_stdin_type(std::string input_file_name, std::fstream *input_file);

#endif
