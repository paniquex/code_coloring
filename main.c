#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "input.h"
#include "analysing.h"


int main(int argc, char *argv[]) {
    /* argv[1] - input type:
        * 0 - program takes input from stdin;
        * 1 - program takes input from file
     * argv[2] - input_file_name:
        * if agrv[1] == 1, then this is name of input file s(NOT BINARY FILE!)
    */

    if (argc <= 1) {
        printf("Not enough program parametrs.\n");
        return 1;
    }

    if (argv[2] != NULL) {
        file_name = argv[2];
    } else if (strcmp(argv[1], "1") == 0) {
        fprintf(stderr, "You need to write file name in mode 1");
        return 1;
    }
    if ((strcmp(argv[1], "0") != 0) && (strcmp(argv[1], "1") != 0)) {
        fprintf(stderr, "First argument of program must be 0 or 1");
        return 1;
    }

    int keyword_max_length = 0;
    char **keywords;
    keywords = keywords_array_init(&keyword_max_length); //keywords array initializer

    int punctuator_max_length = 0;
    char **punctuators;
    punctuators = punctuators_array_init(&punctuator_max_length); //punctuators array initialize

    input_file = input_stage(argv[1], file_name);
    if (input_file == NULL) {
        free(keywords);
        free(punctuators);
        free(file_name);
        perror("Input stage error: ");
        return 1;
    }
    if (analysing_stage(punctuators, punctuator_max_length, keywords, keyword_max_length) != 0) {
        free(keywords);
        free(punctuators);
        free(file_name);
        perror("Coloring stage error: ");
        return 1;
    }
    fclose(input_file);
    if ((int) argv[1][0] == '0') {
        unlink(file_name);
    }
    free(file_name);
    free(keywords);
    free(punctuators);

    return 0;
}