#include <bits/stdc++.h>

using namespace std;

struct Process {
    int arrivalTime;
    int burstTime;
    int priority;
    int processNumber;
};

bool compareArrivalAndPriority(const Process& a, const Process& b) {
    if (a.arrivalTime == b.arrivalTime) {
        return a.priority < b.priority;
    }
    return a.arrivalTime < b.arrivalTime;
}

void calculateWaitingTime(const vector<Process>& processes, int n, vector<int>& waitingTime) {
    vector<int> serviceTime(n);
    serviceTime[0] = processes[0].arrivalTime;
    waitingTime[0] = 0;

    for (int i = 1; i < n; i++) {
        serviceTime[i] = serviceTime[i - 1] + processes[i - 1].burstTime;
        waitingTime[i] = serviceTime[i] - processes[i].arrivalTime;
        if (waitingTime[i] < 0) waitingTime[i] = 0;
    }
}

void calculateTurnAroundTime(const vector<Process>& processes, int n, const vector<int>& waitingTime, vector<int>& turnAroundTime) {
    for (int i = 0; i < n; i++) {
        turnAroundTime[i] = processes[i].burstTime + waitingTime[i];
    }
}

void findAverageTimes(const vector<Process>& processes, int n) {
    vector<int> waitingTime(n), turnAroundTime(n);

    calculateWaitingTime(processes, n, waitingTime);
    calculateTurnAroundTime(processes, n, waitingTime, turnAroundTime);

    vector<int> startTime(n), completionTime(n);
    double totalWaitingTime = 0, totalTurnAroundTime = 0;

    startTime[0] = processes[0].arrivalTime;
    completionTime[0] = startTime[0] + turnAroundTime[0];

    for (int i = 1; i < n; i++) {
        startTime[i] = completionTime[i - 1];
        completionTime[i] = startTime[i] + turnAroundTime[i] - waitingTime[i];
    }

    cout << "Process\tStart Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnAroundTime += turnAroundTime[i];

        cout << "P" << processes[i].processNumber << "\t\t" 
             << startTime[i] << "\t\t" 
             << completionTime[i] << "\t\t" 
             << waitingTime[i] << "\t\t" 
             << turnAroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << (totalWaitingTime / n) << " ms" << endl;
    cout << "Average Turnaround Time: " << (totalTurnAroundTime / n) << " ms" << endl;
}

int main() {
    int n;
    cout << "Enter the total number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter the Arrival Time, Burst Time, and Priority for Process " << (i + 1) << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
        processes[i].processNumber = i + 1;
    }

    sort(processes.begin(), processes.end(), compareArrivalAndPriority);
    findAverageTimes(processes, n);

    return 0;
}
