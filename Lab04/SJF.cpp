#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

class CompareBurst
{
public:
    bool operator()(Process a, Process b)
    {
        return a.bursts[0] > b.bursts[0];
    }
};

class CompareIO
{
public:
    bool operator()(Process a, Process b)
    {
        return a.io[0] > a.io[0];
    }
};

class CompareArrival
{
public:
    bool operator()(Process a, Process b)
    {
        return a.arrival_time > b.arrival_time;
    }
};

class SJF
{
private:
    priority_queue<Process, vector<Process>, CompareArrival> waitlisted_queue;
    priority_queue<Process, vector<Process>, CompareBurst> ready_queue;
    vector<Process> finished;
    int io_available_time = 0;

public:
    bool is_waitlisted_queue_empty()
    {
        return waitlisted_queue.empty();
    }

    bool is_ready_queue_empty()
    {
        return ready_queue.empty();
    }

    void add_to_waitlisted_queue(Process process)
    {
        DEBUG_MODE &&cout << "Process with pid:" << process.pid << " is being added to waitlisted queue" << endl;
        waitlisted_queue.push(process);
    }

    vector<Process> get_finished()
    {
        return finished;
    }

    int run(int time)
    {
        while (!waitlisted_queue.empty() && waitlisted_queue.top().arrival_time <= time)
        {
            ready_queue.push(waitlisted_queue.top());
            DEBUG_MODE &&cout << "At time " << time << " Process with pid:" << waitlisted_queue.top().pid
                              << " is being added to ready queue" << endl;
            waitlisted_queue.pop();
        }
        if (!ready_queue.empty())
        {
            Process process = ready_queue.top();
            ready_queue.pop();
            process.waiting_time += time - process.arrival_time;
            process.turnaround_time += process.waiting_time + process.bursts[0];
            time += process.bursts[0];
            process.bursts.erase(process.bursts.begin());
            if (!process.io.empty())
            {
                process.arrival_time = max(time, io_available_time) + process.io[0];
                io_available_time = process.arrival_time;
                process.io.erase(process.io.begin());
                add_to_waitlisted_queue(process);
                DEBUG_MODE &&cout << process.pid << ": Process being added again" << endl;
                DEBUG_MODE &&cout << process.pid << ": Burst length " << process.bursts.size() << "\t"
                                  << " IO Length " << process.io.size() << endl;
                DEBUG_MODE &&print_process(process);
            }
            else
            {
                finished.push_back(process);
            }
        }
        else
        {
            time++;
        }
        return time;
    }
};

int main(int argc, char *argv[])
{
    string filename;
    int num_processes = 0;
    if (DEBUG_MODE)
    {
        filename = "tests/process1.dat";
    }
    else
    {
        if (argc < 1)
        {
            exit(-1);
        }
    }

    vector<Process> Processes;
    if (DEBUG_MODE)
    {
        Processes = read_file(filename);
    }
    else
    {
        Processes = read_file(argv[1]);
    }

    SJF sjf;
    for (auto i : Processes)
    {
        num_processes++;
        sjf.add_to_waitlisted_queue(i);
    }

    int time = 0;
    int context_switches = -1;

    while (!sjf.is_ready_queue_empty() || !sjf.is_waitlisted_queue_empty())
    {
        context_switches++;
        time = sjf.run(time);
        DEBUG_MODE &&cout << "Stuck in this run loop at time " << time << endl;
        DEBUG_MODE &&cout << "\n"
                          << endl;
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    float total_penalty_ratio = 0;
    for (Process process : sjf.get_finished())
    {
        total_waiting_time += process.waiting_time;
        total_turnaround_time += process.turnaround_time;
        total_penalty_ratio += (float)process.turnaround_time / (process.turnaround_time - process.waiting_time);
    }

    cout << (double)total_waiting_time / num_processes << "\t" << (double)total_turnaround_time / num_processes << "\t" << (double)total_penalty_ratio / num_processes << endl;
}
