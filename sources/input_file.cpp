#include "input_file.hpp"
#include <string>
#include <iostream>

std::fstream *
input_file_type(std::string input_file_name, std::fstream *input_file) {
    input_file->open(input_file_name, std::fstream::in | std::fstream::binary );
    if (!input_file->is_open()) {
        return nullptr;
    }
    return input_file;
}