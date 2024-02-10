#include "utils.h"
#include <bits/stdc++.h>

using namespace std;

bool print_process(Process process);

bool CompareBurst::operator()(Process a, Process b)
{
    return a.bursts[0] > b.bursts[0];
};

bool CompareIO::operator()(Process a, Process b)
{
    return a.io[0] > a.io[0];
};

bool CompareArrival::operator()(Process a, Process b)
{
    return a.arrival_time > b.arrival_time;
};

vector<Process> read_file(const string &filename)
{
    vector<Process> Processes;
    ifstream myfile(filename);

    if (!myfile)
    {
        printf("File doesn't exist");
        exit(-1);
    }

    istream_iterator<string> fileIterator(myfile);
    istream_iterator<string> endIterator;

    int ele = 0;
    Process process;
    pid_t pid = 0;

    while (fileIterator != endIterator)
    {
        string word = *fileIterator;
        if (word[0] == '<')
        {
            ++fileIterator;
            continue;
        }
        int num = stoi(word);
        if (ele == 0)
        {
            process = Process();
            process.arrival_time = num;
            ele++;
            DEBUG_MODE &&cout << "Created new Process with arrival time " << num << endl;
        }
        else if (ele && num != -1)
        {
            DEBUG_MODE &&cout << "(" << ele << ", " << num << ")" << '\t';
            if (ele % 2 == 1) // odd elements are CPU bursts
                process.bursts.push_back(num);
            else
                process.io.push_back(num);
            ele++;
        }
        else
        {
            ele = 0;
            process.pid = pid;
            Processes.push_back(process);
            DEBUG_MODE &&cout << "Process added to Processes Queue with pid:" << pid << endl;
            pid++;
        }
        ++fileIterator;
    }

    myfile.close();
    for (auto i : Processes)
        DEBUG_MODE &&print_process(i);
    return Processes;
}

bool print_process(Process process)
{
    cout << "PID of the process is " << process.pid << endl;
    cout << "Arrival time of the process is " << process.arrival_time << endl;
    cout << "Process busts are: ";
    for (auto i : process.bursts)
        cout << i << "\t";
    cout << endl;
    cout << "Process io are: ";
    for (auto i : process.io)
        cout << i << "\t";
    cout << endl;
    cout << "Process turnaround time is " << process.turnaround_time << endl;
    cout << "Process waiting time is " << process.waiting_time << endl;
    cout << "\n";
    return true;
}