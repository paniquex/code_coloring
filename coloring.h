const char *BLACK = "\033[0;30m";
const char *DARKGRAY = "\033[1;30m";
const char *RED = "\0330[;31m";
const char *LIGHTRED = "\033[1;31m";
const char *GREEN = "\033[0;32m";
const char *LIGHTGREEN = "\033[1;32m";
const char *BROWN = "\033[0;33m";
const char *YELLOW = "\033[1;33m";
const char *BLUE = "\033[0;34m";
const char *LIGHTBLUE = "\033[1;34m";
const char *PURPLE = "\033[0;35m";
const char *LIGHTPURPLE = "\033[1;35m";
const char *CYAN = "\033[0;36m";
const char *LIGTHCYAN = "\033[1;36m";
const char *LIGHTGRAY = "\033[0;37m";
const char *WHITE = "\033[1;37m";
const char *NOCOLOR = "\033[0m";

int
token_coloring(int token_type, char *color);
