//#include <stdio.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
//#include "analysing.h"
//#include "coloring.h"
//#include "counting.h"
#include "input_file.h"
//#include "token_processing.h"
#include "input_stdin_type.h"

//int
//output_stage(Token token);
/* DESCRIPTION:
    * output_stage takes 1 parameter - token struct, which will be printed to stdout
    *
 * RETURN VALUES:
    * token struct with colored buffer, if everything was correct
    * nullptr, if buffer or token is nullptr
 */


int main(int argc, char *argv[]) {
    /* argv[1] - input type:
        * 0 - program takes input from stdin;
        * 1 - program takes input from file
     * argv[2] - input_file_name:
        * if agrv[1] == 1, then this is name of input file s(NOT BINARY FILE!)
    */
    std::fstream f;
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
        input_stdin_type(file_name, &f);
    } else {
        processing_type = argv[3];
        input_file_type(file_name, &f);
    }
    char curr_symb;
    while (f.read(&curr_symb, 1)) {
        std::cout << curr_symb;
    }
    f.close();















/*    if (argc <= 1) {
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
        input_stage = input_stdin_type;
    } else {
        processing_type = argv[3];
        input_stage = input_file_type;
    }
    if (processing_type == "coloring") {
        token_init = (int (* ) (TokenProcessor **)) token_init_color;
        token_destruct = (void (* ) (TokenProcessor *)) token_destruct_color;
    } else if (processing_type == "counting") {
        token_init = (int (*) (TokenProcessor **)) token_init_count;
        token_destruct = (void (*) (TokenProcessor *)) token_destruct_count;
    }
    TokenProcessor *token_processing_struct; //init processing func
    token_init(&token_processing_struct);

    input_file = input_stage(file_name);
    if (input_file == nullptr) {
        if ((int) argv[1][0] == '0') {
            unlink(file_name);
        }
        free(file_name);
        perror("Input stage error: ");
        return 1;
    }
    Token *current_token;
    while ((current_token = analysing_stage()) != nullptr) {
        if (current_token->type == 0) {
            break;
        }
        token_processing_struct->process_token(current_token, token_processing_struct);
        output_stage(*current_token);
        free(current_token);
    }
    if (current_token == nullptr) {
        if ((int) argv[1][0] == '0') {
            unlink(file_name);
        }
        fclose(input_file);
        token_destruct(token_processing_struct);
        free(file_name);
        perror("Coloring stage error: ");
        return 1;
    }
    free(current_token);
    if (strcmp(processing_type, "counting") == 0) {
        output_count_statistics((TokenProcessor_counting *) token_processing_struct);
    }
    fclose(input_file);
    if ((int) argv[1][0] == '0') {
        unlink(file_name);
    }
    token_destruct(token_processing_struct);
    free(file_name);
    return 0;
}


int
output_stage(Token token) {
    if (token.buffer == nullptr) {
        fprintf(stdout, "Error in output_stage");
        return -1;
    }
    printf("%s", token.buffer);
    return 0;
    */
}