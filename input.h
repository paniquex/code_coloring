#include <stdio.h>
#include <uuid/uuid.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

FILE *input_file;
char *file_name;

FILE *
input_stage(char *input_type, char *input_file_name);
/* DESCRIPTION:
       * input_stage takes:
       * 1) input_type, which indicates type of input..
           * if input_type == 0, then preparing_for_coloring func will work
           * if input_type == 1, then program will read symbols from file with name input_file_name
       * 2) input_file_name. It is name of input file..
    * RETURN VALUES:
       * pointer to working file - if function works correctly
       * NULL - if somekind of error was found
   */


FILE *
prep_input(char *random_file_name);
/* DESCRIPTION:
    * prep_input takes name of file, then create and open with "w+" mode,
    * writing to it all symbols from stdin.
 * RETURN VALUES:
    * 0, if there were no errors
    * 1, else
 */


void
free_memory_input();