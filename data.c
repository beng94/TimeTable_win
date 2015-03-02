#include "data.h"
//TODO: free tokens

static language set_language (const char* str)
{
    if(strcmp(str, "magyar") == 0) return hun;
    if(strcmp(str, "német") == 0) return ger;
    if(strcmp(str, "angol") == 0) return eng;

    fprintf(stderr, "\nUnkown language\n");
    return language_not_set;
}

static curse_type set_curse_type (const char* str)
{
    //TODO: tolower
    if(strcmp(str, "Elmélet") == 0) return lecture;
    if(strcmp(str, "Gyakorlat") == 0) return practice;
    if(strcmp(str, "Labor") == 0) return lab;

    fprintf(stderr, "\nUnkown curse_type");
    return curse_not_set;
}

static time_interval* set_time_interval(const char** tokens)
{
    time_interval* tmp = (time_interval*)malloc(sizeof(time_interval));

    tmp->beg_hour = atoi(tokens[1]);
    tmp->beg_min = atoi(tokens[2]);
    tmp->end_hour = atoi(tokens[3]);
    tmp->end_min = atoi(tokens[4]);

    return tmp;
}

static days set_day(const char* str)
{
    if(strcmp(str, "H") == 0) return mon;
    if(strcmp(str, "K") == 0) return tues;
    if(strcmp(str, "SZE") == 0) return wed;
    if(strcmp(str, "CS") == 0) return thu;
    if(strcmp(str, "P") == 0) return fri;

    return days_not_set;
}

static time* set_time(const char** tokens)
{
    time* tmp = (time*)malloc(sizeof(time));
    tmp->day = set_day(tokens[0]);
    tmp->time_interval = set_time_interval(tokens);

    return tmp;
}

//Tokens must be freed
char** get_tokens (const char* line, const char* separetor, int* count)
{
    (*count) = 1;
    char** result = (char**)malloc(sizeof(char*));

    char* str = strdup(line);
    char* token = strtok(str, separetor);
    result[0] = strdup(token);

    while((token = strtok(NULL, separetor)) != NULL)
    {
        result = realloc(result, sizeof(*result) * ((*count) + 1));
        result[(*count)] = strdup(token);
        (*count)++;
    }

    free(str);
    return result;
}

static void add_occassion(occassion* root, occassion* new)
{
    occassion* tmp = root;
    while(tmp->next)
    {
        tmp = tmp->next;
    }

    tmp->next = new;
}

static occassion* parse_occassion(char* str)
{
    int count = 0;
    char** tokens = get_tokens(str, "\":-()", &count);

    occassion* tmp = (occassion*)malloc(sizeof(occassion));
    tmp->time = set_time(tokens);
    tmp->room = strdup(tokens[5]);
    tmp->next = NULL;

    //TODO: free tokens
    return tmp;
}

static occassion* parse_occassions (const char* str)
{
    int count = 0;
    char** tokens = get_tokens(str, "$\"", &count);

    occassion* tmp = parse_occassion(tokens[0]);

    int i;
    for(i = 1; i < count; i++)
    {
        occassion* new = parse_occassion(tokens[i]);
        add_occassion(tmp, new);
    }

    return tmp;
}

data* init_data ()
{
    data* tmp = (data*)malloc(sizeof(data));
    tmp->lec_code = NULL;
    tmp->lec_name = NULL;
    tmp->credit = 0;
    tmp->curse_code = NULL;
    tmp->curse_type = curse_not_set;
    tmp->occas = NULL;
    tmp->lecturer = NULL;
    tmp->lang = days_not_set;
    tmp->next = NULL;

    return tmp;
}

static void free_time(time* time)
{
    free(time->time_interval);
}

static void free_occassions (occassion* occass)
{
    occassion* tmp = occass->next;
    free(occass->room);
    free_time(occass->time);
    free(occass);

    while(tmp != NULL)
    {
        free(tmp->room);
        free_time(tmp->time);
        free(tmp);
        tmp = tmp->next;
    }
}

void free_datas(data* dt)
{
    data* tmp = dt->next;

    free(dt->lec_code);
    free(dt->lec_name);
    free(dt->curse_code);
    free_occassions(dt->occas);
    free(dt->lecturer);
    free(dt);

    while(tmp != NULL)
    {
        tmp = tmp->next;

        free(tmp->lec_code);
        free(tmp->lec_name);
        free(tmp->curse_code);
        free_occassions(tmp->occas);
        free(tmp->lecturer);
        free(tmp);

    }
}

void set_data (data* data, char** const tokens)
{
    data->lec_code = strdup(tokens[0]);
    data->lec_name = strdup(tokens[1]);
    data->credit = atoi(tokens[2]);
    data->curse_code = strdup(tokens[4]);
    data->curse_type = set_curse_type(tokens[5]);
    data->occas = parse_occassions(tokens[7]);
    data->lecturer = strdup(tokens[8]);
    data->lang = set_language(tokens[9]);
}
