#include <bits/stdc++.h>

using namespace std;

struct Process {
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

int main() {
    int n, timeQuantum, remainingProcesses;
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    cout << "Enter the time quantum: ";
    cin >> timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter the arrival time and burst time of each process:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    remainingProcesses = n;
    int currentTime = 0;
    bool processExecuted;

    cout << "\nProcess\tTurnaround Time\tWaiting Time\n";

    while (remainingProcesses != 0) {
        processExecuted = false;

        for (int i = 0; i < n; i++) {
            if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime) {
                // Execute the process for either time quantum or remaining time
                int executionTime = min(processes[i].remainingTime, timeQuantum);
                processes[i].remainingTime -= executionTime;
                currentTime += executionTime;
                processExecuted = true;

                // If the process is completed
                if (processes[i].remainingTime == 0) {
                    remainingProcesses--;
                    processes[i].turnaroundTime = currentTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    totalWaitingTime += processes[i].waitingTime;
                    totalTurnaroundTime += processes[i].turnaroundTime;

                    cout << "P" << i + 1 << "\t\t" << processes[i].turnaroundTime
                         << "\t\t" << processes[i].waitingTime << endl;
                }
            }
        }

        // If no process was executed, advance time to the next arrival time
        if (!processExecuted) {
            currentTime++;
        }
    }

    cout << "\nAverage Waiting Time: " << totalWaitingTime / n << " ms\n";
    cout << "Average Turnaround Time: " << totalTurnaroundTime / n << " ms\n";

    return 0;
}
