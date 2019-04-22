#include "input_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


std::fstream *
input_file_type(std::string input_file_name, std::fstream *input_file) {
    input_file->open(input_file_name, std::fstream::in );
    if (!input_file->is_open()) {
        return nullptr;
    }
    return input_file;
}