#include <bits/stdc++.h>
using namespace std;

#define TIME_QUANT 1

int PID = 1;
double totalCPUWork = 0;
class Process
{
public:
    int PID;
    int arrivalTime;
    vector<int> CPU_Bursts = {};
    vector<int> IO_BURST = {};

    Process(int PID, vector<int> tokens)
    {
        this->PID = PID;
        int tokenLength = tokens.size();
        arrivalTime = tokens[0];
        for (int i = 1; i < tokenLength; i++)
        {
            if (i % 2 != 0)
            {
                this->CPU_Bursts.push_back(tokens[i]);
                totalCPUWork += tokens[i];
            }
            else
                this->IO_BURST.push_back(tokens[i]);
        }
    }
    void printProcess()
    {
        printf("PID: %d\n", this->PID);
        printf("Arrival Time: %d\n", this->arrivalTime);
        for (int i = 0; i < this->CPU_Bursts.size() + this->IO_BURST.size(); i++)
        {
            if (i % 2 == 0)
                printf("CPU Burst: %d\n", this->CPU_Bursts[i / 2]);
            else
                printf("IO Burst: %d\n", this->IO_BURST[(i / 2)]);
        }
        printf("---------\n");
    }
};

int timer = 0;

void printQueue(queue<Process *> q, bool isCPU, vector<int> &waitingTime)
{
    if (q.size() == 0)
        return;
    Process *front = q.front();
    q.pop();
    // isCPU ? printf("CPU\n") : printf("IO\n");
    // isCPU ? printf("PID: %d, CPU: %d\n", front->PID, front->CPU_Bursts[0]) : printf("PID: %d, IO: %d\n", front->PID, front->IO_BURST[0]);
    while (q.size() > 0)
    {
        Process *front = q.front();
        waitingTime[front->PID]++;
        q.pop();
        // isCPU ? printf("PID: %d, CPU: %d\n", front->PID, front->CPU_Bursts[0]) : printf("PID: %d, Io: %d\n", front->PID, front->IO_BURST[0]);
    }
    // printf("----\n");
    return;
}

void simulate(queue<Process *> &arrivalQueue, vector<int> &turnaroundTime, vector<int> &waitingTime)
{
    queue<Process *> CPU_Queue = {}, IO_Queue = {};
    while (arrivalQueue.size() > 0 || CPU_Queue.size() > 0 || IO_Queue.size() > 0)
    {
        int localQuant = TIME_QUANT;
        while (localQuant > 0)
        {
            // printf("Time: %d\n", timer);
            printQueue(CPU_Queue, 1, waitingTime);
            printQueue(IO_Queue, 0, waitingTime);
            Process *pushToIO = NULL, *pushToCPU = NULL;
            if (arrivalQueue.size() > 0 && arrivalQueue.front()->arrivalTime <= timer)
            {
                CPU_Queue.push(arrivalQueue.front());
                turnaroundTime[arrivalQueue.front()->PID] = timer;
                arrivalQueue.pop();
            }
            if (CPU_Queue.size() > 0)
            {
                Process *runningProcess = CPU_Queue.front();
                runningProcess->CPU_Bursts[0] -= 1;
                // if the CPU process has ended then we will try to push the process into IO_Queue
                if (runningProcess->CPU_Bursts[0] <= 0)
                {
                    CPU_Queue.pop();
                    runningProcess->CPU_Bursts.erase(runningProcess->CPU_Bursts.begin());
                    if (runningProcess->IO_BURST.size() > 0)
                        pushToIO = runningProcess; // store it in the variable as it will no be run in the IO queue in this time slice
                    else
                        turnaroundTime[runningProcess->PID] = timer - turnaroundTime[runningProcess->PID];
                }
            }
            if (IO_Queue.size() > 0)
            {
                Process *runningProcess = IO_Queue.front();
                runningProcess->IO_BURST[0] -= 1;
                // if the IO process has ended then we will try to push the process into CPU_Queue
                if (runningProcess->IO_BURST[0] <= 0)
                {
                    IO_Queue.pop();
                    runningProcess->IO_BURST.erase(runningProcess->IO_BURST.begin());
                    if (runningProcess->CPU_Bursts.size() > 0)
                        pushToCPU = runningProcess; // store it in the variable as it will no be run in the CPU queue in this time slice
                    else
                        turnaroundTime[runningProcess->PID] = timer - turnaroundTime[runningProcess->PID];
                }
            }
            if (pushToCPU != NULL)
                CPU_Queue.push(pushToCPU);
            if (pushToIO != NULL)
                IO_Queue.push(pushToIO);
            localQuant--;
            timer++;
        }
        if (CPU_Queue.size() > 0)
        {
            Process *currFront = CPU_Queue.front();
            CPU_Queue.pop();
            CPU_Queue.push(currFront);
        }
        if (IO_Queue.size() > 0)
        {
            Process *currFront = IO_Queue.front();
            IO_Queue.pop();
            IO_Queue.push(currFront);
        }
    }
}

int main(int argc, char const *argv[])
{
    queue<Process *> arrivalQueue;
    ifstream testCase(argv[1]);
    string currLine;
    while (getline(testCase, currLine))
    {
        if (currLine[0] != '<')
        {
            vector<int> currLineToken = {};
            string tempStr;
            stringstream ss(currLine);
            while (getline(ss, tempStr, ' '))
            {
                if (tempStr == "-1")
                    break;
                currLineToken.push_back(stoi(tempStr));
            }
            Process *newProcess = new Process(PID++, currLineToken);
            arrivalQueue.push(newProcess);
        }
    }
    vector<int> turnaroundTime(PID + 1, -1), waitingTime(PID + 1, -1);
    simulate(arrivalQueue, turnaroundTime, waitingTime);
    for (int i = 1; i < PID; i++)
        printf("PID: %d, Turnaround Time: %d, Waiting Time: %d, Penalty Ratio: %f\n", i, turnaroundTime[i], waitingTime[i], (float)turnaroundTime[i] / ((float)turnaroundTime[i] - (float)waitingTime[i]));
    int totalTurnaround = 0, totalWaiting = 0;
    double totalPenalty = 0;
    totalTurnaround = accumulate(turnaroundTime.begin(), turnaroundTime.end(), totalTurnaround);
    totalWaiting = accumulate(waitingTime.begin(), waitingTime.end(), totalWaiting);
    printf("Average Time: %d\n", totalTurnaround / PID);
    printf("Average Waiting: %d\n", totalWaiting / PID);
    for (int i = 1; i < PID; i++)
        totalPenalty += (float)turnaroundTime[i] / ((float)turnaroundTime[i] - (float)waitingTime[i]);
    printf("Average Penalty: %f\n", totalPenalty / PID);
    printf("Throughput: %f", (totalCPUWork / (float)(PID - 1)) / ((double)totalTurnaround));
    return 0;
}

