#include "data.h"

typedef struct decision
{
    int valid;
    data* _data;
    struct decision* next;
} decision;

typedef struct decision_backup
{
    decision* dec;
    struct decision_backup* next;
} decision_backup;

typedef struct solution
{
    decision* dec;
    decision_backup* dec_back;
    struct solution* next;
} solution;

void init_decisions(decision** root, data* data_root);
void print_decisions (decision* root);
void back_track (decision* root);
