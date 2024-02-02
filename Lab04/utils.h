#ifndef __IITDH_CS321_LAB04_UTILS__
#define __IITDH_CS321_LAB04_UTILS__

#include <bits/stdc++.h>

typedef struct Process {
    int arrival_time;
    std::vector<int> bursts;
} Process;

void read_file(const std::string &filename);

#endif //__IITDH_CS321_LAB04_UTILS__