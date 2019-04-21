/*Ques. 10. Design a scheduler with multilevel queue having two queues which will schedule the processes
on the basis of  pre-emptive shortest remaining processing time first algorithm (SROT) followed by a
scheduling in which each process will get 2 units of time to execute. Also note that queue

1 Has higher priority than queue 2

Calculate the average turnaround time and average waiting time for each process.
The input for number of processes  and their arrival time, burst time should be given by the user.*/

#include <iostream>
#include <stdio.h>
#include <Windows.h>

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0, queue;
} * process;

short int total_time = 0, time_quantum = 2, processes_count, queue_count;

int get_max_queue()
{
    int max = 0;
    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].queue > max)
        {
            max = process[index].queue;
        }
    }

    return max;
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

int get_process_with_less_burst_time_in_queue(int queue)
{
    int less_burst_time = 0, process_index = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 && process[index].queue == queue && total_time >= process[index].arrival)
        {
            less_burst_time = process[index].burst;
            process_index = index;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if (less_burst_time > process[index].burst && (process[index].burst > 0) && (process[index].queue == queue) && total_time >= process[index].arrival)
        {
            less_burst_time = process[index].burst;
            process_index = index;
        }
    }
    return process_index;
}

int get_queue_with_highest_priority_containing_process()
{
    for (int priority = 0; priority <= queue_count; priority++)
    {
        for (int index = 0; index < processes_count; index++)
        {
            if (process[index].queue == priority && process[index].burst > 0 && total_time >= process[index].arrival)
            {
                return process[index].queue;
            }
        }
    }
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
            int process_id = get_process_with_less_burst_time_in_queue(get_queue_with_highest_priority_containing_process());

            for (short int time_q = 0; time_q < time_quantum; time_q++)
            {
                --process[process_id].burst;
                ++total_time;
                printf("\nProcess %d executing...", process_id);
                Sleep(1000);

                for (short int index = 0; index < processes_count; index++)
                {
                    if (index != process_id && total_time > process[index].arrival && process[index].burst > 0)
                    {
                        ++process[index].waiting;
                    }
                }

                if (process[process_id].burst == 0)
                {
                    process[process_id].completion = total_time;
                    process[process_id].turn_around = process[process_id].completion - process[process_id].arrival;
                    printf("\nProcess %d executed", process_id);
                    break;
                }

                if (get_queue_with_highest_priority_containing_process() < process[process_id].queue)
                {
                    break;
                }
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
    process = new processes[processes_count];
    printf("\nEnter Foramt AT BT QN (Starts from 0)\n");

    for (short int index = 0; index < processes_count; index++)
    {
        printf("\nP%d details : ", index);
        scanf("%d %d %d", &process[index].arrival, &process[index].burst, &process[index].queue);
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    queue_count = get_max_queue();
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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
