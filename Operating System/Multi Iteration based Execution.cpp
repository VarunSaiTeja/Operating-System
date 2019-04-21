/*Considering the arrival time and burst time requirement of the process the scheduler schedules the processes
by interrupting the processor after every 6 units of time and does consider the completion of the process in this
iteration. The scheduler than checks for the number of process waiting for the processor and allots the processor
to the process but interrupting the processor every 10 unit of time and considers the completion of the processes
in this iteration. The scheduler checks the number of processes waiting in the queue for the processor after the
second iteration and gives the processor to the process which needs more time to complete than the other processes
to go in the terminated state.*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0;
    bool iteration_completed[2] = {FALSE, FALSE};
} * process;

short int total_time = 0, processes_count, first_iteration = 6, second_iteration = 10, loop_iteration_count;

int get_least_arrival_time_of_processes()
{
    int less_burst_time = process[0].arrival, process_index = 0;

    for (short int index = 1; index < processes_count; index++)
    {
        if (process[index].arrival < less_burst_time)
        {
            less_burst_time = process[index].arrival;
            process_index = index;
        }
    }
    return process_index;
}

int get_arrived_process_with_high_burst_time_and_not_iterated(int iterated_count)
{
    int highest_burst_time = 0, process_index = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > 0) && (total_time >= process[index].arrival) && !(process[index].iteration_completed[iterated_count]))
        {
            highest_burst_time = process[index].burst;
            process_index = index;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > highest_burst_time) && (process[index].burst > 0) && (total_time >= process[index].arrival) && !(process[index].iteration_completed[iterated_count]))
        {
            highest_burst_time = process[index].burst;
            process_index = index;
        }
    }
    return process_index;
}

int get_arrived_process_with_high_burst_time()
{
    int highest_burst_time = 0, process_index = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > 0) && (total_time >= process[index].arrival))
        {
            highest_burst_time = process[index].burst;
            process_index = index;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > highest_burst_time) && (process[index].burst > 0) && (total_time >= process[index].arrival))
        {
            highest_burst_time = process[index].burst;
            process_index = index;
        }
    }
    return process_index;
}

bool all_processes_completed()
{
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool all_arrived_processes_completed()
{
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 && total_time >= process[index].arrival)
        {
            return FALSE;
        }
    }
    return TRUE;
}

bool all_arrived_process_iterated(int iterated_count)
{
    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > 0) && (total_time > process[index].arrival) && (process[index].iteration_completed[iterated_count]))
        {
            loop_iteration_count = 0;
            return FALSE;
        }
    }
    return TRUE;
}

void execute_processes()
{
    int process_id;
    for (loop_iteration_count = 0; ((loop_iteration_count < first_iteration) || (!all_arrived_process_iterated(0))); loop_iteration_count++)
    {
        if (total_time < get_least_arrival_time_of_processes())
        {
            ++total_time;
            continue;
        }

        if (loop_iteration_count == 0)
        {
            process_id = get_arrived_process_with_high_burst_time_and_not_iterated(0);
            process[process_id].iteration_completed[0] = TRUE;
        }

        --process[process_id].burst;

        for (short int index = 0; index < processes_count; index++)
        {
            if ((index != process_id) && (process[index].burst > 0) && (total_time > process[index].arrival))
            {
                ++process[index].waiting;
            }
        }

        if (process[process_id].burst == 0)
        {
            process[process_id].completion = total_time;
            process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
            printf("\nProcess %d executed.\n", process_id);
            loop_iteration_count = first_iteration;
        }
    }

    for (loop_iteration_count = 0; ((loop_iteration_count < second_iteration) || (!all_arrived_process_iterated(1))); loop_iteration_count++)
    {
        if (!all_arrived_process_iterated(1))
        {
            ++total_time;
            if (loop_iteration_count == 0)
            {
                process_id = get_arrived_process_with_high_burst_time_and_not_iterated(0);
                process[process_id].iteration_completed[1] = TRUE;
            }

            --process[process_id].burst;

            for (short int index = 0; index < processes_count; index++)
            {
                if ((index != process_id) && (process[index].burst > 0) && (total_time > process[index].arrival))
                {
                    ++process[index].waiting;
                }
            }

            if (process[process_id].burst == 0)
            {
                process[process_id].completion = total_time;
                process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
                printf("\nProcess %d executed.\n", process_id);
                loop_iteration_count = second_iteration;
            }
        }
        else
        {
            ++total_time;
        }
    }

    while (!all_processes_completed())
    {
        if (!all_arrived_processes_completed())
        {
            int process_id = get_arrived_process_with_high_burst_time();

            while (process[process_id].burst > 0)
            {
                ++total_time;
                --process[process_id].burst;
                for (short int index = 0; index < processes_count; index++)
                {
                    if (index != process_id && total_time > process[index].arrival && process[index].burst > 0)
                    {
                        ++process[index].waiting;
                    }
                }
            }

            process[process_id].completion = total_time;
            process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
            printf("\nProcess %d executed.\n", process_id);
        }
        else
        {
            ++total_time;
        }
    }
}

int main()
{

    printf("Enter Processes Count : ");
    scanf("%d", &processes_count);
    process = new processes[processes_count];
    printf("\nEnter Foramt AT BT\n");

    for (short int index = 0; index < processes_count; index++)
    {
        printf("\nP%d details : ", index);
        scanf("%d %d", &process[index].arrival, &process[index].burst);
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    printf("Execution Started : \n");
    execute_processes();
    printf("\n\nAll Processes executed\n\n");

    system("pause");
    system("cls");

    printf("\n\nProcess     :  Arival\t Burst\t Compt\t Turn\t Waiting\t\n");
    printf("__________________________________________________________________\n");
    for (short int index = 0; index < processes_count; index++)
    {
        printf("Process %d   :  %d\t %d\t %d\t %d\t %d\n\n", index, process[index].arrival, process[index].burst_backup, process[index].completion, process[index].turn_around, process[index].waiting);
    }

    printf("__________________________________________________________________\n");

    float total_turnaround_time = 0, total_waiting_time = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        total_turnaround_time += process[index].turn_around;
    }
    total_turnaround_time /= processes_count;

    for (short int index = 0; index < processes_count; index++)
    {
        total_waiting_time += process[index].waiting;
    }
    total_waiting_time /= processes_count;

    printf("\nAverage Turn around Time : %.2f\n", total_turnaround_time);
    printf("\nAverage Waiting Time : %.2f\n\n", total_waiting_time);
    printf("Total time taken by the processor to compute all the jobs : %d\n\n", total_time);
    system("pause");
}
