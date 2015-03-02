#include "data.h"

typedef struct decision
{
    data* _data;
    int valid;
    struct decision* next;
} decision;

void init_decisions(decision** root, data* data_root);
