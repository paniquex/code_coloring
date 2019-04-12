#include "output.h"
#include "token_processing.h"
#include "counting.h"

int
output_stage(Token token) {
if (token.buffer == NULL) {
fprintf(stdout, "Error in output_stage");
return -1;
}
printf("%s", token.buffer);
return 0;
}
