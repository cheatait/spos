#include <bits/stdc++.h>
using namespace std;


struct process{
          int id;
          int arrivalTime;
          int burstTime;
          int waitingTime;
          int turnaroundTime;
};


void findWaitingAndTurnAroundTime(vector<process>& processes){
          int n= processes.size();
          int currentTime =0;

          for(int i=0; i<n; i++){
                    if(currentTime< processes[i].arrivalTime){
                              currentTime = processes[i].arrivalTime;
                    }
                    processes[i].waitingTime = currentTime - processes[i].arrivalTime;
                    processes[i].turnaroundTime = processes[i].waitingTime + processes[i].burstTime;

                    currentTime += processes[i].burstTime;
          }
}

void findAverageTimes(vector<process>& processes){
          int totalWaitingTime =0;
          int totalTurnaroundTime =0;

          findWaitingAndTurnAroundTime(processes);

          for(const auto& p: processes){
                    totalWaitingTime += p.waitingTime;
                    totalTurnaroundTime += p.turnaroundTime;
                    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
                    cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" << p.waitingTime << "\t" << p.turnaroundTime << endl;
          }

          cout << "Average Waiting Time: " << (double)totalWaitingTime/processes.size() << endl;
          cout << "Average Turnaround Time: " << (double)totalTurnaroundTime/processes.size() << endl;
}



int main(){
          int n;
          cout<<"enter the number of processes: ";
          cin>>n;

          vector<process> processes(n);
          for(int i=0; i<n; i++){
                    processes[i].id = i+1;
                    cout<<"enter the arrival time of process "<<i+1<<": ";
                    cin>>processes[i].arrivalTime;
                    cout<<"enter the burst time of process "<<i+1<<": ";
                    cin>>processes[i].burstTime;
          }

          findAverageTimes(processes);
}