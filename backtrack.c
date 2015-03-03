#include "backtrack.h"
#include "io.h"

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

static void add_decision_backup (decision_backup** root, decision* dec)
{
    decision_backup* new_backup = (decision_backup*)malloc(sizeof(decision_backup));
    new_backup->dec = dec;
    new_backup->next = NULL;

    if(*root == NULL)
    {
        *root = new_backup;
    }
    else
    {
        decision_backup* tmp = *root;
        while(tmp != NULL) tmp = tmp->next;

        tmp->next = new_backup;
    }
}

static void collision_handle(decision* root, decision* dec, solution* sol)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->valid == 1 &&
           collision_detect(tmp->_data, dec->_data) &&
           tmp != dec)
        {
            tmp->valid = 0;
            add_decision_backup(&(sol->dec_back), tmp);
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
        while(tmp->next != NULL) tmp = tmp->next;

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

void print_decisions (decision* root)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        printf("Valid: %d\n", tmp->valid);
        print_data(tmp->_data);

        tmp = tmp->next;
    }
}

//TODO: maybe redundant with pick_decision
static int decision_empty (decision* root)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->valid == 1) return 1;

        tmp = tmp->next;
    }

    return 0;
}

//TODO: should it return data instead of decision
static decision* pick_decision (decision* root)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->valid == 1) return tmp;

        tmp = tmp->next;
    }

    return NULL; //wont be needed if decision_empty checked
}


static int solution_found () {}

static void add_decision_to_solution(solution** root, solution* sol)
{
    if(*root == NULL)
    {
        *root = sol;
    }
    else
    {
        solution* tmp = *root;
        while(tmp->next != NULL) tmp = tmp->next;

        tmp = sol;
    }
}

static solution* set_solution (decision* dec)
{
    solution* new_sol = (solution*)malloc(sizeof(solution));
    new_sol->dec = dec;
    new_sol->dec_back = NULL;
    new_sol->next = NULL;

    return new_sol;
}

void back_track (decision* decision_list)
{
    solution* sol = NULL;

    while(decision_empty(decision_list))
    {
        decision* pick = pick_decision(decision_list);
        solution* new_sol = set_solution(pick);
        collision_handle(decision_list, pick, new_sol); //TODO: should store the invalidated data for the step_back
        add_decision_to_solution(&sol, new_sol);

        if(decision_empty(decision_list))
        {
            if(solution_found())
            {
                //TODO: save solution
            }
            else
            {
                //TODO: step_back
            }
        }
    }
}
