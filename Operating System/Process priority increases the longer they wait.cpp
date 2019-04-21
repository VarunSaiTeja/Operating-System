/*Consider a scheduling approach which is non pre-emptive similar to shortest job next in nature.
The priority of each job is dependent on its estimated run time, and also the amount of time it has spent waiting.
Jobs gain higher priority the longer they wait, which prevents indefinite postponement. The jobs that have spent a
long time waiting compete against those estimated to have short run times. The priority can be computed as :

Using the data given below compute the waiting time and turnaround time for each process and average waiting
time and average turnaround time.*/

#include <iostream>
#include <Windows.h>
using namespace std;

struct processes
{
    short int arrival, burst, burst_backup, completion = 0, turn_around = 0, waiting = 0, response = 0, priority = 0;
} * process;

short int total_time = 0, processes_count, queue_count;

int next_process_to_execute()
{
    int high_priority = 0, less_burst_time = 0, process_index = 0;

    for (short int index = 0; index < processes_count; index++)
    {
        if (process[index].burst > 0 &&
            total_time > process[index].arrival &&
            process[index].waiting >= 10)
        {
            process[index].priority = process[index].waiting / 10;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 && (process[index].priority > high_priority))
        {
            high_priority = process[index].priority;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst > 0) && (process[index].priority > high_priority))
        {
            high_priority = process[index].priority;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((process[index].burst) > 0 &&
            (total_time >= process[index].arrival) &&
            (process[index].priority == high_priority))
        {
            less_burst_time = process[index].burst;
            process_index = index;
            break;
        }
    }

    for (short int index = 0; index < processes_count; index++)
    {
        if ((less_burst_time > process[index].burst) &&
            (process[index].burst > 0) &&
            (total_time >= process[index].arrival) &&
            (process[index].priority == high_priority))
        {
            less_burst_time = process[index].burst;
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

void execute_processes()
{
    while (!all_processes_completed())
    {
        if (!all_arrived_processes_completed())
        {
            int process_id = next_process_to_execute();

            cout << "\nProcess " << process_id << " executing... ";

            while (process[process_id].burst > 0)
            {
                ++total_time;
                --process[process_id].burst;
                Sleep(50);
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
            cout << "\nProcess "
                 << process_id
                 << "executed.\n";
        }
        else
        {
            ++total_time;
        }
    }
}

void display_table()
{
    cout << "\n\nProcess     :  Arival\t Burst\t Compt\t Turn\t Waiting\t\n";
    cout << "__________________________________________________________________\n";

    for (short int index = 0; index < processes_count; index++)
    {
        cout << "Process "
             << index << "   :  "
             << process[index].arrival << "\t "
             << process[index].burst_backup
             << "\t " << process[index].completion
             << "\t " << process[index].turn_around << "\t " << process[index].waiting << "\n\n";
    }

    cout << "__________________________________________________________________\n";

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

    cout << "\nAverage Turn around Time : " << total_turnaround_time << "\n";
    cout << "\nAverage Waiting Time : " << total_waiting_time << "\n\n\n";
}

int main()
{
    cout << "Enter Processes Count : ";
    cin >> processes_count;
    process = new processes[processes_count];
    cout << "\nEnter Foramt AT BT\n";

    for (short int index = 0; index < processes_count; index++)
    {
        cout << "\nP " << index << " details : ";
        cin >> process[index].arrival >> process[index].burst;
        process[index].burst_backup = process[index].burst;
    }

    system("cls");
    cout << "Execution Started : \n";
    execute_processes();
    cout << "\n\nAll Processes executed\n\n";
    system("pause");
    system("cls");
    display_table();
    system("pause");
}