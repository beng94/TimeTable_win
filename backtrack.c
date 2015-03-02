#include "backtrack.h"

static int interval_collision (time* _time1, time* _time2)
{
    time* t1 = _time1;
    time* t2 = _time2;

    if(t1->day == t2->day)
    {
        if(t1->time_interval->beg_hour >= t2->time_interval->beg_hour &&
           t1->time_interval->beg_min >= t2->time_interval->beg_min)
        {
            time* tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        if(t1->time_interval->end_hour >= t2->time_interval->beg_hour &&
           t1->time_interval->end_min > t2->time_interval->beg_min &&
           t1->time_interval->end_hour <= t2->time_interval->end_hour &&
           t1->time_interval->end_min < t2->time_interval->end_min)
        {
            return 1;
        }
    }

    return 0;
}

static int time_collision (occassion* oc1, occassion* oc2)
{
    occassion* tmp;
    for(tmp = oc1; tmp; tmp = tmp->next)
    {
        occassion* tmp1;
        for(tmp1 = oc2; tmp1; tmp1 = tmp1->next)
        {
            if(interval_collision(tmp->time, tmp1->time)) return 1;
        }
    }

    return 0;
}

static int type_collision(curse_type crs1, curse_type crs2)
{
    if(crs1 == crs2) return 1;

    return 0;
}

static int collision_detect(data* dt1, data* dt2)
{
    if(type_collision(dt1->curse_type, dt2->curse_type)) return 1;
    if(time_collision(dt1->occas, dt2->occas)) return 1;

    return 0;
}

static void collision_handle(decision* root, decision* dec)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        //TODO: what if it checks itself?
        if(collision_detect(tmp->_data, dec->_data))
        {
            tmp->valid = 0;
        }

        tmp = tmp->next;
    }
}

static void add_decision (decision** root, decision* new_dec)
{
    if(*root == NULL)
    {
        *root = new_dec;
    }
    else
    {
        decision* tmp = *root;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        tmp->next = new_dec;
    }
}

void init_decisions(decision** root, data* data_root)
{
    data* tmp = data_root;
    while(tmp != NULL)
    {
        decision* new_dec = (decision*)malloc(sizeof(decision));
        new_dec->_data = tmp;
        new_dec->valid = 1;
        new_dec->next = NULL;

        add_decision(root, new_dec);
        tmp = tmp->next;
    }
}
