#include <bits/stdc++.h>
using namespace std;


void nextFit(vector<int>& blockSize, int b, vector<int>& processSize, int p){
          vector<int> allocation(p, -1);
          int locationCounter = 0;

          for(int i=0; i<p; i++){
                    bool allocated = false;
                    for(int j=0; j<b; j++){
                              int currentBlock = (locationCounter+j)%b;
                              if(blockSize[currentBlock]>=processSize[i]){
                                        allocation[i] = currentBlock;
                                        blockSize[currentBlock] -= processSize[i];
                                        locationCounter = currentBlock;
                                        allocated = true;
                              }
                    }

                    if(!allocated){
                              allocation[i] = -1;
                    }
          }

          cout<<"Process No.\tProcess Size\tBlock No.\n";
          for(int i=0; i<p; i++){
                    cout<<" "<<i+1<<"\t\t"<<processSize[i]<<"\t\t";
                    if(allocation[i] != -1){
                              cout<<allocation[i]+1;
                    }else{
                              cout<<"Not Allocated";
                    }
                    cout<<endl;
          }
}

int main() {
          vector<int> blockSize = {100, 500, 200, 300, 600};
          vector<int> processSize = {212, 417, 112, 426};
          int b = blockSize.size();
          int p = processSize.size();
          nextFit(blockSize, b, processSize, p);
}