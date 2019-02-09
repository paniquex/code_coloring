#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>

int number_colorer(int color);


int main() {
    int a;
    number_colorer(1);
   // putchar(fgetc(stdin));
   // putchar(fgetc(0));
    return 0;
}


int number_colorer(int color) {
    int curr_symb, is_first_symb = 1;
    while ((curr_symb = fgetc(stdin)) != EOF) {
        if (isdigit(curr_symb) && (is_first_symb)) {
            printf("\033[0;31m");
            is_first_symb = 0;
        } else if (!(isdigit(curr_symb))) {
            break;
        }
        putchar(curr_symb);
    }
    if (!is_first_symb) {
        printf("\033[0m");
    }
    if (fseek(stdin, -1, SEEK_CUR) == -1) {
        return 1;
    }
    return 0;
}