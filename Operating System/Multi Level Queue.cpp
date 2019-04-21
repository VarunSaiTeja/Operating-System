/*Write a program for multilevel queue scheduling algorithm. There must be three queues generated.
There must be specific range of priority associated with every queue. Now prompt the user to enter number of
processes along with their priority and burst time. Each process must occupy the respective queue with specific
priority range according to its priority. Apply Round Robin algorithm with quantum time 4 on queue with highest
priority range. Apply priority scheduling algorithm on the queue with medium range of priority and First come first
serve algorithm on the queue with lowest range of priority. Each and every queue should get a quantum time of
10 seconds. CPU will keep on shifting between queues after every 10 seconds.*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0, queue;
} * process;

short int total_time = 0, time_quantum = 4, queue_time = 10;
short int processes_count, high_priority_queue, low_priority_queue, queue_count = 3;

void set_high_priority_queue()
{
    int max = 0;
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].queue > max)
        {
            max = process[index].queue;
        }
    }

    high_priority_queue = max;
}

void set_low_priority_queue()
{
    int min = 0;
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].queue < min)
        {
            min = process[index].queue;
        }
    }

    low_priority_queue = min;
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
        //Round Robin TQ=4 for 10 sec
        for (short int queue_time_q = 0; queue_time_q < queue_time; queue_time_q++)
        {
            if (!all_arrived_processes_completed())
            {
                for (short int index = 0; index < processes_count; index++)
                {
                    if (process[index].burst > 0 &&
                        total_time > process[index].arrival &&
                        process[index].queue == high_priority_queue)
                    {
                        --process[index].burst;

                        for (short int other_process = 0; other_process < processes_count; other_process++)
                        {
                            if (index != other_process && total_time > process[other_process].arrival && process[other_process].burst > 0)
                            {
                                ++process[other_process].waiting;
                            }
                        }

                        if (process[index].burst == 0)
                        {
                            process[index].completion = total_time;
                            process[index].turn_around = process[index].completion - process[index].arrival;
                            printf("\nProcess %d executed", index);
                            break;
                        }
                    }
                }
            }
            else
            {
                ++total_time;
            }
        }
    }
}

int main()
{
    printf("Enter Processes Count : ");
    scanf("%d", &processes_count);
    process = new processes[processes_count];
    printf("\nEnter Foramt AT BT QN (Starts from 0)\n");

    for (short int index = 0; index < processes_count; index++)
    {
        printf("\nP%d details : ", index);
        scanf("%d %d %d", &process[index].arrival, &process[index].burst, &process[index].queue);
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    printf("Execution Started : \n");
    execute_processes();
    printf("\n\nAll Processes executed\n\n");
    system("pause");
    system("cls");
    printf("\n\nProcess     :  Arival\t Burst\t Queue\t Compt\t Turn\t Waiting\t\n");
    printf("__________________________________________________________________\n");
    for (short int index = 0; index < processes_count; index++)
    {
        printf("Process %d   :  %d\t %d\t %d\t %d\t %d\t %d\n\n", index, process[index].arrival, process[index].burst_backup, process[index].queue, process[index].completion, process[index].turn_around, process[index].waiting);
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