#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "IO.h"

void read_in (const char* file_name)
{
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    FILE *f = fopen(file_name, "r");

    if(!f)
    {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }

    char line[500];

    while((fgets(line, sizeof(line), f)) != EOF)
    {
            printf("%s", line);
            getchar();
    }

    char *new_line;
    new_line = strtok(line, ";");


    fclose(f);
}

