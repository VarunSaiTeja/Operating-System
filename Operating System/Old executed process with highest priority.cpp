/*8. Design a scheduler that uses a preemptive priority scheduling algorithm based on dynamically changing priority.
Larger number for priority indicates higher priority.
Assume that the following processes with arrival time and service time wants to execute (for reference):
When the process starts execution (i.e. CPU assigned), priority for that process changes at the rate of m=1.When the
process waits for CPU in the ready queue (but not yet started execution), its priority changes at a rate n=2. All the
processes are initially assigned priority value of 0 when they enter ready queue for the first time . The time slice for
each process is q = 1. When two processes want to join ready queue simultaneously, the process which has not
executed recently is given priority. Calculate the average waiting time for each process. The program must be
generic i.e. number of processes, their burst time and arrival time must be entered by user.*/

#include <stdio.h>
#include <Windows.h>
#define bool int
#define TRUE 1
#define FALSE 0

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0, priority = 0, recent;
} process[10];

short int total_time = 0, processes_count;

int get_highest_priority()
{
    int high = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 && total_time >= process[index].arrival)
        {
            high = process[index].priority;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > 0) && (process[index].priority > high) && total_time >= process[index].arrival)
        {
            high = process[index].priority;
        }
    }

    return high;
}

int get_old_executed_process(int priority)
{
    int old_process = 0, process_id = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 &&
            (process[index].priority == priority) &&
            total_time >= process[index].arrival)
        {
            old_process = process[index].recent;
            process_id = index;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 &&
            (process[index].priority == priority) &&
            process[index].recent < old_process &&
            total_time >= process[index].arrival)
        {
            old_process = process[index].priority;
            process_id = index;
        }
    }

    return process_id;
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
            int process_id = get_old_executed_process(get_highest_priority());

            ++total_time;
            --process[process_id].burst;
            if (process[process_id].recent == 0)
            {
                process[process_id].priority = 1;
            }

            for (short int index = 0; index < processes_count; index++)
            {
                if (index != process_id && total_time > process[index].arrival && process[index].burst > 0)
                {
                    ++process[index].waiting;
                    if (process[index].recent == 0)
                    {
                        process[index].priority = 2;
                    }
                }
            }

            process[process_id].recent++;

            if (process[process_id].burst == 0)
            {
                process[process_id].completion = total_time;
                process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
                printf("\nProcess %d executed.\n", process_id);
                Sleep(1000);
            }
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

    printf("\n__________________________________________________________________\n");

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
    printf("\nAverage Waiting Time : %.2f\n\n\n", total_waiting_time);
    system("pause");
}