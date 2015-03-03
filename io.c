#include <windows.h>
#include "io.h"

//TODO: make it nice... :)
//At lectures there might be ';' between rooms
//Maybe it should be in init_io
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
static char* read_line (FILE* f, char* line, size_t size)
{
    return (char*) fgets(line, size, f);
}

void print_data(const data* data)
{
    printf("%s\n", data->lec_code);
    printf("%s\n", data->lec_name);
    printf("%d\n", data->credit);
    printf("%s\n", data->curse_code);
    printf("%d\n", data->curse_type);
    printf("%d: ", data->occas->time->day);
    printf("%d:", data->occas->time->time_interval->beg_hour);
    printf("%d-", data->occas->time->time_interval->beg_min);
    printf("%d:", data->occas->time->time_interval->end_hour);
    printf("%d", data->occas->time->time_interval->end_min);
    printf(" (%s)\n", data->occas->room);
    printf("%s\n", data->lecturer);
    printf("%d\n", data->lang);

}

static void add_data_to_list (data** root, data* new_data)
{
    if(*root == NULL)
    {
        *root = new_data;
    }

    else
    {
        data* tmp = *root;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        tmp->next = new_data;
    }
}

static void parse_line (data** root, const char* line)
{
    int count = 0;
    char** tokens = get_tokens(line, ";", &count);

    data* new_data = init_data();
    set_data(new_data, tokens);
    add_data_to_list(root, new_data);
}

void print_data_list (data* root)
{
    data* tmp = root;
    while(tmp != NULL)
    {
        print_data(tmp);
        tmp = tmp->next;
    }
}

void read_in (data** root, const char* file_name)
{
    FILE *f;
    data* data_list = NULL;

    f = init_io(file_name);

    char line [500];
    fgets(line, sizeof(line), f);

    while(read_line(f, line, sizeof(line)) != NULL)
    {
        change_commas(line, sizeof(line));
        parse_line(&data_list, line);
    }

    print_data_list(data_list);

    *root = data_list;

    fclose(f);
}

