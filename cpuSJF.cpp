#include <bits/stdc++.h>
using namespace std;


struct Process{
          int id;
          int arrivalTime;
          int burstTime;
          int waitingTime;
          int turnaroundTime;
};

bool compareArrivalTime(const Process &a, const Process &b){
          if(a.burstTime == b.burstTime){
                    return a.arrivalTime < b.arrivalTime;
          }
          return a.burstTime < b.burstTime;
}


void findWaitAndTurnaroundTime(vector<Process>& processes){
          int n= processes.size();
          int currentTime = 0;
          vector<bool> completed(n, false);
          int completedCount =0;

          while(completedCount<n){
                    int shortestIndex = -1;
                    for(int i=0; i<n; i++){
                              if(!completed[i] && processes[i].arrivalTime <= currentTime){
                                        if(shortestIndex == -1 || processes[i].burstTime < processes[shortestIndex].burstTime){
                                                  shortestIndex = i;
                                        }
                              }
                    }

                    if(shortestIndex != -1){
                              processes[shortestIndex].waitingTime = currentTime - processes[shortestIndex].arrivalTime;
                              processes[shortestIndex].turnaroundTime = processes[shortestIndex].waitingTime + processes[shortestIndex].burstTime;
                              currentTime += processes[shortestIndex].burstTime;
                              completed[shortestIndex] = true;
                              completedCount++;
                    }else{
                              currentTime++;
                    }
          }
}


void findAvgTimes(vector<Process>& processes){
          int totalWaitingTime =0;
          int totalTurnaroundTime=0;
          
          findWaitAndTurnaroundTime(processes);

          for(const auto& p: processes){
                   totalTurnaroundTime += p.turnaroundTime;
                   totalWaitingTime += p.waitingTime;

                   cout<<"Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
                     cout<<p.id<<"\t"<<p.arrivalTime<<"\t"<<p.burstTime<<"\t"<<p.waitingTime<<"\t"<<p.turnaroundTime<<endl;
          }

          cout<<"avg"<<" "<<(float)totalWaitingTime/processes.size()<<" "<<(float)totalTurnaroundTime/processes.size()<<endl; 

}



int main(){
          int n;
          cout<<"enter the number of processes: ";
          cin>>n;

          vector<Process> processes(n);
          for(int i=0; i<n; i++){
                    processes[i].id = i+1;
                    cout<<"enter the arrival time of process "<<i+1<<": ";
                    cin>>processes[i].arrivalTime;
                    cout<<"enter the burst time of process "<<i+1<<": ";
                    cin>>processes[i].burstTime;
          }

          findAvgTimes(processes);
}