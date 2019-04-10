#include <stdio.h>
#include <uuid/uuid.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

FILE *input_file;
char *file_name;

FILE *
(* input_stage)(char *);
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