#include <bits/stdc++.h>
using namespace std;

void LRUPageReplacement(vector<int>& pages, int frames){
          unordered_set<int> s;
          unordered_map<int, int> indexes;
          list<int> memory;
          int pageFaults =0;

          for(int i=0; i<pages.size(); i++){
                    int currentPage = pages[i];

                    if(s.size() < frames){
                              if(s.find(currentPage) == s.end()){
                                        s.insert(currentPage);
                                        memory.push_back(currentPage);
                                        pageFaults++;
                              }
                              indexes[currentPage] = i;
                    }else{
                              if(s.find(currentPage) == s.end()){
                                        int lru = INT_MAX, val =1;

                                        for(auto it: s){
                                                  if(indexes[it] < lru){
                                                            lru = indexes[it];
                                                            val = it;
                                                  }
                                        }

                                        s.erase(val);
                                        memory.remove(val);
                                        s.insert(currentPage);
                                        memory.push_back(currentPage);
                                        pageFaults++;
                              }
                              indexes[currentPage] = i;
                    }

                    cout << "Page " << currentPage << " is in the frame. Frame Contents: ";
                    for (int f : memory) {
                              cout << f << " ";
                    }
                    cout<<"page faults: "<<pageFaults;
                    cout << endl;
          }
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int frames = 4;
    LRUPageReplacement(pages, frames);
    return 0;
}

