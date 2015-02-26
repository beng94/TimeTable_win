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
static char* read_line (FILE* f,  char* line, size_t size)
{
    return (char*) fgets(line, size, f);
}

static void print(data* data)
{
    printf("%s\n", data->lec_code);
    printf("%s\n", data->lec_name);
    printf("%d\n", data->credit);
    printf("%s\n", data->curse_code);
    printf("%d\n", data->curse_type);
    printf("%d\n", data->occas->time->day);
    printf("%d\n", data->occas->time->time_interval->beg_hour);
    printf("%d\n", data->occas->time->time_interval->beg_min);
    printf("%d\n", data->occas->time->time_interval->end_hour);
    printf("%d\n", data->occas->time->time_interval->end_min);
    printf("%s\n", data->occas->room);
    printf("%s\n", data->lecturer);
    printf("%d\n", data->lang);

}

static void parse_line (char* line)
{
    int count = 0;
    char** tokens = get_tokens(line, ";", &count);

    int i;
    for(i = 0; i < count; i++)
    {
        printf("%s\n", tokens[i]);
    }

    data* data;
    init_data(&data);
    add_data(data, tokens);

    print(data);
    //getchar();
}

void read_in (const char* file_name)
{
    FILE *f;

    f = init_io(file_name);

    char line [500];
    fgets(line, sizeof(line), f);

    while(read_line(f, line, sizeof(line)) != NULL)
    {
        change_commas(line, sizeof(line));
        parse_line(line);
    }

    fclose(f);
}

