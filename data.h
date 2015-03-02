#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef DATA_H
#define DATA_H

typedef enum curse_type
{
    lecture,
    practice,
    lab,
    curse_not_set
} curse_type;

typedef enum days
{
    mon,
    tues,
    wed,
    thu,
    fri,
    days_not_set
} days;

typedef struct time_interval
{
    int beg_hour;
    int beg_min;
    int end_hour;
    int end_min;
} time_interval;

typedef struct time
{
    days day;
    time_interval* time_interval;
} time;

typedef enum language
{
    hun,
    eng,
    ger,
    language_not_set
} language;

typedef struct occassion
{
    time* time;
    char* room;
    struct occassion* next;

} occassion;

//TODO: lec_name -> curse_name
typedef struct data
{
    char* lec_code;
    char* lec_name;
    int credit;
    char* curse_code;
    curse_type curse_type;
    occassion* occas;
    char* lecturer;
    language lang;
    struct data* next;
} data;

data* init_data ();
void set_data (data* data, char** const tokens);
char** get_tokens (const char* line, const char* separetor, int* count);
void free_datas(data* data);

#endif // DATA_H
