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
static int read_line (FILE* f,  char* line, size_t size)
{
    fgets(line, size, f);
    return 1;

    //return (fgets(line, sizeof(line), f) != EOF);
}

static void parse_line (char* line)
{
    //TODO: strtok
    data* data;
    init_data(&data);

    char* token = strtok(line, ";");
    add_data(data, token, 0);

    while(token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ";");
    }
}

void read_in (const char* file_name)
{
    FILE *f;

    f = init_io(file_name);

    char line [500];
    while(read_line(f, line, sizeof(line)))
    {
            parse_line(line);
            getchar();
    }

    fclose(f);
}

