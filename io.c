#include <string.h>
#include <windows.h>
#include "io.h"
#include "data.h"

static FILE* init_io (const char* file_name)
{
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);

    FILE* f = fopen(file_name, "r");

    if(!f)
    {
        fprintf(stderr, "Cannot open file");
        exit(EXIT_FAILURE);
    }

    return f;
}

//TODO: It's unsafe
//TODO: reads only 3 characters
int read_line (FILE* f,  char** line)
{
    printf("%d", sizeof(line));
    return fgets(line, sizeof(line), f);
}

void parse_line ()
{
//TODO: strtok
}

void read_in (const char* file_name)
{
    FILE *f;

    f = init_io(file_name);

    char line[500];
    printf("%d", sizeof(line));

    while(read_line(f, &line)!= EOF)
    {
            printf("%s", line);
            getchar();
    }

    fclose(f);
}

