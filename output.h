#ifndef CODE_COLORER_OUTPUT_H
#define CODE_COLORER_OUTPUT_H
#include "analysing.h"

int
output_stage(Token);
/* DESCRIPTION:
    * output_stage takes 1 parameter - token struct, which will be printed to stdout
    *
 * RETURN VALUES:
    * token struct with colored buffer, if everything was correct
    * NULL, if buffer or token is NULL
 */


#endif
