#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "data.h"

static void init_time_interval(time_interval **_interval)
{
    *_interval = (time_interval*)malloc(sizeof(time_interval));
    (*_interval)->beg_hour = 0;
    (*_interval)->beg_min = 0;
    (*_interval)->end_hour = 0;
    (*_interval)->end_min = 0;
}

static void init_time(time **_time)
{
    *_time = (time*)malloc(sizeof(time));
    (*_time)->day = days_not_set;
    (*_time)->time_interval = NULL;
    init_time_interval(&((*_time)->time_interval));
}

static language set_language (char* str)
{
    if(strcmp(str, "magyar") == 0) return hun;
    if(strcmp(str, "német") == 0) return ger;
    if(strcmp(str, "angol") == 0) return eng;

    fprintf(stderr, "Unkown language\n");
    return language_not_set;
}

static curse_type set_curse_type (char* str)
{
    //TODO: tolower
    if(strcmp(str, "Elmélet") == 0) return lecture;
    if(strcmp(str, "Gyakorlat") == 0) return practice;
    if(strcmp(str, "Labor") == 0) return lab;

    fprintf(stderr, "Unkown curse_type");
    return curse_not_set;
}

void init_data (data **_data)
{
    *_data = (data*)malloc(sizeof(data));
    (*_data)->lec_code = NULL;
    (*_data)->lec_name = NULL;
    (*_data)->credit = 0;
    (*_data)->curse_code = NULL;
    (*_data)->curse_type = curse_not_set;
    (*_data)->time = NULL;
    init_time(&((*_data)->time));
    (*_data)->room = NULL;
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
    case 3: //Felvételek száma
        break;
    case 4: //Várólista
        break;
    case 5:
        data->curse_code = strdup(str);
        break;
    case 6:
        data->curse_type = set_curse_type(str);
        break;
    case 7: //Fõ/Várólista/Limit
        break;
    case 8: //empty
        break;
    case 9: //empty
        break;
    case 10:
        //TODO: date, room
        break;
    case 11:
        data->lecturer = strdup(str);
        break;
    case 12:
        data->lang = set_language(str);
        break;
    default:
        fprintf(stderr, "More args than expected");
        break;
    }
}
