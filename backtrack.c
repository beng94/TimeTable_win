#include "backtrack.h"
#include "io.h"

//TODO: implement generic lists

static int interval_collision (time* _time1, time* _time2)
{
    time* t1 = _time1;
    time* t2 = _time2;

    if(t1->day == t2->day)
    {
        if(t1->time_interval->beg_hour > t2->time_interval->beg_hour)
        {
            time* tmp = t1;
            t1 = t2;
            t2 = tmp;
        }
        if(t1->time_interval->beg_hour == t2->time_interval->beg_hour &&
           t1->time_interval->beg_min > t2->time_interval->beg_min)
        {
            time* tmp = t1;
            t1 = t2;
            t2 = tmp;
        }

        if(t1->time_interval->end_hour > t2->time_interval->beg_hour) return 1;

        if(t1->time_interval->end_hour == t2->time_interval->beg_hour &&
           t1->time_interval->end_min >= t2->time_interval->beg_min) return 1;
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

static int name_collision(char* name1, char* name2)
{
    return (strcmp(name1, name2) == 0) ? 1 : 0;
}

static int collision_detect(data* dt1, data* dt2)
{
    if(type_collision(dt1->curse_type, dt2->curse_type) && name_collision(dt1->lec_name, dt2->lec_name)) return 1;
    if(time_collision(dt1->occas, dt2->occas)) return 1;

    return 0;
}

static void add_collision (collisions** col, decision* dec)
{
    collisions* new_col = (collisions*)malloc(sizeof(collisions));
    new_col->dec = dec;
    new_col->next = NULL;

    if(*col == NULL)
    {
        *col = new_col;
    }
    else
    {
        collisions* tmp = *col;
        while(tmp->next != NULL) tmp = tmp->next;

        tmp->next = new_col;
    }
}

static void collision_handle(decision* root, solution* sol)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->valid == 1 &&
           tmp != sol->dec &&
           collision_detect(tmp->_data, sol->dec->_data)
           )
        {
            tmp->valid = 0;
            add_collision(&(sol->col), tmp);
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

void print_solution (solution* root)
{
    solution* tmp = root;

    if(tmp == NULL) return;

    while(tmp != NULL)
    {
        printf("%s %s\n",  tmp->dec->_data->curse_code, tmp->dec->_data->lec_name);

        tmp = tmp->next;
    }
}

//TODO: maybe redundant with pick_decision
static int decision_empty (decision* root)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->valid == 1) return 0;

        tmp = tmp->next;
    }

    return 1;
}

//TODO: should it return data instead of decision?
static decision* pick_decision (decision* root)
{
    decision* tmp = root;
    while(tmp != NULL)
    {
        if(tmp->valid == 1)
        {
            tmp->valid = 0;
            return tmp;
        }

        tmp = tmp->next;
    }

    return NULL;
}


static int solution_found (solution* sol_list)
{
    //TODO: what if sol_list is NULL? Or sol_list->next == NULL?
    int count = 1;
    solution* tmp = sol_list;
    while(tmp->next != NULL)
    {
        count++;
        tmp = tmp->next;
    }

    if(count == 15)
    {
        return 1;
    }
    return 0;
}

static void add_decision_to_solution(solution** root, solution* sol)
{
    if(*root == NULL)
    {
        *root = sol;
    }
    else
    {
        solution* tmp = *root;
        while(tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        tmp->next = sol;
    }
}

static solution* set_solution (decision* dec)
{
    solution* new_sol = (solution*)malloc(sizeof(solution));
    new_sol->dec = dec;
    new_sol->next = NULL;
    new_sol->col = NULL;

    return new_sol;
}

static void step_back (solution** sol, decision* dec_list)
{
    solution* sol_remove = *sol;
    solution* sol_last = NULL; //pointer to the last but one element
    while(sol_remove->next != NULL)
    {
        sol_last = sol_remove;
        sol_remove = sol_remove->next;
    }

    if(sol_last == NULL)  *sol = NULL;
    else sol_last->next = NULL;

    collisions* tmp = sol_remove->col;
    while(tmp != NULL)
    {
        collisions* next = tmp->next;
        tmp->dec->valid = 1;
        free(tmp);
        tmp = next;
    }

    free(sol_remove);
}

static void repair_validity(decision* decision_list, solution* solution_list)
{
    decision* dec_tmp = decision_list;
    while(dec_tmp != NULL)
    {
        //print_data(dec_tmp->_data);
        if(dec_tmp->valid == 0)
        {
            int collide = 0;
            solution* sol_tmp = solution_list;
            while(sol_tmp != NULL)
            {
                //print_data(sol_tmp->dec->_data);
                if(dec_tmp == sol_tmp->dec)
                {
                    collide = 1;
                    break;
                }
                if(collision_detect(dec_tmp->_data, sol_tmp->dec->_data))
                {
                    collide = 1;
                    break;
                }
                sol_tmp = sol_tmp->next;
            }

            if(!collide)
            {
                dec_tmp->valid = 1;
                printf("%s\n", dec_tmp->_data->curse_code);
            }
        }

        dec_tmp = dec_tmp->next;
    }
}

void back_track (decision* decision_list)
{
    solution* sol = NULL;

    while(!decision_empty(decision_list) || sol != NULL)
    {
        decision* pick = pick_decision(decision_list);
        if(pick == NULL)
        {
            //repair_validity(decision_list, sol);
            step_back(&sol, decision_list);
            continue;
        }
        solution* new_sol = set_solution(pick);
        collision_handle(decision_list, new_sol);
        add_decision_to_solution(&sol, new_sol);

        if(solution_found(sol))
        {
            print_solution(sol);
            break;
        }
    }
}
