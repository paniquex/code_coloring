#include "../headers/input_stdin_type.hpp"

std::fstream *
input_stdin_type(std::string random_file_name, std::fstream *input_file) {
    /* DESCRIPTION:
        * prep_input takes name of file, then create and open with "w+" mode,
        * writing to it all symbols from stdin.
        * RETURN VALUES:
        * 0, if there were no errors
        * 1, else
    */
    random_file_name = "input_file";
    input_file->open(random_file_name, std::fstream::out | std::fstream::in | std::fstream::trunc);
    if (!input_file->is_open()) {
        perror("File didn't open: ");
        return nullptr;
    }
    int curr_symb;
    std::string tmp;
    while ((curr_symb = getchar()) != EOF) {
        *input_file << (char) curr_symb;
    }
    input_file->seekg(0, std::fstream::beg);
    return input_file;
}