#include "input_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


FILE *
input_file_type(char *input_file_name) {
    size_t file_name_size;
    file_name_size = strlen(input_file_name) + 1;
    file_name = calloc(file_name_size, sizeof(char));
    strncpy(file_name, input_file_name, file_name_size);
    FILE *input_file = fopen(file_name, "a+");
    if (input_file == NULL) {
        return NULL;
    }
    if (fseek(input_file, 0, SEEK_SET) == -1) {
        fclose(input_file);
        perror("fseek error: ");
        return NULL;
    }
    return input_file;
}