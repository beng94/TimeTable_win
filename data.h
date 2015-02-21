typedef enum curse_type
{
    lecture,
    practice,
    lab
} curse_type;

typedef enum days
{
    mon,
    tues,
    wed,
    thu,
    fri
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
    time_interval time_interval;
} time;

typedef enum language
{
    hun,
    eng,
    ger
} language;

typedef struct data
{
    char* lec_code;
    char* lec_name;
    int credit;
    char* curse_code;
    curse_type curse_type;
    time time;
    char* room;
    char* lecturer;
    language lang;
} data;