#include <string.h>
#include <windows.h>
#include "io.h"
#include "data.h"

//TODO: make it nice... :)
//At lectures there might be ';' between rooms
static void change_commas(char* str, size_t len)
{
    int i = 0;
    while(i < len)
    {
        if(str[i] == '\"')
        {
            i++;
            break;
        }
        i++;
    }

    while(i < len)
    {
        if(str[i] == '\"') break;
        if(str[i] == ';') str[i] = '$';
        i++;
    }
}

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
//always returns 1!!
static int read_line (FILE* f,  char* line, size_t size)
{
    fgets(line, size, f);
    return 1;
}

static void print(data* data)
{
    printf("%s\n%s\n%d\n%s\n%s\n%d",
           data->lec_code,
           data->lec_name,
           data->credit,
           data->curse_code,
           data->lecturer,
           data->lang
           );
    printf("----------------------------");
}

static void parse_line (char* line)
{
    //TODO: strtok
    data* data;
    init_data(&data);

    char* token = strtok(line, ";");
    add_data(data, token, 0);

    int i = 1;
    while(token != NULL)
    {
        printf("%s\n", token);
        token = strtok(NULL, ";");
        add_data(data, token, i);
        i++;
    }
    print(data);
}

void read_in (const char* file_name)
{
    FILE *f;

    f = init_io(file_name);

    char line [500];
    fgets(line, sizeof(line), f);

    while(read_line(f, line, sizeof(line)))
    {
        change_commas(line, sizeof(line));
        getchar();
        parse_line(line);
        getchar();
    }

    fclose(f);
}

