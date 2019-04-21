/*
Consider a scheduler which schedules the job by considering the arrival time of the processes
where arrival time if given as 0 is discarded or displayed as error. The scheduler implements the
shortest job first scheduling policy, but checks the queue of the processes after the every process terminates
and time taken for checking and arranging the process according to the shortest job is 2 time unit.
Compute the waiting time, turnaround time and average waiting time and turnaround time of the processes.
Also compute the total time taken by the processor to compute all the jobs.*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0;
} * process;

short int total_time = 0, time_to_caluclate = 2, processes_count;

bool one_process_executed = FALSE;

int get_arrived_process_with_less_burst_time()
{
    int less_burst_time = 0, process_index = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 && total_time >= process[index].arrival)
        {
            less_burst_time = process[index].burst;
            process_index = index;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if (less_burst_time > process[index].burst && (process[index].burst > 0) && total_time >= process[index].arrival)
        {
            less_burst_time = process[index].burst;
            process_index = index;
        }
    }
    if (one_process_executed)
    {

        for (short int loop = 0; loop < time_to_caluclate; loop++)
        {
            ++total_time;
            for (short int index = 0; index < processes_count; index++)
            {
                if (total_time > process[index].arrival && process[index].burst > 0)
                {
                    ++process[index].waiting;
                }
            }
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

void execute_processes()
{
    while (!all_processes_completed())
    {
        if (!all_arrived_processes_completed())
        {
            int process_id = get_arrived_process_with_less_burst_time();

            printf("\nProcess %d executing...", process_id);

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
            one_process_executed = TRUE;
            printf("\nProcess %d executed.\n", process_id);
            Sleep(1000);
        }
        else
        {
            ++total_time;
        }
    }
}

int main()
{
    bool can_execute = TRUE;
    printf("Enter Processes Count : ");
    scanf("%d", &processes_count);
    process = new processes[processes_count];
    printf("\nEnter Foramt AT BT\n");

    for (short int index = 0; index < processes_count; index++)
    {
        printf("\nP%d details : ", index);
        scanf("%d %d", &process[index].arrival, &process[index].burst);
        if (process[index].arrival == 0)
        {
            printf("\n\nOops, P%d process having Arival time 0\n\n", index);
            can_execute = FALSE;
            break;
        }
        process[index].burst_backup = process[index].burst;
    }

    if (can_execute)
    {
        system("cls");
        printf("Execution Started : \n");
        execute_processes();
        printf("\n\nAll Processes executed\n\n");
    }

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