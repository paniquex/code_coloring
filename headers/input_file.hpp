#ifndef INPUT_FILE
#define INPUT_FILE

#include <fstream>


std::fstream *
input_file_type(std::string input_file_name, std::fstream *input_file);
/* DESCRIPTION:
   * input_stage takes:
   * 1) input_file_name. It is name of input file..
   * 2) input_file - file stream to input.

* RETURN VALUES:
   * pointer to file - if function works correctly
   * nullptr - if somekind of error was found
*/
#endif