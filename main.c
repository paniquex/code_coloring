#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "input.h"
#include "analysing.h"
#include "coloring.h"
#include "counting.h"
#include "input_file.h"
#include "input_stdin_type.h"


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
    if (strcmp(argv[1], "1") == 0) {
        if (argv[3] == NULL) {
            fprintf(stderr, "You need to choose processing method: \"coloring\" or \"counting\" in third parametr(input type - 1)");
            return 1;
        }
        if ((strcmp(argv[3], "coloring") != 0) && (strcmp(argv[3], "counting") != 0)) {
            fprintf(stderr, "You need to choose processing method: \"coloring\" or \"counting\" in third parametr(input type - 1)");
            return 1;
        }
    } else if (strcmp(argv[1], "0") == 0) {
        if (argv[2] == NULL) {
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

    char *processing_type;
    if (strcmp(argv[1], "0") == 0) {
        processing_type = argv[2];
        input_stage = input_stdin_type;
    } else {
        processing_type = argv[3];
        input_stage = input_file_type;
    }

    input_file = input_stage(file_name);
    if (input_file == NULL) {
        if ((int) argv[1][0] == '0') {
            unlink(file_name);
        }
        free(file_name);
        perror("Input stage error: ");
        return 1;
    }
    if (processing_stage(processing_type) != 0) {
        if ((int) argv[1][0] == '0') {
            unlink(file_name);
        }
        fclose(input_file);
        free(file_name);
        perror("Coloring stage error: ");
        return 1;
    }
    fclose(input_file);
    if ((int) argv[1][0] == '0') {
        unlink(file_name);
    }
    free(file_name);
    return 0;
}