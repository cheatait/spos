#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

class RW {
private:
    mutex readlock;   // Mutex for read lock
    mutex writelock;  // Mutex for write lock
    static int readcount;           // Counter for number of readers

public:
    class Read {
    private:
        RW& rw;  // Reference to the RW object
    public:
        Read(RW& rw_obj) : rw(rw_obj) {}

        void operator()() {
            try {
                unique_lock<mutex> readlock_guard(rw.readlock);
                rw.readcount++;
                if (rw.readcount == 1) {
                    rw.writelock.lock();
                }
                readlock_guard.unlock();

                cout << "Thread " << this_thread::get_id() << " is reading." << endl;
                this_thread::sleep_for(chrono::milliseconds(2500)); // Simulating reading operation
                cout << "Thread " << this_thread::get_id() << " has finished reading." << endl;

                unique_lock<mutex> readlock_guard2(rw.readlock);
                rw.readcount--;
                if (rw.readcount == 0) {
                    rw.writelock.unlock();
                }
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
    };

    class Write {
    private:
        RW& rw;  // Reference to the RW object
    public:
        Write(RW& rw_obj) : rw(rw_obj) {}

        void operator()() {
            try {
                unique_lock<mutex> writelock_guard(rw.writelock);
                cout << "Thread " << this_thread::get_id() << " is writing." << endl;
                this_thread::sleep_for(chrono::milliseconds(1000)); // Simulating writing operation
                cout << "Thread " << this_thread::get_id() << " has finished writing." << endl;
            } catch (const exception& e) {
                cout << e.what() << endl;
            }
        }
    };

    void fun() {
        int n;
        cout << "Enter the number of read & write processes: ";
        cin >> n;

        vector<int> seq(n);
        cout << "Enter the sequence: 1 for reading & 0 for writing." << endl;
        for (int i = 0; i < n; i++) {
            cin >> seq[i];
        }

        vector<thread> processes;
        for (int i = 0; i < n; i++) {
            if (seq[i] == 1) {
                processes.push_back(thread(Read(*this)));  // Pass RW instance to Read thread
            } else if (seq[i] == 0) {
                processes.push_back(thread(Write(*this))); // Pass RW instance to Write thread
            }
        }

        for (auto& t : processes) {
            t.join();
        }
    }
};

int RW::readcount = 0;  // Initialize static variable readcount

int main() {
    RW rw;
    rw.fun();
   
}
