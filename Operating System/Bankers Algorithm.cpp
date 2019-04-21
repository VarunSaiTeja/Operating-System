#include <iostream>
#include <stdio.h>
#include <Windows.h>
//To clear screen, sleep, pause using Windows.h
using namespace std;

short int allocated_instances[5][4];
short int need_instances[5][4];
short int max_instances[5][4];
short int total_allocated[4] = {0, 0, 0, 0};
short int avil_instances[4];

short int processes_count = 4, resource_count = 3;
// above count starts from 0
// so actual processes_count=5, resource_count=4

bool process_completed[5] = {FALSE, FALSE, FALSE, FALSE, FALSE};

void execute_processes()
{
    printf("Executed Process : \n");
    printf("___________________\n");
    for (int count = 0; count <= processes_count; count++)
    {
        for (int process = 0; process <= processes_count; process++)
        {
            if (process_completed[process] == FALSE)
            {
                if (need_instances[process][0] <= avil_instances[0] &&
                    need_instances[process][1] <= avil_instances[1] &&
                    need_instances[process][2] <= avil_instances[2] &&
                    need_instances[process][3] <= avil_instances[3])
                {
                    //If block execute only if all resources and required max instances are avilable
                    Sleep(2000);

                    printf("Process %d Executed\n", process);
                    for (int instance = 0; instance <= resource_count; instance++)
                    {
                        avil_instances[instance] += allocated_instances[process][instance];
                        //After Process terminated, giving back instances
                    }

                    process_completed[process] = TRUE;
                }
            }
        }
    }

    Sleep(2000);

    if (process_completed[0] &&
        process_completed[1] &&
        process_completed[2] &&
        process_completed[3] &&
        process_completed[4])
    {
        system("color 0A");
        printf("\nSystem in safe state\n\n");
    }
    else
    {
        system("color 0C");
        printf("\nSystem In Unsafe State\n\n");
        printf("Unexecuted Process : \n");
        printf("____________________\n");
        for (int process = 0; process <= processes_count; process++)
        {
            if (process_completed[process] == FALSE)
            {
                Sleep(2000);
                printf("Process %d\n", process);
            }
        }
        printf("\n");
    }
}

void cal_need_instances()
{
    for (int process = 0; process <= processes_count; process++)
    {
        for (int instance = 0; instance <= resource_count; instance++)
        {
            need_instances[process][instance] = max_instances[process][instance] - allocated_instances[process][instance];
        }
    }
}

void display_table()
{
    system("cls");
    printf("\n_______________________________________________________\n");
    printf("| Details    | Allocated   |   Maximum   |    Need    |\n");
    printf("|_____________________________________________________|\n");
    printf("| Process No |  A  B  C  D |  A  B  C  D | A  B  C  D |\n");
    printf("|____________|_____________|_____________|____________|\n");
    for (int process = 0; process <= processes_count; process++)
    {
        printf("| Process %d  |  %d  %d  %d  %d ", process, allocated_instances[process][0], allocated_instances[process][1], allocated_instances[process][2], allocated_instances[process][3]);
        printf("|  %d  %d  %d  %d ", max_instances[process][0], max_instances[process][1], max_instances[process][2], max_instances[process][3]);
        printf("| %d  %d  %d  %d |\n",
               need_instances[process][0] > 0 ? need_instances[process][0] : 0,
               need_instances[process][1] > 0 ? need_instances[process][1] : 0,
               need_instances[process][2] > 0 ? need_instances[process][2] : 0,
               need_instances[process][3] > 0 ? need_instances[process][3] : 0);
    }
    printf("\n\n\n");
}

void cal_total_allocated()
{
    for (int instance = 0; instance <= resource_count; instance++)
    {
        for (int process = 0; process <= processes_count; process++)
        {
            total_allocated[instance] += allocated_instances[process][instance];
        }
    }
}

int main()
{
    printf("Avilable instances of A, B, C, D : ");
    scanf("%d %d %d %d", &avil_instances[0], &avil_instances[1], &avil_instances[2], &avil_instances[3]);
    system("cls");

    printf("Allocated instances of Process : A, B, C, D\n");
    for (int process = 0; process <= 4; process++)
    {
        printf("\nAllocated resources for P%d : ", process);
        scanf("%d %d %d %d", &allocated_instances[process][0], &allocated_instances[process][1], &allocated_instances[process][2], &allocated_instances[process][3]);
    }
    system("cls");

    printf("Maximum instances for Process : A, B, C, D\n");
    for (int process = 0; process <= 4; process++)
    {
        printf("\nMaximum resources required for P%d : ", process);
        scanf("%d %d %d %d", &max_instances[process][0], &max_instances[process][1], &max_instances[process][2], &max_instances[process][3]);
    }

    cal_total_allocated();
    cal_need_instances();
    display_table();
    execute_processes();

    system("pause");
}