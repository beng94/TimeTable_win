#include "io.h"
#include "backtrack.h"

const char *file_name = "TimeTable.csv";

int main()
{
    data* data_list = NULL;
    read_in(&data_list, file_name);

    getchar();
    print_data_list(data_list);

    decision* decision_list = NULL;
    init_decisions(&decision_list, data_list);
    print_decisions(decision_list);

    back_track(decision_list);

    return 0;
}
