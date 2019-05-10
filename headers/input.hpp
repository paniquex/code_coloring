#ifndef INPUT
#define INPUT
#include <stdio.h>
#include <uuid/uuid.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


std::fstream *
(* input_stage)(std::string, std::fstream *input_file);
/* DESCRIPTION:
       * input_stage takes:
       * 1) input_file_name. It is name of input file..
       * 2) input_file - file stream to input.

    * RETURN VALUES:
       * pointer to file stream - if function works correctly
       * nullptr - if somekind of error was found
   */

#endif