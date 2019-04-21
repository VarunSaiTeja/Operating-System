/*A barrier is a tool for synchronizing the activity of a number of threads. When a thread reaches a barrier
point, it cannot proceed until all other threads have reached this point as well. When the last thread reaches
the barrier point, all threads are released and can resume concurrent execution.

Assume that the barrier is initialized to N—the number of threads that must wait at the barrier point:
init(N);

Each thread then performs some work until it reaches the barrier
    point : do some work for awhile
    barrierpoint();
 do some work for awhile

Using synchronization tools like locks, semaphores and monitors, construct a barrier that implements the
following API :
• int init(int n)—Initializes the barrier to the specified size.
• int barrier point(void)—Identifies the barrier point.
All threads are released from the barrier when the last thread reaches this point.*/

#include <iostream>
#include <stdlib.h>
#include <Windows.h>
#include <thread>

using namespace std;

short int barrier_size, arrived_threads = 0;

int init(int n)
{
    barrier_size = n;
    return n;
}

int barrier_point()
{
    return arrived_threads;
}

bool barrier_full()
{
    if (barrier_point() == barrier_size)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void do_work(int id)
{
    using namespace std::literals::chrono_literals;
    while (!barrier_full())
    {
        cout << "Thread " << id << " waiting..." << endl;
        this_thread::sleep_for(1s);
    }
}

void start()
{
    thread *threads = new thread[barrier_size];

    for (int loop = 0; loop < barrier_size; loop++)
    {
        ++arrived_threads;
        if (arrived_threads == barrier_size)
        {
            cout << endl
                 << "Thread " << loop << " arrived" << endl;
        }
        threads[loop] = thread(do_work, loop);
        Sleep(1100);
    }

    cout << endl
         << endl
         << "All threads Arrived" << endl;

    for (int loop = 0; loop < barrier_size; loop++)
    {
        threads[loop].join();
    }

    cout << "All threads are released and resumed concurrent execution";
}

int main()
{
    int bs;
    cout << "Enter Barrier Size : ";
    cin >> bs;
    init(bs);
    start();
    cout << "\n\n";
    system("pause");
}