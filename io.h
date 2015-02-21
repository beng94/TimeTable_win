#include <stdio.h>

static FILE* init_io (const char* file_name);
void read_in (const char* file_name);
int read_line (FILE* f,  char** line);

