#ifndef INPUT
#define INPUT
#include "input.h"


FILE *
input_stage(char *input_type, char *input_file_name) {
    size_t file_name_size;
    if ((int) input_type[0] == '0') {
        file_name_size = 37;
        file_name = calloc(file_name_size, sizeof(char));
        return prep_input(file_name);
    } else if ((int) input_type[0] == '1') {
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
    return 0;
}


FILE *
prep_input(char *random_file_name) {
    uuid_t binuuid;
    uuid_generate_random(binuuid);
    uuid_unparse_upper(binuuid, random_file_name);
    unlink(random_file_name);

    FILE *input_file = fopen(random_file_name, "w+");
    if (input_file == NULL) {
        perror("File didn't open: ");
        return NULL;
    }
    int curr_symb;
    while ((curr_symb = getchar()) != EOF) {
        if (fprintf(input_file, "%c", curr_symb) <= 0) {
            fclose(input_file);
            perror("Cannot write to file: ");
            return NULL;
        }
        if (fseek(input_file, 0, SEEK_SET) == -1) {
            fclose(input_file);
            perror("fseek error: ");
            return NULL;
        }
        return input_file;
    }
}

#endif