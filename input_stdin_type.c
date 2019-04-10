#include "input_stdin_type.h"


static FILE *
prep_input(char *random_file_name) {
    /* DESCRIPTION:
    * prep_input takes name of file, then create and open with "w+" mode,
    * writing to it all symbols from stdin.
 * RETURN VALUES:
    * 0, if there were no errors
    * 1, else
 */
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
    }
    if (fseek(input_file, 0, SEEK_SET) == -1) {
        fclose(input_file);
        perror("fseek error: ");
        return NULL;
    }
    return input_file;
}


FILE *
input_stdin_type(char *input_file_name) {
    size_t file_name_size;
    file_name_size = 37;
    file_name = calloc(file_name_size, sizeof(char));
    return prep_input(file_name);
}