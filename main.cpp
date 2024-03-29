#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include "analysing.hpp"
#include "token_headers/coloring.hpp"
#include "token_headers/counting.hpp"
#include "headers/input_file.hpp"
#include "headers/input_stdin_type.hpp"
#include "token_headers/token.hpp"


int
output_stage(Token token);
/* DESCRIPTION:
    * output_stage takes 1 parameter - token struct, which will be printed to stdout
    *
 * RETURN VALUES:
    * token struct with colored buffer, if everything was correct
    * nullptr, if buffer or token is nullptr
 */

template<typename processor>
int main_cycle(processor *token_processor_obj, std::fstream *input_file,  char *argv[], std::string file_name, std::string processing_type);


int main(int argc, char *argv[]) {
    /* argv[1] - input type:
        * 0 - program takes input from stdin;
        * 1 - program takes input from file
     * argv[2] - input_file_name:
        * if agrv[1] == 1, then this is name of input file s(NOT BINARY FILE!)
    */

    std::fstream input_file;
    std::string file_name;


    if (argc <= 1) {
        printf("Not enough program parametrs.\n");
        return 1;
    }

    if (argv[2] != nullptr) {
        file_name = argv[2];
    } else if (strcmp(argv[1], "1") == 0) {
        fprintf(stderr, "You need to write file name in mode 1");
        return 1;
    }
    if (strcmp(argv[1], "1") == 0) {
        if (argv[3] == nullptr) {
            fprintf(stderr, "You need to choose processing method: \"coloring\" or \"counting\" in third parametr(input type - 1)");
            return 1;
        }
        if ((strcmp(argv[3], "coloring") != 0) && (strcmp(argv[3], "counting") != 0)) {
            fprintf(stderr, "You need to choose processing method: \"coloring\" or \"counting\" in third parametr(input type - 1)");
            return 1;
        }
    } else if (strcmp(argv[1], "0") == 0) {
        if (argv[2] == nullptr) {
            fprintf(stderr, "You need to choose processing method: \"coloring\" or \"counting\" in second parametr(input type - 0)");
            return 1;
        }
        if ((strcmp(argv[2], "coloring") != 0) && (strcmp(argv[2], "counting") != 0)) {
            fprintf(stderr, "You need to choose processing method: \"coloring\" or \"counting\" in second parametr(input type - 0)");
            return 1;
        }
    }
    if ((strcmp(argv[1], "0") != 0) && (strcmp(argv[1], "1") != 0)) {
        fprintf(stderr, "First argument of program must be 0 or 1");
        return 1;
    }

    std::string processing_type;
    if (strcmp(argv[1], "0") == 0) {
        processing_type = argv[2];
        input_stdin_type(file_name, &input_file);
    } else {
        processing_type = argv[3];
        input_file_type(file_name, &input_file);
    }
    if (processing_type == "coloring") {
        auto *token_colorer = new TokenProcessor_coloring;
        main_cycle(token_colorer, &input_file, argv, file_name, processing_type);
    } else if (processing_type == "counting") {
        auto *token_counter = new TokenProcessor_counting;
        main_cycle(token_counter, &input_file,  argv, file_name, processing_type);
    }
    return 0;
}


int
output_stage(Token token) {
    if (token.get_buffer().length() == 0) {
        fprintf(stdout, "Error in output_stage");
        return -1;
    }
    std::cout << token.get_buffer();
    return 0;
}


template<typename processor>
int main_cycle(processor *token_processor_obj, std::fstream *input_file, char *argv[], std::string file_name, std::string processing_type) {
    Token *current_token;
    while ((current_token = analysing_stage(input_file)) != nullptr) {
        if (current_token->get_type() == 0) {
            delete current_token;
            break;
        } else if (current_token->get_type() == -1) {
            delete current_token;
            return 1;
        }
        token_processor_obj->process_token(current_token);
        output_stage(*current_token);
        delete current_token;
    }
    if (current_token == nullptr) {
        if ((int) argv[1][0] == '0') {
            remove(file_name.c_str());
        }
        input_file->close();
        perror("Coloring stage error: ");
        delete token_processor_obj;
        return 1;
    }
    if (processing_type == "counting") {
        token_processor_obj->print_token();
    }
    input_file->close();
    if ((int) argv[1][0] == '0') {
        remove(file_name.c_str());
    }
    delete token_processor_obj;
    return 0;
}