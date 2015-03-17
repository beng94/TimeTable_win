#include "data.h"

typedef struct decision
{
    int valid;
    data* _data;
    struct decision* next;
} decision;

typedef struct collisions
{
    decision* dec;
    struct collisions* next;
} collisions;

typedef struct solution
{
    decision* dec;
    collisions* col;
    struct solution* next;
} solution;

void init_decisions(decision** root, data* data_root);
void print_decisions (decision* root);
void back_track (decision* root);
