#include <bits/stdc++.h>
using namespace std;

void optimalPageReplacement(vector<int>& pages, int frames) {
    unordered_set<int> s;
    vector<int> memory;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        int currentPage = pages[i];

        // If the page is not already in memory
        if (s.find(currentPage) == s.end()) {
            pageFaults++;

            // If there is space in memory, add the page directly
            if (s.size() < frames) {
                s.insert(currentPage);
                memory.push_back(currentPage);
            } else {
                // Find the page to replace
                int farthestIndex = -1, pageToReplace = -1;
                for (int j = 0; j < memory.size(); j++) {
                    int page = memory[j];
                    int nextUseIndex = INT_MAX;

                    // Check when this page will be used next
                    for (int k = i + 1; k < pages.size(); k++) {
                        if (pages[k] == page) {
                            nextUseIndex = k;
                            break;
                        }
                    }

                    // Choose the page that has the farthest next use
                    if (nextUseIndex > farthestIndex) {
                        farthestIndex = nextUseIndex;
                        pageToReplace = j;
                    }
                }

                // Replace the page in memory
                s.erase(memory[pageToReplace]);
                s.insert(currentPage);
                memory[pageToReplace] = currentPage;
            }
        }

        // Display current frame contents
        cout << "Page " << currentPage << " is in the frame. Frame Contents: ";
        for (int f : memory) {
            cout << f << " ";
        }
        cout << endl;
    }

    cout << "Total Page Faults = " << pageFaults << endl;
}

int main() {
    vector<int> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int frames = 3;
    optimalPageReplacement(pages, frames);
    return 0;
}
