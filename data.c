#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data.h"

static time_interval* init_time_interval()
{
    time_interval *tmp = (time_interval*)malloc(sizeof(time_interval));
    tmp->beg_hour = 0;
    tmp->beg_min = 0;
    tmp->end_hour = 0;
    tmp->end_min = 0;

    return tmp;
}

static time* init_time()
{
    time* tmp = (time*)malloc(sizeof(time));
    tmp->day = days_not_set;
    tmp->time_interval = init_time_interval();

    return tmp;
}

static language set_language (char* str)
{
    if(strcmp(str, "magyar") == 0) return hun;
    if(strcmp(str, "német") == 0) return ger;
    if(strcmp(str, "angol") == 0) return eng;

    fprintf(stderr, "\nUnkown language\n");
    return language_not_set;
}

static curse_type set_curse_type (char* str)
{
    //TODO: tolower
    if(strcmp(str, "Elmélet") == 0) return lecture;
    if(strcmp(str, "Gyakorlat") == 0) return practice;
    if(strcmp(str, "Labor") == 0) return lab;

    fprintf(stderr, "\nUnkown curse_type");
    return curse_not_set;
}

static occassion* init_occassion()
{
    occassion* occ = (occassion*)malloc(sizeof(occassion));
    occ->next = NULL;
    occ->room = NULL;
    occ->time = init_time();

    return occ;
}

void init_data (data **_data)
{
    *_data = (data*)malloc(sizeof(data));
    (*_data)->lec_code = NULL;
    (*_data)->lec_name = NULL;
    (*_data)->credit = 0;
    (*_data)->curse_code = NULL;
    (*_data)->curse_type = curse_not_set;
    (*_data)->occas = init_occassion();
    (*_data)->lecturer = NULL;
    (*_data)->lang = days_not_set;
}

//TODO: free data

void add_data (data* data, char* str, int arg_num)
{
    switch(arg_num)
    {
    case 0:
        data->lec_code = strdup(str);
        break;
    case 1:
        data->lec_name = strdup(str);
        break;
    case 2:
        data->credit = atoi(str);
        break;
    //case 3: Waiting list
    case 4:
        data->curse_code = strdup(str);
        break;
    case 5:
        data->curse_type = set_curse_type(str);
        break;
    //case 6: Fõ/Várólista/Limit
    case 7:
        //TODO: date, room
        break;
    case 8:
        data->lecturer = strdup(str);
        break;
    case 9:
        data->lang = set_language(str);
        break;
    default:
        fprintf(stderr, "\nMore args than expected\n");
        break;
    }
}
