#ifndef __IITDH_CS312_LAB04_UTILS__
#define __IITDH_CS312_LAB04_UTILS__

#include <bits/stdc++.h>
#define DEBUG_MODE 0

typedef struct Process
{
    pid_t pid;
    int arrival_time;
    std::vector<int> bursts;
    std::vector<int> io;
    int turnaround_time;
    int waiting_time;
} Process;

bool print_process(Process process);

std::vector<Process> read_file(const std::string &filename);

#endif //__IITDH_CS312_LAB04_UTILS__