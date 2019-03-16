#include "input.h"
#include "coloring.h"

FILE *
input_stage(char *input_type, char *input_file_name) {
    size_t file_name_size;
    if ((int) input_type[0] == '0') {
        file_name_size = 37;
        file_name = calloc(file_name_size, sizeof(char));
        return preparing_for_coloring(file_name);
    } else if ((int) input_type[0] == '1') {
        file_name_size = strlen(input_file_name) + 1;
        file_name = calloc(file_name_size, sizeof(char));
        strncpy(file_name, input_file_name, file_name_size);
        FILE *input_file = fopen(file_name, "r+");
        if (input_file == NULL) {
            return NULL;
        }
        return input_file;
    }
    return 0;
}