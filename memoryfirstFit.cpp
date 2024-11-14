#include <bits/stdc++.h>
using namespace std;

void firstFit(vector<int>& blockSize, int b, vector<int>& processSize, int p){
          vector<int> allocation(p, -1);

          for(int i=0; i<p; i++){
                    for(int j=0; j<b; j++){
                              if(blockSize[j]>=processSize[i]){
                                        allocation[i] = j;
                                        blockSize[j] -= processSize[i];
                                        break;
                              }
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
          }
}

int main(){
          vector<int> blockSize = {100, 500, 200, 300, 600};
          vector<int> processSize = {212, 417, 112, 426};
          int b = blockSize.size();
          int p = processSize.size();
          firstFit(blockSize, b, processSize, p);

          return 0;
}