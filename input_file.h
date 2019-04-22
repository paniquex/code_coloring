#ifndef INPUT_FILE
#define INPUT_FILE
//#include "input.h"
#include <stdio.h>
#include <uuid/uuid.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>


std::fstream *
input_file_type(std::string input_file_name, std::fstream *input_file);

#endif