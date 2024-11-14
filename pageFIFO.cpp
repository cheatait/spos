#include <bits/stdc++.h>
using namespace std;


void fifoPageReplacement(vector<int>& pages, int frames){
          unordered_set<int> s;
          queue<int> pageQueue;
          vector<int> frameContents(frames, -1);
          int pageFaults =0;
          int pageHits =0;

          for(int page: pages){
                    
                    if(s.find(page) == s.end()){
                              if(s.size() < frames){
                                        s.insert(page);
                                        pageQueue.push(page);
                                        frameContents[s.size()-1]=page;
                              }else{
                                        int oldPage = pageQueue.front();
                                        pageQueue.pop();
                                        s.erase(oldPage);

                                        s.insert(page);
                                        pageQueue.push(page);

                                        for(int i=0; i<frames; i++){
                                                  if(frameContents[i] == oldPage){
                                                            frameContents[i] = page;
                                                            break;
                                                  }
                                        }
                              }
                              pageFaults++;
                    }else{
                              pageHits++;
                    }

                    cout <<"page"<<page<<" is in the frame . Frame Contents: ";
                    for(int i=0; i<frames; i++){
                              cout << frameContents[i] << " ";
                    }
          }

          cout << "\nPage Faults: " << pageFaults << "\nPage Hits: " << pageHits << endl;
}

int main(){
          vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
          int frames = 3;
          fifoPageReplacement(pages, frames);
          return 0;
}